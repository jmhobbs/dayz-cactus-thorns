//! Server-side handling of a player moving through a cactus
class CactusConsequencesContact
{
	protected static const vector CHECK_BOX_SIZE = "0.75 2.5 0.75";

	protected static const string LEG_BLEED_ZONES[2] = {"LeftLeg", "RightLeg"};
	protected static const string UPPER_BODY_BLEED_ZONES[2] = {"LeftForeArmRoll", "RightForeArmRoll"};

	static bool IsTriggeringMovement(CactusConsequencesConfig config, int movementIdx)
	{
		switch (movementIdx)
		{
			case DayZPlayerConstants.MOVEMENTIDX_WALK:
				return config.TriggerWhileWalking;
			case DayZPlayerConstants.MOVEMENTIDX_RUN:
			case DayZPlayerConstants.MOVEMENTIDX_CROUCH_RUN:
				return config.TriggerWhileJogging;
			case DayZPlayerConstants.MOVEMENTIDX_SPRINT:
				return config.TriggerWhileSprinting;
		}

		return false;
	}

	static bool IsTouchingCactus(PlayerBase player, CactusConsequencesConfig config)
	{
		if (config.CactusClassNames.Count() == 0)
			return false;

		array<Object> excludedObjects = new array<Object>();
		excludedObjects.Insert(player);
		array<Object> collidedObjects = new array<Object>();

		// The cacti have a Geometry LOD but no View Geometry, so check Geometry first
		if (!g_Game.IsBoxCollidingGeometry(player.GetPosition(), vector.Zero, CHECK_BOX_SIZE, ObjIntersectGeom, ObjIntersectView, excludedObjects, collidedObjects))
			return false;

		foreach (Object obj : collidedObjects)
		{
			if (obj && IsCactus(obj.GetType(), config))
				return true;
		}

		return false;
	}

	static bool IsCactus(string typeName, CactusConsequencesConfig config)
	{
		foreach (string cactusPrefix : config.CactusClassNames)
		{
			if (cactusPrefix != "" && typeName.IndexOf(cactusPrefix) == 0)
				return true;
		}

		return false;
	}

	static void ApplyContact(PlayerBase player, CactusConsequencesConfig config)
	{
		bool hitLegs = Math.RandomFloat01() < config.LegHitChance;

		array<EntityAI> clothing = new array<EntityAI>();
		if (hitLegs)
		{
			AddWornItem(player, InventorySlots.LEGS, clothing);
			AddWornItem(player, InventorySlots.FEET, clothing);
		}
		else
		{
			AddWornItem(player, InventorySlots.BODY, clothing);
			AddWornItem(player, InventorySlots.VEST, clothing);
		}

		float exposure = 1.0 - GetProtection(clothing, config);

		// New thorns always come with a cut and a health hit; otherwise roll for a plain cut
		if (Math.RandomFloat01() < config.ThornsChance * exposure && player.CC_AddThorns())
		{
			if (config.ThornsHealthDamage > 0)
				player.AddHealth("", "Health", -config.ThornsHealthDamage);

			ApplyCut(player, config, hitLegs, clothing);
		}
		else if (Math.RandomFloat01() < config.CutChance * exposure)
		{
			ApplyCut(player, config, hitLegs, clothing);
		}
	}

	protected static void AddWornItem(PlayerBase player, int slotId, array<EntityAI> clothing)
	{
		EntityAI item = player.GetInventory().FindAttachment(slotId);
		if (item)
			clothing.Insert(item);
	}

	//! Combined protection of the worn items, each one stopping its share of what gets past the others
	protected static float GetProtection(array<EntityAI> clothing, CactusConsequencesConfig config)
	{
		float exposure = 1.0;

		foreach (EntityAI item : clothing)
		{
			if (item.IsRuined())
				continue;

			foreach (CactusConsequencesProofItem proofItem : config.CactusProofItems)
			{
				if (proofItem && proofItem.ClassName != "" && item.IsKindOf(proofItem.ClassName))
				{
					exposure *= 1.0 - proofItem.Protection;
					break;
				}
			}
		}

		return 1.0 - exposure;
	}

	protected static void ApplyCut(PlayerBase player, CactusConsequencesConfig config, bool hitLegs, array<EntityAI> clothing)
	{
		string zone;
		if (hitLegs)
			zone = LEG_BLEED_ZONES[Math.RandomInt(0, 2)];
		else
			zone = UPPER_BODY_BLEED_ZONES[Math.RandomInt(0, 2)];

		if (player.GetBleedingManagerServer() && player.GetBleedingManagerServer().AttemptAddBleedingSourceBySelection(zone))
			player.CC_SendInjuredSound();

		if (config.ClothingDamage <= 0)
			return;

		foreach (EntityAI item : clothing)
		{
			item.AddHealth("", "", -config.ClothingDamage);
		}
	}
}
