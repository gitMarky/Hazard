
#appendto Goal_BombingRun

public func DoSetup(int round)
{
	CreateBomb(747, 390, RGB(200, 200, 200));
	CreateBombGate(1,  126, 290, DIR_Right);
	CreateBombGate(2, 1374, 290, DIR_Left);
}
