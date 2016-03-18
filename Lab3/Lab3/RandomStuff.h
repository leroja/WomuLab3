#pragma once
ref class RandomStuff sealed
{
public:
	RandomStuff();
	virtual ~RandomStuff();

	Platform::String^ convertStdString(std::string e);

private:
};

