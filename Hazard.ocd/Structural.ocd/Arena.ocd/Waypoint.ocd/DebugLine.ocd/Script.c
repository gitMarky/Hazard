/*-- Debug display line --*/

local Visibility = VIS_Editor;

// definition call: create line
func Create(int x1, int y1, int x2, int y2, int clr)
{
	var line = CreateObject(DebugLine);
	line->Set(x1, y1, x2, y2, clr);
	return line;
}

func Connect(object target1, object target2, int clr, int yoff)
{
	return Create(target1->GetX(), target1->GetY() + yoff, target2->GetX(), target2->GetY(), clr);
}

func Set(int x1, int y1, int x2, int y2, int clr)
{
	//SetAction("Connect");
	SetVertexXY(0, x1, y1);
	SetVertexXY(1, x2, y2);
	this.LineColors = [clr, clr];
	return;
}

// Will be recreated when needed.
func SaveScenarioObject() { return false; }

local ActMap = {
	Connect = {
		Prototype = Action,
		Name = "Connect",
		Procedure = DFA_CONNECT,
		NextAction = "Connect"
	}
};



