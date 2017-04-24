/*-- Waffenautomat --*/


//tolle Waffenliste!
local aWare;
local aCount;

func Initialize()
{
	aWare = [];
	aCount = [];
}

//Ware anzeigen
func Display()
{
	//haben wir ueberhaupt Ware?
	if (!GetLength(aWare))
		return SetGraphics(0, 0, 0, 1);
	
	var i = Random(GetLength(aWare));
	SetGraphics(0, this, aWare[i], 1, GFXOV_MODE_IngamePicture, 0, 1);
	if (!aCount[i])
		SetClrModulation(RGB(150, 100, 100), 0, 1);
	
	SetObjDrawTransform(218, 0, -16000, 0, 203, -6000, 0, 1);
}

func SortWare()
{
	if (GetLength(aWare) != GetLength(aCount))
		return Log("Waffenautomat-PANICK. Den Devs melden!");
	
	var length;
	while (Par(length++));
	
	var ware = [], count = [];
	
	//Nach Kategorie sortieren
	for (var y = 0; y < length; y++)
	{
		ware[y] = CreateArray();
		count[y] = CreateArray();
		for (var x = 0; x < GetLength(aWare); x++)
		{
			if (aWare[x]->Call(Par(y)))
			{
				PushBack(ware[y], aWare[x]);
				PushBack(count[y], aCount[x]);
			}
		}
	}
	
	//Nach Preis sortieren
	for (var y = 0; y < length; y++)
	{
		for (var x = 0; x < GetLength(ware[y]); x++)
		{
			for (var z = x + 1; z < GetLength(ware[y]); z++)
			{
				if (GetDefValue(ware[y][z]) < GetDefValue(ware[y][x]))
				{
					var tmp = ware[y][x];
					ware[y][x] = ware[y][z];
					ware[y][z] = tmp;
					tmp = count[y][x];
					count[y][x] = count[y][z];
					count[y][z] = tmp;
				}
			}
		}
	}
	
	//Wieder sortiert ins Array tun
	aWare = aCount = CreateArray();
	var cnt;
	for (var y = 0; y < length; y++)
	{
		for (var x = 0; x < GetLength(ware[y]); x++)
		{
			aWare[cnt] = ware[y][x];
			aCount[cnt] = count[y][x];
			cnt++;
		}
	}
}


/* Menuezeugs */

func ControlDigDouble(object pByObj)
{
	if (!GetLength(aWare))
		return 0;
	CreateBuyMenu(pByObj);
}

func CreateBuyMenu(object pClonk)
{
	if (!pClonk)
		return 0;
	CreateMenu(WPVM, pClonk, this, 0, 0, 0, 0, 1);
	for (var x; x < GetLength(aWare); x++)
		AddBuyMenuItem(aWare[x], pClonk, aCount[x]);
}

func AddBuyMenuItem(id id, object pClonk, int iCount)
{
	//bei NoAmmo-Regel Munition nicht anzeigen
	if (id->~IsAmmoPacket() && NoAmmo())
		return;
	
	if (!id || !pClonk)
		return;
	// noch mehr Variablen
	var name = GetName(0, id), obj = CreateObject(id), wealth = GetDefValue(id), iPlayer = GetOwner(pClonk), bMoney = false;
	
	//Kann sich der Spieler die Waffe leisten?
	if (GetWealth(iPlayer) < wealth || iCount == 0)
	{
		name = Format("<c 646464>%s</c>", name);
		obj->SetClrModulation(RGB(100, 100, 100));
		bMoney = true;
	}
	
	//Hiermit koennen andere sachen, die den Waffenautomaten includen, noch Grafisches Zeugs mit den Icons machen
	this->~AdaptMenuItem(obj, iPlayer);
	
	var description = id->GetDesc();
	
	var info = 4;
	
	//hinzufuegen
	if (!iCount)
		info = info | C4MN_Add_ForceCount;
	
	var count = 0;
	
	if (!bMoney && iCount > 0)
		count = iCount;
	
	pClonk->AddMenuItem(Format("%3d$: %s", wealth, name), "BuyItem", id, count, pClonk, description, info, obj);
	
	RemoveObject(obj); //Hilfsobjekt loeschen
}

//Kaufbar?
func BuyAble(id Item, int Plr)
{
	//genug Geld?
	if (GetWealth(Plr) < GetDefValue(Item))
		return false;
	if (GetWareCount(Item) == 0)
		return false;
	return true;
}

func BuyItem(id Item, object pClonk)
{
	var iPlr = GetOwner(pClonk);
	
	if (!DoBuyItem(Item, iPlr, pClonk))
	{
		Sound("Error", 0, 0, 0, iPlr + 1);
		return;
	}
	Sound("Cash", 0, 0, 0, iPlr + 1);
	
	var sel = GetMenuSelection(pClonk);
	CloseMenu(pClonk);
	CreateBuyMenu(pClonk);
	SelectMenuItem(sel, pClonk);
}

