modded enum eModifiers
{
	MDF_CACTUS_THORNS
}

enum CactusConsequencesThornsState
{
	NONE = 0,
	THORNS = 1,
	THORNS_NO_SPRINT = 2
}

//! HUD badge key, kept well clear of the vanilla NTFKEY_* values
const int NTFKEY_CACTUS_THORNS = 2601;

//! Bit in InjuryAnimationHandler.m_ForceInjuryAnimMask, above the vanilla eInjuryOverrides values
const int CACTUS_CONSEQUENCES_INJURY_OVERRIDE = 128;

//! Shared by client and server, so it cannot come from the server-side config
const float CACTUS_CONSEQUENCES_THORNS_REMOVE_TIME = 8.0;

const string CACTUS_CONSEQUENCES_BADGE_WIDGET = "CactusConsequencesThorns";
