#pragma once


ref class Wall sealed
{
public:
	Wall();
	virtual ~Wall();

	Platform::String^ GetTitle() { return(Title); };
	Platform::String^ GetDescription() { return Description; };
	Windows::UI::Xaml::Controls::Image^ getImage() { return wallImage; };

	void setTitle(Platform::String^ title) { this->Title = title; };
	void setDescription(Platform::String^ desc) { this->Description = desc; };
	void setWallImage(Windows::UI::Xaml::Controls::Image^ image) { wallImage = image; };
	
	
private:
	Platform::String^ Title;
	Platform::String^ Description;
	double Area;
	Windows::UI::Xaml::Controls::Image^ wallImage;
};

