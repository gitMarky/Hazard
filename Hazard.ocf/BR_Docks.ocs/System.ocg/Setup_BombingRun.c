
#appendto Goal_BombingRun

public func DoSetup(int round)
{
	CreateBomb(750, 70, RGB(200,200,200));
	CreateBombGate(1,  15, 200, DIR_Right);
	CreateBombGate(2, 1485, 200, DIR_Left);
	//CreateBombGate(1,  155, 200, DIR_Right);
	//CreateBombGate(2, 1345, 200, DIR_Left);
}
