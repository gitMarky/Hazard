#appendto Library_HUDController

// Overload the hud controller
public func GetGUIControllerID()
{
	return GUI_Controller_Hazard;
}


private func GuiPositionHazardInfoField()
{
	var margin = ToEmString(5);
	var margin_bottom = ToEmString(-5);
	var width = ToPercentString(400);
	var height = ToPercentString(-200);
	var bottom = ToPercentString(1000);

	return {
		Left = Format("%s", margin), Right = Format("%s%s", margin, width),
		Top = Format("%s%s%s", bottom, margin_bottom, height), Bottom = Format("%s%s", bottom, margin_bottom),
	};
}