#include "pch.h"
#include "RandomStuff.h"

using namespace Platform;

RandomStuff::RandomStuff()
{
}


RandomStuff::~RandomStuff()
{
}



Platform::String ^ RandomStuff::GenerateSaveString(Room ^ room)
{
	String^ returnString;
	String^ Wall1, ^Wall2, ^Wall3, ^Wall4, ^ceiling,^ floor,^ Volume,^ longitude,^ latitude,^ title,^ desc;



	Wall1 = WallString(room->GetWall1()); 
	Wall2 = WallString(room->GetWall2());
	Wall3 = WallString(room->GetWall3());
	Wall4 = WallString(room->GetWall4());
	ceiling = WallString(room->GetCeiling());
	floor = WallString(room->GetFloor());

	return returnString;
}

Platform::String ^ RandomStuff::GeneratePicPath(Room ^ room, Wall ^ wall)
{
	String^ l;



	return  l;
}

Platform::String ^ RandomStuff::WallString(Wall ^ wall)
{
	String^ wallStr, ^ title, ^desc, ^area,^picPath;
	if (wall != nullptr)
	{
		
//		picPath = GeneratePicPath();
		double ar = wall->GetArea();
		area = "" + ar;
		title = wall->GetTitle();
		desc = wall->GetDescription();

		wallStr = title + "\n" + desc + "\n" + area + "\n" + picPath + "\n";
	}
	else
	{
		wallStr = "WallNullptr";
	}


	return wallStr;
}
