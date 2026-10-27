modded class MissionServer
{
	override void OnMissionStart()
	{
		super.OnMissionStart();

		// Load now so the default config file is written at startup, not on the first cactus contact
		CactusConsequencesSettings.Load();
	}
}
