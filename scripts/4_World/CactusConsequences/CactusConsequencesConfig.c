class CactusConsequencesProofItem
{
	string ClassName;
	float Protection;

	void CactusConsequencesProofItem(string className = "", float protection = 0.0)
	{
		ClassName = className;
		Protection = protection;
	}
}

class CactusConsequencesConfig
{
	int Version = 1;

	//! Matched as a prefix of the object's type name
	ref array<string> CactusClassNames = new array<string>();

	bool TriggerWhileWalking = false;
	bool TriggerWhileJogging = true;
	bool TriggerWhileSprinting = true;
	float ContactCooldownSeconds = 5.0;

	//! Chance a contact hits the legs; otherwise it hits the upper body
	float LegHitChance = 0.7;

	float CutChance = 0.5;
	float ClothingDamage = 8.0;

	float ThornsChance = 0.25;
	//! Single health hit when thorns go in, which always comes with a cut
	float ThornsHealthDamage = 5.0;
	//! Blood (ml, out of 5000) drained per minute while thorns are in. Vanilla regen is ~18 ml/min when fed and watered.
	float ThornsBloodLossPerMinute = 30.0;
	//! eInjuryHandlerLevels value the limp is forced to while thorns are in (1 = WORN, the mildest limp)
	int ThornsInjuryLevel = 1;
	bool ThornsBlockSprint = true;

	float PliersDamage = 2.0;

	//! Matched with IsKindOf, so a base class covers all its variants
	ref array<ref CactusConsequencesProofItem> CactusProofItems = new array<ref CactusConsequencesProofItem>();

	void SetDefaults()
	{
		CactusClassNames.Clear();
		CactusClassNames.Insert("BushHard_b_OpuntiaFicusIndica");

		CactusProofItems.Clear();
		CactusProofItems.Insert(new CactusConsequencesProofItem("HunterPants_ColorBase", 0.75));
		CactusProofItems.Insert(new CactusConsequencesProofItem("HuntingJacket_ColorBase", 0.75));
		CactusProofItems.Insert(new CactusConsequencesProofItem("GorkaPants_ColorBase", 0.6));
		CactusProofItems.Insert(new CactusConsequencesProofItem("GorkaEJacket_ColorBase", 0.6));
		CactusProofItems.Insert(new CactusConsequencesProofItem("LeatherPants_ColorBase", 0.75));
		CactusProofItems.Insert(new CactusConsequencesProofItem("LeatherJacket_ColorBase", 0.75));
		CactusProofItems.Insert(new CactusConsequencesProofItem("FirefightersPants_ColorBase", 0.75));
		CactusProofItems.Insert(new CactusConsequencesProofItem("FirefighterJacket_ColorBase", 0.75));
		CactusProofItems.Insert(new CactusConsequencesProofItem("BDUPants", 0.5));
		CactusProofItems.Insert(new CactusConsequencesProofItem("BDUJacket", 0.5));
		CactusProofItems.Insert(new CactusConsequencesProofItem("USMCPants_ColorBase", 0.5));
		CactusProofItems.Insert(new CactusConsequencesProofItem("USMCJacket_ColorBase", 0.5));
		CactusProofItems.Insert(new CactusConsequencesProofItem("TTSKOPants", 0.5));
		CactusProofItems.Insert(new CactusConsequencesProofItem("TTsKOJacket_ColorBase", 0.5));
		CactusProofItems.Insert(new CactusConsequencesProofItem("M65Jacket_ColorBase", 0.5));
	}

	void Validate()
	{
		if (!CactusClassNames)
			CactusClassNames = new array<string>();

		if (!CactusProofItems)
			CactusProofItems = new array<ref CactusConsequencesProofItem>();

		ContactCooldownSeconds = Math.Max(ContactCooldownSeconds, 0.0);
		LegHitChance = Math.Clamp(LegHitChance, 0.0, 1.0);
		CutChance = Math.Clamp(CutChance, 0.0, 1.0);
		ClothingDamage = Math.Max(ClothingDamage, 0.0);
		ThornsChance = Math.Clamp(ThornsChance, 0.0, 1.0);
		ThornsHealthDamage = Math.Max(ThornsHealthDamage, 0.0);
		ThornsBloodLossPerMinute = Math.Max(ThornsBloodLossPerMinute, 0.0);
		ThornsInjuryLevel = (int)Math.Clamp(ThornsInjuryLevel, eInjuryHandlerLevels.PRISTINE, eInjuryHandlerLevels.RUINED);
		PliersDamage = Math.Max(PliersDamage, 0.0);

		foreach (CactusConsequencesProofItem proofItem : CactusProofItems)
		{
			if (proofItem)
				proofItem.Protection = Math.Clamp(proofItem.Protection, 0.0, 1.0);
		}
	}
}
