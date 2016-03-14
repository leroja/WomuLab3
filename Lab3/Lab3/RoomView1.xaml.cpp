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

		if (room != nullptr) {
			this->room = room;
			RoomTitle->Text = room->GetTitle();
			RoomDescription->Text = room->GetDescription();
			Longitude->Text = room->GetLongitude().ToString();
			Latitude->Text = room->GetLatitude().ToString();


		}
	}
	catch (const std::exception&)
	{
		
	}

}










void Lab3::RoomView1::Floor_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(WallView1::typeid));
}


void Lab3::RoomView1::Ceiling_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(WallView1::typeid));
}


void Lab3::RoomView1::Wall4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(WallView1::typeid));
}


void Lab3::RoomView1::Wall3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(WallView1::typeid));
}


void Lab3::RoomView1::Wall2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(WallView1::typeid));
}


void Lab3::RoomView1::Wall1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
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
	double Volume = this->room->getVolume();

	title = RoomTitle->Text;
	description = RoomDescription->Text;

	this->room->setTitle(title);
	this->room->setDescription(description);



	//Platform::String^ FileName = "namn.end";

	//auto createFileTask = create_task(localFolder->CreateFileAsync(FileName, CreationCollisionOption::ReplaceExisting)).then([](StorageFile^ newFile) {

	//	//temp
	//	String^ te = "test tets";
	//	create_task(FileIO::WriteTextAsync(newFile,te)).then([](task<void> task)
	//	{
	//	
	//	});
	//	//Do something with new file
	//});
}