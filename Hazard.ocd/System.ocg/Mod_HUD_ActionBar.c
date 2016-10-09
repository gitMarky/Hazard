#appendto GUI_Controller_ActionBar

func AssembleActionBar()
{
	var gui = _inherited(...);
	gui.Symbol = Icon_Hazard_Menu_RectangleRounded;
	gui.key.Text = Format("<c %s>[%s]</c>", GUI_COLOR_TEXT, GetPlayerControlAssignment(GetOwner(), CON_Interact, true));
	return gui;
}