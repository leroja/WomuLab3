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

Platform::String ^ RandomStuff::WallString(Wall ^ wall)
{
	String^ wallStr, ^ title, ^desc, ^area,^picPath;
	if (wall != nullptr)
	{
		Windows::UI::Xaml::Controls::Image^ img = wall->getImage();
		Windows::UI::Xaml::Media::ImageSource^ l = img->Source;
		
		// get path
		double ar = wall->GetArea();
		area = "" + ar;
		title = wall->GetTitle();
		desc = wall->GetDescription();

		wallStr = title + desc + area + picPath;
	}
	else
	{
		wallStr = "WallNullptr";
	}


	return wallStr;
}
