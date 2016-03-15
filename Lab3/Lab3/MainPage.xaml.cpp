//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "RoomView1.xaml.h"
#include "RoomChooserView.xaml.h"

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
using namespace Windows::UI::Core;
using namespace Concurrency;
using namespace Windows::Storage;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::Devices::Geolocation;
using namespace Windows::Devices::Geolocation::Geofencing;
using namespace Windows::Devices::Enumeration;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();
	
}


void Lab3::MainPage::NewRoom_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Windows::Devices::Geolocation::Geolocator^ geolocator = ref new Geolocator;
	double lati, longi;

	geolocator->DesiredAccuracy = PositionAccuracy::High;

	
	task<Geoposition^> geopositionTask(geolocator->GetGeopositionAsync());
	geopositionTask.then([this, &lati, &longi](task<Geoposition^> getPosTask)
	{
		try
		{
			// Get will throw an exception if the task was canceled or failed with an error
			Geoposition^ pos = getPosTask.get();

			auto Latitude = pos->Coordinate->Point->Position.Latitude;
			auto Longitude = pos->Coordinate->Point->Position.Longitude;


			Room^ newRoom = ref new Room("Room Title", "Room Description", Latitude, Longitude);


			this->Frame->Navigate(TypeName(RoomView1::typeid), newRoom);
		}
		catch (task_canceled&)
		{

		}
		catch (Exception^ ex)
		{
			
		}
	});

}


void Lab3::MainPage::Continue_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(RoomChooserView::typeid));
}
