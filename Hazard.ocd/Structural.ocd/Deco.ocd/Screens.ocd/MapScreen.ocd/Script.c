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
	// Only needed by the masterscreen
	map_x = MAP_SCREEN_ZoomFactor / 2;
	map_y = MAP_SCREEN_ZoomFactor / 2;
}

/* Slave-functiones */


func InitScreen()
{
	// Adjusting size.
	SetShape(-MAP_SCREEN_ScreenWidth / 2, -MAP_SCREEN_ScreenHeight / 2, MAP_SCREEN_ScreenWidth, MAP_SCREEN_ScreenHeight);
	// Draw black screen.
	for (var x = 0; x < MAP_SCREEN_ScreenWidth; ++x)
	for (var y = 0; y < MAP_SCREEN_ScreenHeight; ++y)
	{
		InitPixel(x, y);
		DrawPixel(x, y, RGB(0, 0, 0));
	}
	// Adding frame.
	var frame = AddFrame();
	frame->PanelColor(RGBa(1, 1, 1, 200));
	frame->FrameColor(RGBa(255, 255, 255));
	// Showing the position of the clonks.
	ScheduleCall(this, this.ShowCrew, 1);
	ShowLandscape();
	ScreenLandscape();
}

func ShowLandscape()
{
	// Only the master screen does this
	if (MAP_SCREEN_MasterScreen != this) return;
	// Draw the whole landscape
	for (var x = 0; x < LandscapeWidth(); x += MAP_SCREEN_ZoomFactor)
	for (var y = 0; y < LandscapeHeight(); y += MAP_SCREEN_ZoomFactor)
	{
		DrawLandscape(x, y);
	}
}

func ScreenLandscape()
{
	// Am I masterscreen?
	if (MAP_SCREEN_MasterScreen != this) return;
	// Scanning three pixels of the landscape.
	for (var j = 0; j < 3; j++)
	{
		DrawLandscape(map_x, map_y);
		// Determine next pixel
		map_x += MAP_SCREEN_ZoomFactor;
		if (map_x > LandscapeWidth())
		{
			map_x = 0;
			map_y += MAP_SCREEN_ZoomFactor;
			if (map_y > LandscapeHeight())
			{
				map_y = 0;
			}
		}
	}
	ScheduleCall(this, this.ScreenLandscape, 1, 1);
}

func DrawLandscape(int global_x, int global_y)
{
	var texture = GetTexture(global_x - GetX(), global_y - GetY());
	var color = GetAverageTextureColor(texture);
	UpdatePixel(global_x / MAP_SCREEN_ZoomFactor, global_y / MAP_SCREEN_ZoomFactor, color);
}

func InitPixel(int x, int y)
{
	var overlay = GetPixelOverlay(x, y);
	SetGraphics("Pixel", GetID(), overlay, GFXOV_MODE_Base);
	SetObjDrawTransform(1000, 0, (x - MAP_SCREEN_ScreenWidth / 2) * 1000, 0, 1000, (y - MAP_SCREEN_ScreenHeight / 2) * 1000, overlay);
}

func UpdatePixel(int x, int y, int color)
{
	var screens = FindObjects(Find_ID(GetID()));
	for (var screen in screens)
	{
		screen->DrawPixel(x, y, color);
	}
}

func DrawPixel(int x, int y, int color)
{
	SetClrModulation(color, GetPixelOverlay(x, y));
}

func ShowCrew()
{
	var lifetime = 10;
	for (map_dot in FindObjects(Find_OCF(OCF_CrewMember))) 
	{
		if (map_dot)
		{
			// Showing crew member position.
			var x = map_dot->GetX() / MAP_SCREEN_ZoomFactor;
			var y = map_dot->GetY() / MAP_SCREEN_ZoomFactor;
			CreateLEDEffect(map_dot->GetColor(), x - MAP_SCREEN_ScreenWidth / 2, y - MAP_SCREEN_ScreenHeight / 2, 2, lifetime * 2);
		}
	}
	ScheduleCall(this, this.ShowCrew, lifetime);
}

func GetPixelOverlay(int x, int y)
{
	return 1 + x + y * MAP_SCREEN_ScreenWidth;
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
