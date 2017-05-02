
local iDir, iPos;   // iDir: welches Tor als nächstes geöffnet wird;
            // iPos: ob es die linke oder rechte Schleuse ist


public func SetLeft()  { iPos = -1; }
public func SetRight() { iPos = +1; }

protected func Initialize() { SetAction("Pump"); Close(); }


protected func Check()          // öffnet je nach Bedarf die Schleusen
{
  // will jemand aus der Schleuse raus?
  if(iDir == -1) return(SetAction("OpenLeft"));
  if(iDir == +1) return(SetAction("OpenRight"));

  // will jemand in die Schleuse rein? Hierbei haben alle die Vorrang, die von draußen (=Wasser) kommen
  if(iPos == -1) {
    if(Check4Clonk(-1)) return(SetAction("OpenLeft"));
    if(Check4Clonk(+1)) return(SetAction("OpenRight"));
  }
  else {
    if(Check4Clonk(+1)) return(SetAction("OpenRight"));
    if(Check4Clonk(-1)) return(SetAction("OpenLeft"));
  }
}

protected func WannaClose()     // soll Pumpen einschalten, will aber keine Clonks zerquetschen
{
  var iActDir;
  if(GetAction() eq "LeftOpen") iActDir = -1; else iActDir = +1;

  // Clonks gefunden: offen lassen
  if(Check4Clonk(iActDir)) return();

  // Clonks in der Schleuse
  if(Check4Clonk(0))
  {
    // Schleuse hat zum Passieren geöffnet: Warten bis der Clonk raus ist
    if(iDir) return();
    // ansonsten schließen damit geschleust werden kann
    iDir = -iActDir;
  }
  else iDir = 0;

  // schließen
  if(iActDir == -1) return(SetAction("CloseLeft"));
  if(iActDir == +1) return(SetAction("CloseRight"));
}

protected func Pumping()        // alles dicht: abpumpen
{
  DigFreeRect(GetX()-20,GetY()-17,40,35);

  for(var j=0;j<30;++j)
    InsertMaterial(ExtractLiquid(0,RandomX(13,15)),40*iPos,0);

  // genug gepumpt?
  for(var i=-14; i<16; ++i)
    if(GBackLiquid(0,i))
      return();
  // jupp!
  SetAction("Wait");
}

protected func SoundOpen()  { Sound("Airlock1"); }
protected func SoundClose() { Sound("Airlock2"); }

private func Check4Clonk(int iD)    // sucht nach nicht verfeindeten Clonks die gerne rein oder raus möchten
{
  var pClonk;
  while(pClonk = FindObject(0,iD*30-20,-20,40,40,OCF_CrewMember(),0,0,NoContainer(),pClonk))
    if(!Hostile(GetOwner(pClonk),GetOwner()))
      // bingo!
        return(true);
  // niemand da
  return(false);
}

protected func LeftOpen()  { SetSolidMask(120,0,40,35); }
protected func RightOpen() { SetSolidMask(160,0,40,35); }
protected func Close()     { SetSolidMask(80,0,40,35);  }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Components = METL=3;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Wait = {
	Prototype = Action,
	Name = "Wait",
	Procedure = DFA_FLOAT,
	Delay = 37,
	X = 0,
	Y = 0,
	Wdt = 40,
	Hgt = 35,
	OffX = 0,
	OffY = 0,
	FacetBase = 0,
	FacetTopFace = 0,
	NextAction = "Wait",
	StartCall = "Check",
},

Pump = {
	Prototype = Action,
	Name = "Pump",
	Procedure = DFA_FLOAT,
	Length = 10,
	Delay = 2,
	X = 0,
	Y = 105,
	Wdt = 40,
	Hgt = 35,
	FacetBase = 0,
	FacetTopFace = 0,
	NextAction = "Pump",
	PhaseCall = "Pumping",
	Sound = "Research",
},

OpenLeft = {
	Prototype = Action,
	Name = "OpenLeft",
	Procedure = DFA_FLOAT,
	Length = 10,
	Delay = 2,
	X = 0,
	Y = 35,
	Wdt = 40,
	Hgt = 35,
	FacetBase = 0,
	FacetTopFace = 0,
	NextAction = "LeftOpen",
	StartCall = "SoundOpen",
	EndCall = "LeftOpen",
},

LeftOpen = {
	Prototype = Action,
	Name = "LeftOpen",
	Procedure = DFA_FLOAT,
	Length = 1,
	Delay = 35,
	X = 360,
	Y = 35,
	Wdt = 40,
	Hgt = 35,
	FacetBase = 0,
	FacetTopFace = 0,
	NextAction = "LeftOpen",
	EndCall = "WannaClose",
},

CloseLeft = {
	Prototype = Action,
	Name = "CloseLeft",
	Procedure = DFA_FLOAT,
	Length = 10,
	Reverse = 1,
	Delay = 1,
	X = 0,
	Y = 35,
	Wdt = 40,
	Hgt = 35,
	FacetBase = 0,
	FacetTopFace = 0,
	NextAction = "Pump",
	StartCall = "Close",
	EndCall = "SoundClose",
},

OpenRight = {
	Prototype = Action,
	Name = "OpenRight",
	Procedure = DFA_FLOAT,
	Length = 10,
	Delay = 2,
	X = 0,
	Y = 70,
	Wdt = 40,
	Hgt = 35,
	FacetBase = 0,
	FacetTopFace = 0,
	NextAction = "RightOpen",
	StartCall = "SoundOpen",
	EndCall = "RightOpen",
},

RightOpen = {
	Prototype = Action,
	Name = "RightOpen",
	Procedure = DFA_FLOAT,
	Length = 1,
	Delay = 35,
	X = 360,
	Y = 70,
	Wdt = 40,
	Hgt = 35,
	FacetBase = 0,
	FacetTopFace = 0,
	NextAction = "RightOpen",
	EndCall = "WannaClose",
},

CloseRight = {
	Prototype = Action,
	Name = "CloseRight",
	Procedure = DFA_FLOAT,
	Length = 10,
	Reverse = 1,
	Delay = 1,
	X = 0,
	Y = 70,
	Wdt = 40,
	Hgt = 35,
	FacetBase = 0,
	FacetTopFace = 0,
	NextAction = "Pump",
	StartCall = "Close",
	EndCall = "SoundClose",
},

};
