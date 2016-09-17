/*-- Map shower --*/
static const MAP_ZoomFactor = 10;
static MAP_ScreenWidth, MAP_ScreenHeight;
static MAP_MasterScreen;

local MapX, MapY, lClonk;

protected func Initialize()
{
  // Waiting
  ScheduleCall(this, "Initialized", 1);
}

protected func Initialized()
{
  // No masterscreen?
  if(!MAP_MasterScreen)
    {
    // this is the masterscreen.
    MAP_MasterScreen = this;
    // Getting the landscape width and height.
    LandscapeWH();
    }
  // Masterscreen is occupied, initializing this screen.
  InitScreen();
  // Only needs the masterscreen
  MapX = MAP_ZoomFactor / 2;
  MapY = MAP_ZoomFactor / 2;
}

/* Slave-functiones */


private func InitScreen()
{
  // Adjusting size.
  SetShape(-MAP_ScreenWidth/2, -MAP_ScreenHeight/2, MAP_ScreenWidth, MAP_ScreenHeight);
  // Adding frame.
  var pFrame = AddFrame();
  pFrame->PanelColor(RGBa(1,1,1,200));
  pFrame->FrameColor(RGBa(255,255,255));
  // Showing the position of the clonks.
  ScheduleCall(this, "ShowClonks", 1);
}

private func ScreenLandscape()
{
  // No masterscreen?
  if(!MAP_MasterScreen)
    MAP_MasterScreen = this;
  // Am I masterscreen?
  if(MAP_MasterScreen != this)
    return;
  // Saving all existing screens.
  var screens = CreateArray();
  screens = FindObjects(Find_ID(GetID()));
  // Scanning three pixels of the landscape.
  for(var j=0,mat,matC ; j<3 ; j++)
    {
    mat = GetMaterial(AbsX(MapX), AbsY(MapY));
    matC = RGB(255, 0, 0); //TODO RGB(GetMaterialColor(mat, 1, 0), GetMaterialColor(mat, 1, 1), GetMaterialColor(mat, 1, 2));
    
    for(var i=0 ; i < GetLength(screens) ; i++)
      screens[i]->DrawPixel((MapX-MAP_ZoomFactor/2) / MAP_ZoomFactor, (MapY-MAP_ZoomFactor/2) / MAP_ZoomFactor, matC);
    // Increasing MapX and MapY.
    MapX += MAP_ZoomFactor;
    if((MapX-MAP_ZoomFactor/2) / MAP_ZoomFactor > MAP_ScreenWidth)
      {
      MapX = MAP_ZoomFactor / 2;
      MapY += MAP_ZoomFactor;
      if((MapY-MAP_ZoomFactor/2) / MAP_ZoomFactor > MAP_ScreenHeight)
        MapY = MAP_ZoomFactor / 2;
      }
    }
}

public func DrawPixel(int iX, int iY, int Color)
{
  // Drawing.
  // TODO SetLandscapePixel(-MAP_ScreenWidth/2 + iX, -MAP_ScreenHeight/2 + iY, Color);
}

protected func ShowClonks()
{
    for(lClonk in FindObjects(Find_OCF(OCF_CrewMember)))
    {
        if(lClonk)
        {
            // Showing clonk position.
            var iX = lClonk->GetX() / MAP_ZoomFactor;
            var iY = lClonk->GetY() / MAP_ZoomFactor;
            CreateParticle("MapDot", -MAP_ScreenWidth/2 + iX, -MAP_ScreenHeight/2 + iY, 0, 0, 10, );// TODO GetColor(lClonk));
        }
    }
}

/* Master-functions */

// Only for the masterscreen

private func LandscapeWH()
{
  MAP_ScreenWidth = LandscapeWidth() / MAP_ZoomFactor;
  MAP_ScreenHeight = LandscapeHeight() / MAP_ZoomFactor;
}
local Name = "$Name$";
local Description = "$Description$";
