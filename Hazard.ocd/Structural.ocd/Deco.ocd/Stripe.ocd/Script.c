
func Initialize()
{
	SetWidth(100);
	SetColor(RGB(200, 200, 200));
}


func SetWidth(int width)
{
	this.width = width;
	Redraw();
	return this;
}


func SetSkew(int dir)
{
	this.dir = dir;
	Redraw();
	return this;
}


func Redraw()
{
	SetShape(-width / 2, -4, width, 8);
	
	var current_width = width;
	if (dir != 0)  current_width -= 8;
	
	var w = 1000 * current_width / 8;
	
	SetObjDrawTransform(w, dir * 1000, 0, 0, 1000);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local width, dir;
local Name = "$Name$";
local Description = "$Description$";