func DoBuyItem(id Item, int iPlr, object pClonk)
{
	//kaufbar?
	if (!BuyAble(Item, iPlr))
		return false;
	
	//Objekt erzeugen
	var tmp = CreateObject(Item, 0, 0, GetOwner(pClonk));
	//einsammelbar?
	if (pClonk->~RejectCollect(Item, tmp))
	{
		RemoveObject(tmp);
		//nein. :(
		return false;
	}
	else
	{
		//Waffe?
		if (tmp->~IsWeapon())
			//n bisschen Muni gibts gratis dazu!
			// TODO tmp->DoAmmo(tmp->GetFMData(FM_AmmoID), tmp->GetFMData(FM_AmmoLoad));
			Enter(pClonk, tmp);
	}
	
	//Geld abziehn
	DoWealth(iPlr, -GetDefValue(Item));
	
	DoWare(Item, -1);
	
	return true;
}








/* Warenhandling-Funktionen */

//Warenbestand aendern
func DoWare(id ID, int iChange)
{
	//Ware nicht im Angebot?
	if (!FindWare(ID))
		return false;
	if (!ID)
	{
		for (var ware in aWare) 
			ChangeWare(ware, iChange);
	}
	else
		ChangeWare(GetWare(ID), iChange);
}

//nur eine interne Funktion, die die Ware dann wirklich aendert
//Damit man den Check nicht immer schreiben muss
func ChangeWare(int iIndex, int iChange)
{
	//Ware ist unendlich oft verfuegbar?
	if (aCount[iIndex] < 0)
		return;
	
	aCount[iIndex] += iChange;
	//Anzahl < 0?
	if (aCount[iIndex] < 0)
		//Anzahl auf 0 setzen
		//sonst waere die Ware ja auf einmal unendlich oft zu haben.
		aCount[iIndex] = 0;
}

//Ware hinzufuegen
func AddWare(id ID, int iCount)
{
	//keine ID angegeben?
	if (!ID)
		return false;
	//Ware schon im Angebot?
	if (FindWare(ID))
		return false;
	
	//Anzahl-Parameter checken
	if (iCount < -1)
		iCount = -1;
	
	//Ware hinzufuegen
	PushBack(aWare, ID);
	PushBack(aCount, iCount);
}

//Alle Waren eines Typs hinzufuegen
func AddWares(string szCallback, int iCount)
{
	var id, defz;
	//alle Definitionen durchgehn
	while (id = GetDefinition(defz++))
	{
		//Objekt kann nicht gewaehlt werden?
		if (id->~NoWeaponChoice())
			continue; //weiter
		//Objekt ist vom richtigen Typ?
		if (id->Call(szCallback))
			AddWare(id, iCount); //hinzufuegen.
	}
}

//Ware entfernen
func RemoveWare(id ID)
{
	//wenn nichts angegeben, alles entfernen
	if (!ID)
	{
		aWare = aCount = CreateArray();
		return true;
	}
	
	if (!FindWare(ID))
		return false;
	
	var x = GetWare(ID);
	aWare[x] = 0;
	aCount[x] = 0;
	return true;
}

//Warenindex abfragen
func GetWare(id ID)
{
	for (var x; x < GetLength(aWare); x++)
		if (aWare[x] == ID)
			return x;
	//haben wir nicht? -1 zurueckgeben.
	return -1;
}

//Anzahl einer Ware abfragen
func GetWareCount(id ID)
{
	for (var x; x < GetLength(aWare); x++)
		if (aWare[x] == ID)
			return aCount[x];
}

//Warenliste abfragen
func GetWareList()
{
	return aWare;
}

// Waren nach Kategorie abfragten
func GetWares(string szCallback)
{
	var ret = CreateArray();
	for (var x; x < GetLength(aWare); x++)
		if (aWare[x]->Call(szCallback))
			ret[GetLength(ret)] = aWare[x];
	return ret;
}

func GetBuyableWaresFor(string szCallback, int player)
{
	var aWaresAll = GetWares(szCallback);
	var aWares = CreateArray();
	for (var ware in aWaresAll) 
		if (GetWealth(player) >= GetValue(0, ware))
			aWares[GetLength(aWares)] = ware;
	return aWares;
}

//bestimmte Ware auf bestimmten Wert setzen. Oder alle.
func SetWare(id id, int iCount)
{
	for (var x; x < GetLength(aWare); x++)
		if (!id || id == aWare[x])
			aCount[x] = iCount;
}

func FindWare(id ID)
{
	for (var x in aWare) 
		if (x == ID)
			return true;
	return false;
}

//Bei Aufsammlung zur Warenliste hinzufuegen
func RejectCollect(id id, object pObj)
{
	if (FindWare(id))
		return RemoveObject(pObj);
	AddWare(id, 0);
}

func Grabbed(object pByObject, bool fGrab)
{
	if (fGrab)
		CreateBuyMenu(pByObject);
	return 1;
}

/* Serialisierung */

func Serialize(array extra) //TODO: implement correct saving mechanism
{
	if (GetLength(aWare))
	{
		extra[GetLength(extra)] = Format("LocalN(\"aWare\")=%v", aWare);
		extra[GetLength(extra)] = Format("LocalN(\"aCount\")=%v", aCount);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
