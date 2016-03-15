#include "pch.h"
#include "Room.h"
#include <cmath>


Room::Room()
{

	this->Ceiling = ref new Wall();
	this->Floor = ref new Wall();
	this->Wall1 = ref new Wall();
	this->Wall2 = ref new Wall();
	this->Wall3 = ref new Wall();
	this->Wall4 = ref new Wall();
}

Room::~Room()
{

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
	if (this->Floor != nullptr) {

		double baseArea = this->Floor->GetArea();
		double height = 0.0;

		if (this->Wall1 != nullptr) {
			height = sqrt(this->Wall1->GetArea());
		}
		else if (this->Wall2 != nullptr) {
			height = sqrt(this->Wall2->GetArea());
		}
		else if (this->Wall3 != nullptr) {
			height = sqrt(this->Wall3->GetArea());
		}
		else if (this->Wall4 != nullptr) {
			height = sqrt(this->Wall4->GetArea());
		}
		else {
			return 0.0;
		}
		return baseArea * height;
	}
	else {

		return 0.0;
	}


}