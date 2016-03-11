#include "pch.h"
#include "Room.h"


Room::Room()
{

}

Room::Room(std::string title, std::string desc) {
	this->Description = desc;
	this->Title = title;
}