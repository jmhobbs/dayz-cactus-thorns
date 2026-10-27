modded class IngameHud
{
	protected static const string CC_THORNS_BADGE_LAYOUT = "CactusConsequences/gui/layouts/thorns_badge.layout";
	protected static const string CC_THORNS_BADGE_IMAGE = "CactusConsequences/data/gui/thorns_badge_co.paa";

	//! Vanilla clears the badge maps here, so our badge is added back after super every time
	override void InitBadgesAndNotifiers()
	{
		super.InitBadgesAndNotifiers();

		ImageWidget thornsBadge = ImageWidget.Cast(m_Badges.FindAnyWidget(CACTUS_CONSEQUENCES_BADGE_WIDGET));
		if (!thornsBadge)
		{
			thornsBadge = ImageWidget.Cast(g_Game.GetWorkspace().CreateWidgets(CC_THORNS_BADGE_LAYOUT, m_Badges));
			if (!thornsBadge)
				return;

			thornsBadge.SetName(CACTUS_CONSEQUENCES_BADGE_WIDGET);
			thornsBadge.LoadImageFile(0, CC_THORNS_BADGE_IMAGE);
			thornsBadge.SetImage(0);
		}

		m_BadgesWidgetNames.Set(NTFKEY_CACTUS_THORNS, CACTUS_CONSEQUENCES_BADGE_WIDGET);
		m_BadgesWidgets.Set(NTFKEY_CACTUS_THORNS, thornsBadge);
		m_BadgesWidgetDisplay.Set(NTFKEY_CACTUS_THORNS, false);
		thornsBadge.Show(false);

		// Restore the badge if the HUD was rebuilt while thorns are in
		PlayerBase player = PlayerBase.Cast(g_Game.GetPlayer());
		if (player && player.CC_HasThorns())
			DisplayBadge(NTFKEY_CACTUS_THORNS, 1);
	}
}
