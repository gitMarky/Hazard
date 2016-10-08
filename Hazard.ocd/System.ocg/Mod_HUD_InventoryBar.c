#appendto GUI_Controller_InventoryBar

func AssembleInventoryButton(int max_slots, int slot_number, proplist slot_info)
{
	var button = _inherited(max_slots, slot_number, slot_info, ...);
	
	button.Symbol.Std = Icon_Hazard_Menu_Circle;
	button.Symbol.Quick = Icon_Hazard_Menu_Circle;
	button.Symbol.Selected = Icon_Hazard_Menu_CircleHighlight;
	button.quick_switch.Text.Quick = Format("<c %s>[%s]</c>", GUI_COLOR_TEXT, GetPlayerControlAssignment(GetOwner(), CON_QuickSwitch, true));
	//button.slot_number.Text = Format("<c %s>%2d</c>", GUI_COLOR_TEXT, slot_info.slot + 1);
	
	return button;
}
