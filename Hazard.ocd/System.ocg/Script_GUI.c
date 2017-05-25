/*
 * Shows a GUI for a crew member, if the crew is enabled.
 * Hides it otherwise
 *
 * @par crew The crew member. The GUI is hidden if this object is nil.
 * @par gui A proplist containing the following properties:
 *           - Menu: a GUI definition (you usually open it with GUIOpen)
 *           - ID: the GUI ID (return value of GUIOpen) 
 */
global func GuiShowForCrew(proplist gui, int player, object crew)
{
	AssertObjectContext();

	if (crew && crew->GetCrewEnabled())
	{
		GuiShowMenu(gui, player);
		return true;
	}
	else
	{
		GuiHideMenu(gui);

		return false;
	}
}


/*
 * Makes a gui visible to a certain player.
 *
 * @par gui A proplist containing the following properties:
 *           - Menu: a GUI definition (you usually open it with GUIOpen)
 *           - ID: the GUI ID (return value of GUIOpen) 
 */
global func GuiShowMenu(proplist gui, int player)
{
	AssertObjectContext();

	player = player ?? GetOwner();
	
	// Make sure inventory is visible
	if (gui.Menu.Player != player)
	{
		gui.Menu.Player = player;
		GuiUpdate(gui.Menu, gui.ID);
	}
}

/*
 * Hides a gui from all players.
 *
 * @par menu A proplist containing the following properties:
 *           - Menu: a GUI definition (you usually open it with GUIOpen)
 *           - ID: the GUI ID (return value of GUIOpen) 
 */
global func GuiHideMenu(proplist gui)
{
	AssertObjectContext();

	// Make sure inventory is invisible
	if (gui.Menu.Player != NO_OWNER)
	{
		gui.Menu.Player = NO_OWNER;
		GuiUpdate(gui.Menu, gui.ID);
	}
}


global func AmmoUpdateNotification(int diff, int size, proplist info)
{
	AddEffect("AmmoUpdateNotification", this, 300, 1, this, nil, diff, size, info);
}

/* Changed ammo count effect - the ammo icon bounces a little whenever ammo is increased or decreased */
global func FxAmmoUpdateNotificationStart(object target, proplist fx, int temp, int ammodiff, int size, proplist info)
{
	if (temp) return;
	
	fx.diff = 3 * size * ammodiff / Abs(ammodiff) / 4 + size / 4;
	fx.size = size;
	fx.info = info;
}


global func FxAmmoUpdateNotificationAdd(object target, proplist fx, string name, int timer, int ammodiff, int size, proplist info)
{
	fx.diff = 3 * size * ammodiff / Abs(ammodiff) / 4 + size / 4;
}


global func FxAmmoUpdateNotificationEffect(string name, object target, proplist fx, int newNumber)
{
	if (name == "AmmoUpdateNotification")
		return -2;
}


global func FxAmmoUpdateNotificationTimer(object target, proplist fx, int timer)
{
	fx.diff = BoundBy(fx.diff, -fx.size, 1200 - fx.size);
	var size = BoundBy(fx.size + fx.diff, 400, 1200);
	
	var layout = {
		Prototype = GUI_BoxLayout,
		Align = {X = GUI_AlignCenter, Y = GUI_AlignCenter},
		Width = size, Height = size,
	};
	
	var pos = GuiCalculateBoxElementPosition(layout);
	target->~OnAmmoUpdateNotification(pos, fx.info);
	
	
	if (!fx.diff)
	{
		return FX_Execute_Kill;
	}
	
	var sqrtDiff = fx.diff / Abs(fx.diff) * Sqrt(Abs(fx.diff));
	fx.diff -= sqrtDiff;
}
