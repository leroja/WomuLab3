#pragma once
class Wall;
ref class Room sealed
{
public:
	Room();
private:
	double Volume;
	Wall *Wall1, *Wall2, *Wall3, *Wall4, *Roof, *Floor;
};

