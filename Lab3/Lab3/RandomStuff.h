#pragma once
ref class RandomStuff sealed
{
public:
	RandomStuff();
	virtual ~RandomStuff();

	Platform::String^ GenerateSaveString(Room^ room);

private:
	Platform::String^ WallString(Wall^ wall);
};

