/* Context Use equipment functionality */
/* Ausrüstungssteuerung */

/*
   Objekte die die volle Funktionalität benutzen wollen müssen folgende Dinge
   sicherstellen... Bis auf das erste sind alle optional. Falls definiert:
   
   * In "Construction" _inherited() aufrufen 
   
   * In "OnDmg" _inherited() aufrufen und den Rückgabewert zum eigenen
     Rückgabewert hinzuaddieren
     [falls die Ausrüstung genommenen Schaden modifizieren können soll
      z.B. die Rüstung]
     
   * In "OnHit" _inherited() aufrufen
     [falls Ausrüstung Effekte nach Schaden machen können soll
      (z.B. Aufblinken des Schildgenerators)]

   * In "Death" _inherited() aufrufen
     [falls der Clonk bei Tod die Ausrüstung fallen lassen soll]

*/


local lib_gear;

/* An Objekt ranhängen... */

// Array erstellen
func Initialize()
{
	lib_gear = [];
	_inherited(...);
}

// Ausrüstung fallenlassen
func Death()
{
	if (HasGear())
		TakeOffGear();
	_inherited(...);
}

// Ermöglicht die Modifikation des Schadens für das Objekt durch die Ausrüstung
func OnDmg(int iDamage, int iType)
{
	var before = _inherited(iDamage, iType);
	
	var add = before;
	var gear;
	for (gear in lib_gear) 
	{
		// not null...
		if (gear)
		{
			add += (gear->~OnClonkDmg(iDamage, iType, this));
		}
	}
	return add;
}

// Effekte o.Ä. anzeigen
func OnHit(int iDmg, int iType, object pFrom)
{
	_inherited(iDmg, iType, pFrom);
	
	// Ausrüstung will vielleicht mitreden...
	for (var gear in lib_gear) 
		if (gear)
			gear->~OnClonkHit(iDmg, iType, this);
}

/* Kontext menü */

// Ausrüstung benutzen
func ContextUseEquipment(object caller)
{
// TODO	[$CtxUseEquipmentDesc$|Image=HARM|Condition=HasUsableGear]
	if (!HasUsableGear()) return;
	CreateMenu(HARM, this, nil, nil, nil, C4MN_Style_Context);
	// nutzbare Ausrüstung anzeigen
	for (var i = 0; i < GetLength(lib_gear); ++i)
	{
		var gear = lib_gear[i];
		if (gear)
			if (gear->~ConUseable())
				AddMenuItem(gear->ConDesc(), "UseEquipment", gear->GetID(), nil, i);
	}
	return true;
}

// Ausrüstung ablegen
func ContextUnbuckle(object caller)
{
// TODO	[$CtxUnbuckleDesc$|Image=HARM|Condition=FunnyBug]
	if (!HasGear()) return;
	CreateMenu(HARM, this, nil, nil, nil, C4MN_Style_Context);
	// alle Ausrüstung anzeigen
	for (var i; i < GetLength(lib_gear); ++i)
	{
		var gear = lib_gear[i];
		if (gear)
			AddMenuItem("$CtxUnbuckleItem$", Format("TakeOffGear(0,%d)", i), gear->GetID());
	}
	return true;
}


/* Statusfunktionen */

// Objekt hat eine Ausrüstung angelegt die man benutzen kann
func HasUsableGear()
{
	// gibt true zurück wenn mindestens eine Ausrüstung
	// vorhanden ist, die per Kontextmenü nutzbar ist
	var gear;
	for (gear in lib_gear) 
	{
		if (gear)
			if (gear->~ConUseable())
				return true;
	}
}

// Objekt hat eine Ausrüstung des Typs iGearType angelegt
//   alternativ kann man per idGear auch nach einer bestimmten
//   Ausrüstung suchen. Ohne Parameter = irgendeine ausrüstung angelegt
func HasGear(gear_type)
{
	// nach bestimmter ID suchen
	var gear;
	if (GetType(gear_type) == C4V_Def)
	{
		for (gear in lib_gear)
		{ 
			if (gear && gear->GetID() == gear_type)
					return gear;
		}
		return false;
	}
	
	// nach bestimmtem Typ suchen
	if (GetType(gear_type) == C4V_Int)
	{
		if (lib_gear[gear_type])
			return true;
		return false;
	}

	// keine Parameter: allgemein ob Ausrüstung da ist
	if (gear_type == nil)
	{
		for (gear in lib_gear) 
			if (gear)
				return true;
	}
	return false;
}

func CanUse(id def)
{
	if (def->~IsHazardGear())
		return true;
	return _inherited(def);
}



/* Benutzen */

// Ausrüstung benutzen
func UseEquipment(id bla, int i)
{
	if (lib_gear[i])
		lib_gear[i]->ConUse(this);
}


// Ausrüstung ablegen
func TakeOffGear(object pGear, int iGearType)
{
	var geartype = iGearType;
	
	// man kann auch statt iGearType das konkrete Objekt angeben
	if (!geartype)
	{
		
		// ohne Parameter = alles runter
		if (!pGear)
		{
			var i;
			for (var i = 0; i < GetLength(lib_gear); ++i)
				if (lib_gear[i])
					TakeOffGear(nil, i);
			return 1;
		}
		
		geartype = pGear->GetGearType();
		// das Objekt ist nicht angelegt
		if (lib_gear[geartype] != pGear)
			return 0;
	}
	else
	{
		// angegebener geartype garnicht angelegt 
		if (!HasGear(geartype))
			return 0;
	}
	
	// er ist angelegt: ok, ablegen
	lib_gear[geartype]->GearUnbuckle(this);
	
	// aufsammeln wenn möglich
	if (lib_gear[geartype])
		Collect(lib_gear[geartype]);
	
	// und löschen
	lib_gear[geartype] = 0;
}


// Ausrüstung anlegen
func EquipGear(object pGear)
{
	// überhaupt benutzbar
	if (!pGear) return false;
	if (!CanUse(pGear)) return false;
	// schon eine Ausrüstung dieses Typs am Clonk
	var geartype = pGear->GetGearType();
	if (HasGear(geartype)) return false;

	// ok:
	// speichern
	lib_gear[geartype] = pGear;
	// Auslösen
	return true;
}

