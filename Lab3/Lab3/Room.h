#pragma once
class Wall;
class Room
{
public:
	Room();
	std::string GetTitle() const { return Title; };
	void SetTitle(const std::string& title) { Title = title; }
	std::string GetDescription() const { return Description; };
	void SetDescription(const std::string& desc) { Description = desc; }

private:
	double Volume;
	Wall* Wall1;
	Wall* Wall2;
	Wall* Wall3;
	Wall* Wall4;
	Wall* Roof;
	Wall* Floor;
	std::string Title;
	std::string Description;
	// latitude
	// longitude
};

