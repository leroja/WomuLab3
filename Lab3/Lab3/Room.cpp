#include "pch.h"
#include "Room.h"


Room::Room()
{

}

Room::~Room()
{

	this->Ceiling = ref new Wall();
	this->Floor = ref new Wall();
	this->Wall1 = ref new Wall();
	this->Wall2 = ref new Wall();
	this->Wall3 = ref new Wall();
	this->Wall4 = ref new Wall();
}

Room::Room(Platform::String^ title, Platform::String^ desc, double lati, double longi) {
	this->Description = desc;
	this->Title = title;
	this->latitude = lati;
	this->longitude = longi;
	this->Ceiling = ref new Wall();
	this->Floor = ref new Wall();
	this->Wall1 = ref new Wall();
	this->Wall2 = ref new Wall();
	this->Wall3 = ref new Wall();
	this->Wall4 = ref new Wall();
}

double Room::getVolume() {


	//temp
	return 0.0;

}