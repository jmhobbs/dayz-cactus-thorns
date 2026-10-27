class ActionRemoveCactusThornsSelfCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(CACTUS_CONSEQUENCES_THORNS_REMOVE_TIME);
	}
}

class ActionRemoveCactusThornsSelf: ActionContinuousBase
{
	void ActionRemoveCactusThornsSelf()
	{
		m_CallbackClass = ActionRemoveCactusThornsSelfCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_CRAFTING;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_Text = "Pull out cactus thorns";
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTSelf;
	}

	override bool HasTarget()
	{
		return false;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!player.CC_HasThorns())
			return false;

		return super.ActionCondition(player, target, item);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		action_data.m_Player.CC_RemoveThorns();

		float pliersDamage = CactusConsequencesSettings.Get().PliersDamage;
		if (pliersDamage > 0 && action_data.m_MainItem)
			action_data.m_MainItem.AddHealth("", "", -pliersDamage);
	}
}
