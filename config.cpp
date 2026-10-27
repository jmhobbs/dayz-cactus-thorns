class CfgPatches
{
  class CactusConsequences
  {
    units[] = {};
    weapons[] = {};
    requiredVersion = 0.1;
    requiredAddons[] = {
      "DZ_Data",
      "DZ_Scripts",
      "DZ_Gear_Tools"
    };
  };
};
class CfgMods
{
  class CactusConsequences
  {
    type = "mod";
    author = "WILDLANDZ Team";
    name = "CactusConsequences";
    dir = "CactusConsequences";
    dependencies[] = {"World", "Mission"};
    class defs
    {
      class worldScriptModule
      {
        value = "";
        files[] = {"CactusConsequences/scripts/4_World"};
      };
      class missionScriptModule
      {
        value = "";
        files[] = {"CactusConsequences/scripts/5_Mission"};
      };
    };
  };
};
