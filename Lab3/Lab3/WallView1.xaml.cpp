//
// WallView1.xaml.cpp
// Implementation of the WallView1 class
//

#include "pch.h"
#include "WallView1.xaml.h"
#include "MainPage.xaml.h"
#include "ChangePicView.xaml.h"
#include "RoomView1.xaml.h"
using namespace Lab3;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Storage;
using namespace Windows::Devices::Sensors;
using namespace Windows::Graphics::Display;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

WallView1::WallView1()
{
	InitializeComponent();
	meter = Accelerometer::GetDefault();
	acel();
}



void WallView1::OnNavigatedTo(NavigationEventArgs^ e)
{
	try
	{
		Wall^ newWall = (Wall^)e->Parameter;

		if (newWall != nullptr) {
			this->wall = newWall;
			this->Title->Text = this->wall->GetTitle();
			this->Description->Text = this->wall->GetDescription();
			this->Area->Text = this->wall->GetArea().ToString();
			if (this->wall->getImage() != nullptr) {
				this->WallImage->Source = this->wall->getImage()->Source;
			}
		}
		else {
			wall = ref new Wall();
		}
	}
	catch (const std::exception&)
	{
	
	}

}



void Lab3::WallView1::Save_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Platform::String^ title, ^ description;
	double area;

	title = Title->Text;
	description = Description->Text;
	wchar_t* end_parse;
	area = wcstod(Area->Text->Data(), &end_parse);

	this->wall->setTitle(title);
	this->wall->setDescription(description);
	this->wall->setArea(area);
}


void Lab3::WallView1::Back_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	App^ thisApp = (App^)Application::Current;
	this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(RoomView1::typeid),thisApp->curentRoom);
}


void Lab3::WallView1::Home_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	//this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(MainPage::typeid));
}


void Lab3::WallView1::ChangePicture_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Platform::String^ title, ^ description;
	double area;

	title = Title->Text;
	description = Description->Text;
	wchar_t* end_parse;
	area = wcstod(Area->Text->Data(), &end_parse);

	this->wall->setTitle(title);
	this->wall->setDescription(description);
	this->wall->setArea(area);

	this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(ChangePicView::typeid), this->wall);
}

void Lab3::WallView1::acel(void){
	meter->ReportInterval = 10000;
	readingTokenOriginal = meter->ReadingChanged += ref new TypedEventHandler<Accelerometer^, AccelerometerReadingChangedEventArgs^>(this, &WallView1::ReadingChangedOriginal);


}
void Lab3::WallView1::ReadingChangedOriginal(Accelerometer^ sender, AccelerometerReadingChangedEventArgs^ e) {
	Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([this, e]()
	{
		AccelerometerReading^ test = e->Reading;
		App^ thisApp = (App^)Application::Current;
		switch (thisApp->currentWall)
		{
		case 1:
			if (test->AccelerationX > 0.5) {
				Wall^ free;
				free = thisApp->curentRoom->GetWall4();
				this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(WallView1::typeid), free);
				break;
			}
			else if (test->AccelerationX < -0.5) {
				Wall^ free;
				free = thisApp->curentRoom->GetWall2();
				this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(WallView1::typeid), free);
				break;
			}
				break;
		case 2:

		case 3:

		case 4:

		case 5:

		case 6:

		default:
			break;
		}
		}));
}
void Lab3::WallView1::OnNavigatedFrom(NavigationEventArgs^ e) {
	meter->ReadingChanged -= readingTokenOriginal;
	meter->ReportInterval = 0;
}
