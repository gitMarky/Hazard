/** Base object for other rails

Single rail parts get an index and can, theoretically, be
combined to your liking, as long as the following criteria 
are fulfilled:
- Index 0 is the left end
- Index 1+ is a middle part, but not a support
- Index n = last index is the right end
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// constants

// has support beams in regular positions, as long as the rail supports supports (this is not a typo :p)
static const RAIL_Supported = 1;		

static const RAIL_LeftOpen = 2;			// no support at the left end
static const RAIL_RightOpen = 4;		// no support at the right end

static const RAIL_AltLinkage = 8;		// alternate graphics style, if available



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Plane = 999;

local rail_length;	// length of the rail, in rail elements
local rail_part_type; // array that saves the rail parts


func Index(int index)
{
	FatalError("Implement this function: Map an index, such as Left(), to an action name");
}

// value of -1: not supported; this is to be overloaded by the individual rails
func Left() {        return -1;}
func Right(){        return -1;}
func Linkage(int i){ return -1;}
func Backing(){      return -1;}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// public interface

/**
 The easiest way for setting up a rail.
 
 @par length the rail length, in rail elements
 @par modifier modifier for the rail elements, for skipping an end for example
 */
func SetRailLength(int length, int modifier)
{
	ClearRail();

	rail_part_type = CreateArray();
	
	var part_index = 0;
	// set left end, if there is no modifier
	if (!(modifier & RAIL_LeftOpen))
	{
		rail_part_type[part_index++] = Left();
	}
	else
	{
		length--;
	}
	
	var support = false, now = false;
	if ((modifier & RAIL_Supported) && (Backing() != -1))
	{
		support = true;
	}
	
	while (part_index <= length)
	{
		if (support && now)
		{
			rail_part_type[part_index] = Backing();
			now = false;
			length++;
		}
		else
		{
			if (modifier & RAIL_AltLinkage)
			{
				rail_part_type[part_index] = Linkage(1);
			}
			else
			{
				rail_part_type[part_index] = Linkage(0);
			}
			now = true;
		}
		part_index++;
	}
	
	// set right end, if there is no modifier
	if (!(modifier & RAIL_RightOpen))
		rail_part_type[GetLength(rail_part_type)] = Right();

	DrawRail();
}

/**
 Sets a sequence of rail parts, end parts are added automatically
 
 @par parts An array containing the rail part indices.
 @par do_not_add_end_parts If set to {@c true} then the end parts will not be added.
 */
func SetRail(array parts, bool do_not_add_end_parts)
{
	ClearRail();

	rail_part_type = [];

	var part_index = 0, j = 0;
	if (!do_not_add_end_parts) rail_part_type[part_index++] = Left();

	for (; j < GetLength(parts); part_index++)
	{
		rail_part_type[part_index] = parts[j++];
	}

	if (!do_not_add_end_parts) rail_part_type[GetLength(rail_part_type)] = Right();

	DrawRail();
}


/**
 Use this to manipulate single parts of the rail
 
 @par part_index This part will be modified, starting with 0.
 @par new_index The index of the new appearance for that part.
 */
func AdjustPart(int part_index, int new_index)
{
	// check the parameters
	if (GetLength(rail_part_type) <= part_index || part_index < 0)
	{
		FatalError(Format("The part index %d must satisfy 0 <= part_index <= %d", part_index, GetLength(rail_part_type)));
	}

	ClearRail();
	rail_part_type[part_index] = new_index;
	DrawRail();
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// internals


func Initialize()
{
	// set a default size and draw the rail
	rail_part_type = [];
	rail_part_type = [Left(), Linkage(), Right()];
	DrawRail();
}

/**
 Draws the rail
 */
func DrawRail()
{
	var total_length = 0; // total length in pixels
	rail_length = GetLength(rail_part_type);
	// add single parts
	for (var part_index = 0, action, part_length; part_index < rail_length; part_index++)
	{
		var overlay = part_index + 1;
		// save action
		action = Index(rail_part_type[part_index]);
		// get part length
		part_length = this.ActMap[action].Wdt; //GetActMapVal("Facet", action, GetID(), 2);
		// set graphics and transform to the relevant position
		SetGraphics("Rail", GetID(), overlay, 2, action);
		SetObjDrawTransform(1000, 0, 1000 * (part_length / 2 + total_length), 0, 1000, 0, overlay);
		// add size to total length
		total_length += part_length;
	}
	SetShape(0, -this->GetObjHeight() / 2, total_length, this->GetObjHeight());
}


func ClearRail()
{
	for (var part_index = 0; part_index < GetLength(rail_part_type); part_index++)
		SetGraphics("", this, 0, part_index + 1);
}


func UpdateTransferZone()
{
	ClearRail();
	DrawRail();
}

/* Serialization */

func Serialize(array extra) // TODO: implement saving object correctly
{
	extra[GetLength(extra)] = Format("SetRail(%v,1)", rail_part_type);
}
