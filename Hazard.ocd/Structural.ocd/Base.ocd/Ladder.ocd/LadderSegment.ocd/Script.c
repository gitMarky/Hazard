/**
	Ladder Segment

	@author Maikel, Marky
*/

#include Library_Ladder

local index;

// Called from the ladder object to set a master and the segment index.
public func SetMaster(object new_master, int new_index) 
{
	// First perform setting the master in the library function.
	_inherited(new_master, new_index, ...);
	// Then set index and attach to master object.
	index = new_index;
	AddVertex(0, new_master->GetY() - GetY() + new_master->GetTop());
	SetAction("Attach", master);
	// Set graphics
	if (new_index == 0)
	{
		SetGraphics("Part1");
	}
	else
	{
		SetGraphics(Format("Part%d", RandomX(1, 3)));
	}
	SetObjDrawTransform(1000 * (1 - 2 * master.dir), 0, 0, 0, 1000);
}

// Returns whether the ladder can be climbed.
public func CanNotBeClimbed(bool is_climbing, object clonk)
{
	var test_height = 10;
	if (is_climbing) test_height = 8;
	if (GBackSolid(1, test_height) && GBackSolid(-1, test_height)) 
		return true;
	if (master->~CanNotBeClimbed(is_climbing, clonk))
		return true;
	return false;
}

// Returns the segment (start x, start y, end x, end y, angle) on which the clonk can climb.
// The coordinate value must be specified with a precision of a 1000.
public func GetLadderData()
{
	var precision = 1000;
	var y = GetDefHeight() / 2;

	return [
		GetX(precision),
		GetY(precision) + y * precision,
		GetX(precision),
		GetY(precision) - y * precision,
		0
	];
}

public func OnLadderGrab(object clonk)
{
	if (master)
		master->OnLadderGrab(clonk, this, index);
}

public func OnLadderClimb(object clonk)
{
	if (master)
		master->OnLadderClimb(clonk, this, index);
}

public func OnLadderReleased(object clonk)
{
	if (master)
		master->OnLadderReleased(clonk, this, index);
}

// Main ladder object is saved.
public func SaveScenarioObject() { return false; }


/*-- Properties --*/

local ActMap = {
	Attach = {
		Prototype = Action,
		Name = "Attach",
		Procedure = DFA_ATTACH,
		FacetBase = true,
	},
};
