//! Thorns stay in until pulled out with pliers. Persistent but without attached-time tracking,
//! so a save stays loadable if the mod is ever removed (see ModifiersManager.OnStoreLoad).
class CactusThornsMdfr: ModifierBase
{
	override void Init()
	{
		m_TrackActivatedTime 	= false;
		m_IsPersistent 			= true;
		m_ID 					= eModifiers.MDF_CACTUS_THORNS;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= DEFAULT_TICK_TIME_ACTIVE;

		DisableActivateCheck();
	}

	override bool ActivateCondition(PlayerBase player)
	{
		return false;
	}

	override bool DeactivateCondition(PlayerBase player)
	{
		return false;
	}

	override void OnReconnect(PlayerBase player)
	{
		OnActivate(player);
	}

	override void OnActivate(PlayerBase player)
	{
		CactusConsequencesConfig config = CactusConsequencesSettings.Get();

		player.m_InjuryHandler.m_ForceInjuryAnimMask = player.m_InjuryHandler.m_ForceInjuryAnimMask | CACTUS_CONSEQUENCES_INJURY_OVERRIDE;
		player.ForceUpdateInjuredState();

		if (config.ThornsBlockSprint)
			player.CC_SetThornsState(CactusConsequencesThornsState.THORNS_NO_SPRINT);
		else
			player.CC_SetThornsState(CactusConsequencesThornsState.THORNS);
	}

	override void OnDeactivate(PlayerBase player)
	{
		player.m_InjuryHandler.m_ForceInjuryAnimMask = player.m_InjuryHandler.m_ForceInjuryAnimMask & ~CACTUS_CONSEQUENCES_INJURY_OVERRIDE;
		player.ForceUpdateInjuredState();

		player.CC_SetThornsState(CactusConsequencesThornsState.NONE);
	}

	//! Slow seep rather than a vanilla bleeding source, so it can't be bandaged and only pliers stop it
	override void OnTick(PlayerBase player, float deltaT)
	{
		float bloodLoss = CactusConsequencesSettings.Get().ThornsBloodLossPerMinute / 60.0 * deltaT;
		if (bloodLoss > 0)
			player.AddHealth("", "Blood", -bloodLoss);
	}
}
