#pragma once

#include "Wall.h"

ref class Room sealed
{
public:
	Room();
	virtual ~Room();
	Room(Platform::String^ title, Platform::String^ desc, double lati, double longi);

	Platform::String^ GetTitle() { return Title; };
	Platform::String^ GetDescription() { return Description; };
	double GetLatitude() { return latitude; };
	double GetLongitude() { return longitude; };

	Wall^ GetWall1() { return Wall1; };
	Wall^ GetWall2() { return Wall2; };
	Wall^ GetWall3() { return Wall3; };
	Wall^ GetWall4() { return Wall4; };
	Wall^ GetCeiling() { return Ceiling; };
	Wall^ GetFloor() { return Floor; };
	double getVolume();

	void setTitle(Platform::String^ title) { this->Title = title; };
	void setDescription(Platform::String^ desc) { this->Description = desc; };
	void setLatitude(double lati) { this->latitude = lati; };
	void setLongitude(double longi) { this->longitude = longi; };

private:
	double Volume;
	Wall^ Wall1;
	Wall^ Wall2;
	Wall^ Wall3;
	Wall^ Wall4;
	Wall^ Ceiling;
	Wall^ Floor;
	Platform::String^ Title;
	Platform::String^ Description;
	double latitude;
	double longitude;
};

