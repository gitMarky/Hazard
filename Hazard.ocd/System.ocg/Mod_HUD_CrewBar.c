#appendto GUI_Controller_CrewBar

func AssembleCrewBar()
{
	var gui = _inherited(...);
	
	gui.cursor.portrait.frame.Symbol = GUI_Hazard_CrewBar;
	gui.next_clonk.portrait.frame.Symbol = GUI_Hazard_CrewBar;
	
	return gui;
}


func CrewDeathIcon()
{
	return Icon_Skull;
}

func CrewHealIcon()
{
	return { Symbol = Icon_Heart, GraphicsName = "" };
}

func CrewFireDamageIcon()
{
	return { Symbol = Icon_Heart, GraphicsName = "OnFire" };
}

func CrewDamageIcon()
{
	return { Symbol = Icon_Heart, GraphicsName = "Broken" };
}

func CrewBreathIcon()
{
	return Icon_Bubbles;
}

func AddCrewBars()
{
	// Health bar
	crew_health_bar = AddCrewBar(RGB(210, 30, 30));
	// Magic bar
	crew_magic_bar = AddCrewBar(RGB(114, 87, 216));
	// Breath bar
	crew_breath_bar = AddCrewBar(RGB(173, 198, 199));
}

// Sets the fill status of the bar. value is between 0 and 1000
// Shows text_val before the bar if given
private func SetCrewBarValue(int bar, int value, int text_val)
{
	if (!crew_bars[bar]) return;
	value = BoundBy(value, 0, 1000);
	var plr = GetOwner();
	var bar_text = "";
	if (text_val) bar_text = Format("<c %s>%d</c>", GUI_COLOR_TEXT, text_val); // only change: text color
	// Displaying the fill with Top = 100% creates an unwanted scrollbar
	//if (value == 0) plr = NO_OWNER;

	GuiUpdate({ fill = { Player = plr, Right = ToPercentString(value) }, text = { Text = bar_text } }, crew_gui_id, crew_bars[bar].ID, this);
}

