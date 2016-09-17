
static const LIGHT_COLOR_SCREEN = 0xffd2ffe6;
static const LIGHT_COLOR_NEON = 0xfff2fff8;
static const LIGHT_COLOR_TELEPORT = 0xff64dcff;
static const LIGHT_COLOR_EMP = 0xff64dcff;
static const LIGHT_COLOR_EMP_SHOCK = 0xff3282ff;
static const LIGHT_COLOR_LASER = 0xffff0000;
static const LIGHT_COLOR_LAMP = 0xffffffdc;

static const LIGHT_CONE_Prec = 1000;
static const LIGHT_CONE_MinRadius = 2;
static const LIGHT_CONE_MinRange = 20;

global func AddLightAmbience(int radius)
{
	if (!this) FatalError("This function has to be called from object context");
	
	SetLightRange(radius, 3 * radius / 4);
}

global func RemoveLight()
{
	if (!this) FatalError("This function has to be called from object context");

	SetLightRange(0);
}

global func GetLightCone()
{
	AssertObjectContext("GetLightCone()");
	
	return GetEffect("IntLightCone", this);
}

global func AddLightCone(int radius, int angle, int opening_angle, int color)
{
	AssertObjectContext("AddLightCone()");	

	var cone = GetLightCone();
	cone = cone ?? AddEffect("IntLightCone", this, 1, 0, nil, nil, radius ?? 100, angle ?? 0, opening_angle ?? 30, color ?? LIGHT_COLOR_LAMP);
}

global func RemoveLightCone()
{
	AssertObjectContext("RemoveLightCone()");
	
	var cone = GetLightCone();
	if (cone) ClearLightCone(cone);
}

global func FxIntLightConeStart(object target, proplist cone, temp, int radius, int angle, int opening_angle, int color)
{
	cone.radius = radius;
	cone.angle = angle;
	cone.width = opening_angle;
	cone.color = color;
	cone.spots = [];
	cone.factor = BoundBy(LIGHT_CONE_Prec - Sin(cone.width, LIGHT_CONE_Prec), 1, LIGHT_CONE_Prec - 1);

	CreateLightCone(cone);
	target->DrawLightCone(cone);
}

global func CreateLightCone(proplist cone)
{
	if (GetLength(cone.spots) > 0)
	{
		ClearLightCone(cone);
	}

	// create helper objects
	var spot_distance = cone.radius;
	var spot_intensity = RGBA_MAX / 5;
	//var i = 0;
	
	while (true) // i < 100)
	{
		var spot_radius = spot_distance * Sin(cone.width, LIGHT_CONE_Prec) / LIGHT_CONE_Prec;		
		
		if (spot_radius < LIGHT_CONE_MinRadius)
		{
			break;
		}
		else
		{
			var spot = CreateObject(Dummy, 0, 0, NO_OWNER);
			spot.Visibility = VIS_All;

			var light_spot = {
				center = spot,
				distance = spot_distance,
				radius = spot_radius,
				intensity = spot_intensity,
			};
			
			//Log("Adding light spot at %d %d %d", spot_distance, spot_radius, spot_intensity);
			
			PushFront(cone.spots, light_spot);
		}
		
		// update size
		spot_distance = spot_distance * cone.factor / LIGHT_CONE_Prec;
		//spot_intensity = BoundBy(spot_intensity * LIGHT_CONE_Prec / cone.factor, 0, RGBA_MAX); 
		spot_intensity = BoundBy(spot_intensity * cone.radius / light_spot.distance, 0, RGBA_MAX); 
		//i += 1;
	}
}

global func ClearLightCone(proplist cone)
{
	for (var light_spot in cone.spots)
	{
		if (light_spot.center) light_spot.center->RemoveObject();
	}
	
	cone.spots = [];
	RemoveEffect(nil, this, cone);
}

global func DrawLightCone(proplist cone)
{
	AssertObjectContext("DrawLightCone()");
	
	var path_free = true;
	
	for (var light_spot in cone.spots)
	{
		var x = GetX() + Sin(cone.angle, light_spot.distance); 
		var y = GetY() - Cos(cone.angle, light_spot.distance); 
		light_spot.center->SetPosition(x, y);

		if (light_spot.center->GBackSolid())
		{
			path_free = false;
		}

		if (path_free)
		{
			var r = light_spot.intensity * GetRGBaValue(cone.color, RGBA_RED) / RGBA_MAX;
			var g = light_spot.intensity * GetRGBaValue(cone.color, RGBA_GREEN) / RGBA_MAX;
			var b = light_spot.intensity * GetRGBaValue(cone.color, RGBA_BLUE) / RGBA_MAX;
			
			//Log("Light color: %d, %d, %d, of %d", r, g, b, cone.color);
	
			var range = Max(light_spot.radius, LIGHT_CONE_MinRange);
			light_spot.center->SetLightRange(range, range * 2);
			light_spot.center->SetLightColor(RGB(r, g, b));
		}
		else
		{
			light_spot.center->RemoveLight();
		}
	}
}