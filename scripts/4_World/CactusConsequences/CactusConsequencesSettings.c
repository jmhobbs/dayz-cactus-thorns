class CactusConsequencesSettings
{
	protected static const string CONFIG_PATH = "$profile:CactusConsequences.json";

	protected static ref CactusConsequencesConfig s_Config;

	//! Server only. Loads the config on first use, writing defaults if the file is missing.
	static CactusConsequencesConfig Get()
	{
		if (!s_Config)
			Load();

		return s_Config;
	}

	static void Load()
	{
		s_Config = new CactusConsequencesConfig();

		if (!FileExist(CONFIG_PATH))
		{
			s_Config.SetDefaults();
			Save();
			return;
		}

		string errorMessage;
		if (!JsonFileLoader<CactusConsequencesConfig>.LoadFile(CONFIG_PATH, s_Config, errorMessage))
		{
			Print("[CactusConsequences] Failed to load " + CONFIG_PATH + ", using defaults: " + errorMessage);
			s_Config = new CactusConsequencesConfig();
			s_Config.SetDefaults();
		}

		s_Config.Validate();
	}

	protected static void Save()
	{
		string errorMessage;
		if (!JsonFileLoader<CactusConsequencesConfig>.SaveFile(CONFIG_PATH, s_Config, errorMessage))
			Print("[CactusConsequences] Failed to write default config to " + CONFIG_PATH + ": " + errorMessage);
	}
}
