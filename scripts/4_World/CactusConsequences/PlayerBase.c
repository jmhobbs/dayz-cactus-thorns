modded class PlayerBase
{
	//! Server-authoritative thorns state (CactusConsequencesThornsState), synced so the client can show the badge,
	//! block sprint and offer the pliers action
	protected int m_CC_ThornsState;
	protected int m_CC_ThornsStateLocal;
	protected int m_CC_NextCactusContactTime;

	//! Vanilla registers its own sync variables in Init, which its constructor calls
	override void Init()
	{
		super.Init();

		RegisterNetSyncVariableInt("m_CC_ThornsState", CactusConsequencesThornsState.NONE, CactusConsequencesThornsState.THORNS_NO_SPRINT);
	}

	override void OnStepEvent(string pEventType, string pUserString, int pUserInt)
	{
		super.OnStepEvent(pEventType, pUserString, pUserInt);

		if (g_Game.IsServer())
			CC_CheckCactusContact();
	}

	//! The first sync can arrive before the client controls this character, so refresh the badge once it does
	override void OnPlayerLoaded()
	{
		super.OnPlayerLoaded();

		if (IsControlledPlayer())
			CC_UpdateThornsBadge();
	}

	override bool CanSprint()
	{
		if (m_CC_ThornsState == CactusConsequencesThornsState.THORNS_NO_SPRINT)
			return false;

		return super.CanSprint();
	}

	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();

		if (m_CC_ThornsStateLocal != m_CC_ThornsState)
		{
			m_CC_ThornsStateLocal = m_CC_ThornsState;
			if (IsControlledPlayer())
				CC_UpdateThornsBadge();
		}
	}

	bool CC_HasThorns()
	{
		return m_CC_ThornsState != CactusConsequencesThornsState.NONE;
	}

	//! Server only
	void CC_SetThornsState(int state)
	{
		if (m_CC_ThornsState == state)
			return;

		m_CC_ThornsState = state;
		SetSynchDirty();
	}

	//! Server only. Returns false if thorns were already in.
	bool CC_AddThorns()
	{
		if (GetModifiersManager().IsModifierActive(eModifiers.MDF_CACTUS_THORNS))
			return false;

		GetModifiersManager().ActivateModifier(eModifiers.MDF_CACTUS_THORNS);
		return true;
	}

	//! Server only
	void CC_RemoveThorns()
	{
		if (GetModifiersManager().IsModifierActive(eModifiers.MDF_CACTUS_THORNS))
			GetModifiersManager().DeactivateModifier(eModifiers.MDF_CACTUS_THORNS);
	}

	void CC_SendInjuredSound()
	{
		SendSoundEvent(EPlayerSoundEventID.INJURED_LIGHT);
	}

	void CC_UpdateThornsBadge()
	{
		PluginPlayerStatus playerStatus = PluginPlayerStatus.Cast(GetPlugin(PluginPlayerStatus));
		if (playerStatus)
			playerStatus.SetBadge(NTFKEY_CACTUS_THORNS, CC_HasThorns());
	}

	protected void CC_CheckCactusContact()
	{
		if (!IsAlive() || IsInVehicle() || !GetModifiersManager())
			return;

		int now = g_Game.GetTime();
		if (now < m_CC_NextCactusContactTime)
			return;

		CactusConsequencesConfig config = CactusConsequencesSettings.Get();

		HumanMovementState state = new HumanMovementState();
		GetMovementState(state);
		if (!CactusConsequencesContact.IsTriggeringMovement(config, state.m_iMovement))
			return;

		if (!CactusConsequencesContact.IsTouchingCactus(this, config))
			return;

		m_CC_NextCactusContactTime = now + Math.Round(config.ContactCooldownSeconds * 1000.0);
		CactusConsequencesContact.ApplyContact(this, config);
	}
}
