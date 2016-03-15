#pragma once
ref class RandomStuff sealed
{
public:
	RandomStuff();
	virtual ~RandomStuff();

	Platform::String^ GenerateSaveString(Room^ room);
	Platform::String^ GeneratePicPath(Room^ room, Wall^ wall);

private:
	Platform::String^ WallString(Wall^ wall);
};

