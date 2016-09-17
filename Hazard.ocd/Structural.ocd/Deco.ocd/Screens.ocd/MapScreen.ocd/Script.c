static const MAP_SCREEN_ZoomFactor = 10;

static MAP_SCREEN_ScreenWidth, MAP_SCREEN_ScreenHeight;
static MAP_SCREEN_MasterScreen;

local map_x, map_y, map_dot;

func Initialize()
{
	ScheduleCall(this, this.Initialized, 1);
}

func Initialized()
{
	// No masterscreen?
	if (!MAP_SCREEN_MasterScreen)
	{
		// this is the masterscreen.
		MAP_SCREEN_MasterScreen = this;
		// Getting the landscape width and height.
		GetLandscapeDimensions();
	}
	// Masterscreen is occupied, initializing this screen.
	InitScreen();
	// Only needs the masterscreen
	map_x = MAP_SCREEN_ZoomFactor / 2;
	map_y = MAP_SCREEN_ZoomFactor / 2;
}

/* Slave-functiones */


func InitScreen()
{
	// Adjusting size.
	SetShape(-MAP_SCREEN_ScreenWidth / 2, -MAP_SCREEN_ScreenHeight / 2, MAP_SCREEN_ScreenWidth, MAP_SCREEN_ScreenHeight);
	// Adding frame.
	var frame = AddFrame();
	frame->PanelColor(RGBa(1, 1, 1, 200));
	frame->FrameColor(RGBa(255, 255, 255));
	// Showing the position of the clonks.
	ScheduleCall(this, this.ShowCrew, 1);
	ScreenLandscape();
}

func ScreenLandscape()
{
	// Am I masterscreen?
	if (MAP_SCREEN_MasterScreen != this) return;
	// Saving all existing screens.
	var screens = [];
	screens = FindObjects(Find_ID(GetID()));
	// Scanning three pixels of the landscape.
	for (var j = 0, mat, matC; j < 3; j++)
	{
		mat = GetMaterial(AbsX(map_x), AbsY(map_y));
		matC = RGB(255, 0, 0); //TODO RGB(GetMaterialColor(mat, 1, 0), GetMaterialColor(mat, 1, 1), GetMaterialColor(mat, 1, 2));

		for (var i = 0; i < GetLength(screens); i++)
		screens[i]->DrawPixel(
			(map_x - MAP_SCREEN_ZoomFactor / 2) / MAP_SCREEN_ZoomFactor,
			(map_y - MAP_SCREEN_ZoomFactor / 2) / MAP_SCREEN_ZoomFactor,
			matC);
		// Increasing map_x and map_y.
		map_x += MAP_SCREEN_ZoomFactor;
		if ((map_x - MAP_SCREEN_ZoomFactor / 2) / MAP_SCREEN_ZoomFactor > MAP_SCREEN_ScreenWidth)
		{
			map_x = MAP_SCREEN_ZoomFactor / 2;
			map_y += MAP_SCREEN_ZoomFactor;
			if ((map_y - MAP_SCREEN_ZoomFactor / 2) / MAP_SCREEN_ZoomFactor > MAP_SCREEN_ScreenHeight)
				map_y = MAP_SCREEN_ZoomFactor / 2;
		}
	}
	ScheduleCall(this, this.ScreenLandscape, 1, 1);
}

func DrawPixel(int x, int y, int color)
{
	// Drawing.
	// TODO SetLandscapePixel(-MAP_SCREEN_ScreenWidth/2 + x, -MAP_SCREEN_ScreenHeight/2 + y, color);
}

func ShowCrew()
{
	for (map_dot in FindObjects(Find_OCF(OCF_CrewMember))) 
	{
		if (map_dot)
		{
			// Showing crew member position.
			var x = map_dot->GetX() / MAP_SCREEN_ZoomFactor;
			var y = map_dot->GetY() / MAP_SCREEN_ZoomFactor;
			CreateLEDEffect(map_dot->GetColor(), -MAP_SCREEN_ScreenWidth / 2 + x, -MAP_SCREEN_ScreenHeight / 2 + y, 1, 10);
		}
	}
}

/* Master-functions */

// Only for the masterscreen

func GetLandscapeDimensions()
{
	MAP_SCREEN_ScreenWidth = LandscapeWidth() / MAP_SCREEN_ZoomFactor;
	MAP_SCREEN_ScreenHeight = LandscapeHeight() / MAP_SCREEN_ZoomFactor;
}

local Name = "$Name$";
local Description = "$Description$";
