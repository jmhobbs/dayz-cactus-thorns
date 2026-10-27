modded class InjuryAnimationHandler
{
	override eInjuryHandlerLevels GetOverrideLevel(eInjuryHandlerLevels unchanged_level)
	{
		// Vanilla always uses the pristine animation while prone, leave that alone
		if (!(m_ForceInjuryAnimMask & CACTUS_CONSEQUENCES_INJURY_OVERRIDE) || (m_ForceInjuryAnimMask & eInjuryOverrides.PRONE_ANIM_OVERRIDE))
			return super.GetOverrideLevel(unchanged_level);

		// Hide our bit from vanilla, which forces RUINED for any non-zero mask once health is below DAMAGED
		int forceMask = m_ForceInjuryAnimMask;
		m_ForceInjuryAnimMask = forceMask & ~CACTUS_CONSEQUENCES_INJURY_OVERRIDE;
		eInjuryHandlerLevels override_level = super.GetOverrideLevel(unchanged_level);
		m_ForceInjuryAnimMask = forceMask;

		int thornsLevel = CactusConsequencesSettings.Get().ThornsInjuryLevel;
		if (override_level < thornsLevel)
			override_level = thornsLevel;

		return override_level;
	}
}
