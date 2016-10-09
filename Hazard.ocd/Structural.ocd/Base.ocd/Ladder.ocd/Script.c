
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Properties

local Name = "$Name$";
local Description = "$Description$";
local segments;
local height;
local dir;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ladder control


public func LadderHeight(int y_top, int y_bottom)
{
	if (y_bottom <= y_top)
	{
		FatalError(Format("Ladder end (y = %d) must be below ladder start (y = %d)!", y_bottom, y_top));
	}
	if (segments != nil)
	{
		FatalError("This function should not be called, because the ladder already has segments.");
	}
	
	var diff = y_top - GetY() - GetTop();
	MovePosition(0, diff);

	this.height = y_bottom - y_top;
	CreateSegments();
	return this;
}


public func LadderDirection(int direction)
{
	dir = direction;
	return this;
}


// Creates the segments that control the climbing.
private func CreateSegments()
{
	segments = [];
	var segment_height = LadderSegment->GetDefHeight();
	var nr_segments = height / segment_height;

	for (var index = 0; index < nr_segments; index++)
	{
		var y = GetTop() + index * segment_height;

		var segment = CreateObject(LadderSegment, 0, y + segment_height / 2);
		segment->SetMaster(this, index);

		// Store the segments.
		PushBack(segments, segment);

		// Set next and previous segment for climbing control.
		if (index > 0)
		{
			segments[index - 1]->SetPreviousLadder(segment);
			segment->SetNextLadder(segments[index - 1]);		
		}
	}
}


// Callback by the ladder climb library when the ladder is grabbed.
public func OnLadderGrab(object clonk, object segment, int segment_index)
{
	segment->Sound("Hits::Materials::Metal::DullMetalHit?");
}


// Callback by the ladder climb library when the lader is climbed.
public func OnLadderClimb(object clonk, object segment, int segment_index)
{
}


// Callback by the ladder climb library when the ladder is released.
public func OnLadderReleased(object clonk, object segment, int segment_index)
{
}


// Callback by the ladder segment when a clonk tries to grab it.
public func CanNotBeClimbed(bool is_climbing, object clonk)
{
	if (clonk && dir)
	{
		return clonk->GetDir() != dir;
	}
	return false;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Saving

// Save placed ladder segments in scenarios.
public func SaveScenarioObject(props)
{
	if (!inherited(props, ...)) 
		return false;
	props->AddCall("LadderHeight", this, "LadderHeight", GetTop(), height);
	if (dir) props->AddCall("LadderDirection", this, "LadderDirection", dir);
	props->AddCall("CreateSegments", this, "CreateSegments");
	return true;
}
