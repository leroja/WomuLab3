//
// RoomView1.xaml.cpp
// Implementation of the RoomView1 class
//

#include "pch.h"
#include "RoomView1.xaml.h"
#include "MainPage.xaml.h"
#include "WallView1.xaml.h"
#include "Room.h"

using namespace Lab3;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace std;
using namespace concurrency;
using namespace Windows::Storage;
using namespace Windows::Devices::Geolocation;


// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

RoomView1::RoomView1()
{
	InitializeComponent();

}



void RoomView1::OnNavigatedTo(NavigationEventArgs^ e)
{
	try
	{
		Room^ room = (Room^)e->Parameter;
		App^ thisApp = (App^)Application::Current;
		thisApp->currentWall = 0;
		if (room != nullptr) {
			this->room = room;
			RoomTitle->Text = room->GetTitle();
			RoomDescription->Text = room->GetDescription();
			RoomVolume->Text = room->getVolume().ToString();
			Longitude->Text = room->GetLongitude().ToString();
			Latitude->Text = room->GetLatitude().ToString();
		}
		thisApp->curentRoom = this->room;
	}
	catch (const std::exception&)
	{
		
	}
}










void Lab3::RoomView1::Floor_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	App^ thisApp = (App^)Application::Current;
	thisApp->currentWall = 6;
	this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(WallView1::typeid), this->room->GetFloor());
}


void Lab3::RoomView1::Ceiling_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	App^ thisApp = (App^)Application::Current;
	thisApp->currentWall = 5;
	this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(WallView1::typeid), this->room->GetCeiling());
}


void Lab3::RoomView1::Wall4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	App^ thisApp = (App^)Application::Current;
	thisApp->currentWall = 4;
	this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(WallView1::typeid), this->room->GetWall4());
}


void Lab3::RoomView1::Wall3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	App^ thisApp = (App^)Application::Current;
	thisApp->currentWall = 3;
	this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(WallView1::typeid), this->room->GetWall3());
}


void Lab3::RoomView1::Wall2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	App^ thisApp = (App^)Application::Current;
	thisApp->currentWall = 2;
	this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(WallView1::typeid), this->room->GetWall2());
}


void Lab3::RoomView1::Wall1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	App^ thisApp = (App^)Application::Current;
	thisApp->currentWall = 1;
	this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(WallView1::typeid), this->room->GetWall1());
}



void Lab3::RoomView1::HomeButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(MainPage::typeid));
}


void Lab3::RoomView1::SaveButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Platform::String^ title, ^ description;
	StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;
	title = RoomTitle->Text;
	description = RoomDescription->Text;
	this->room->setTitle(title);
	this->room->setDescription(description);
	String^ filenamn = this->room->GetTitle();
	concurrency::task<StorageFile^>(localFolder->CreateFileAsync(filenamn, CreationCollisionOption::ReplaceExisting)).then([this](StorageFile^ newFile) {
		
		Platform::String^ filestring;
		filestring += this->room->GetTitle() +"\n";
		filestring += this->room->GetDescription() + "\n";
		filestring += this->room->GetLatitude() + "\n";
		filestring += this->room->GetLongitude() + "\n";

		filestring += this->room->GetWall1()->GetTitle() + "\n";
		filestring += this->room->GetWall1()->GetDescription() + "\n";
		filestring += this->room->GetWall1()->GetArea() + "\n";
		filestring += "..." + "\n"; //for pic filepath

		filestring += this->room->GetWall2()->GetTitle() + "\n";
		filestring += this->room->GetWall2()->GetDescription() + "\n";
		filestring += this->room->GetWall2()->GetArea() + "\n";
		filestring += "..." + "\n"; //for pic filepath

		filestring += this->room->GetWall3()->GetTitle() + "\n";
		filestring += this->room->GetWall3()->GetDescription() + "\n";
		filestring += this->room->GetWall3()->GetArea() + "\n";
		filestring += "..." + "\n"; //for pic filepath

		filestring += this->room->GetWall4()->GetTitle() + "\n";
		filestring += this->room->GetWall4()->GetDescription() + "\n";
		filestring += this->room->GetWall4()->GetArea() + "\n";
		filestring += "..." + "\n"; //for pic filepath

		filestring += this->room->GetCeiling() ->GetTitle() + "\n";
		filestring += this->room->GetCeiling()->GetDescription() + "\n";
		filestring += this->room->GetCeiling()->GetArea() + "\n";
		filestring += "..." + "\n"; //for pic filepath

		filestring += this->room->GetFloor()->GetTitle() + "\n";
		filestring += this->room->GetFloor()->GetDescription() + "\n";
		filestring += this->room->GetFloor()->GetArea() + "\n";
		filestring += "..." + "\n"; //for pic filepath

		return FileIO::WriteTextAsync(newFile, filestring);
	});
}
	
	

void Lab3::RoomView1::Updatelatlong_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Geolocator^ geolocator = ref new Geolocator;

	geolocator->DesiredAccuracy = PositionAccuracy::High;


	task<Geoposition^> geopositionTask(geolocator->GetGeopositionAsync());
	geopositionTask.then([this](task<Geoposition^> getPosTask)
	{
		try
		{
			// Get will throw an exception if the task was canceled or failed with an error
			Geoposition^ pos = getPosTask.get();

			auto Lati = pos->Coordinate->Point->Position.Latitude;
			auto Longi = pos->Coordinate->Point->Position.Longitude;

			room->setLatitude(Lati);
			room->setLongitude(Longi);
			Longitude->Text = Longi.ToString();
			Latitude->Text = Lati.ToString();
		}
		catch (task_canceled&)
		{

		}
		catch (Exception^ ex)
		{

		}
	});

}
