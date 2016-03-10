//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "RoomView1.xaml.h"

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
using namespace concurrency;
using namespace Windows::Storage;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();
}


void Lab3::MainPage::button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(RoomView1::typeid));
}


void Lab3::MainPage::NewRoom_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	//Get the app's local folder
	StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;
	String^ desiredName = "Subfolder";

	StorageFolder^ appFolder = Windows::ApplicationModel::Package::Current->InstalledLocation;

	auto ctF = create_task(localFolder->CreateFolderAsync(desiredName, Windows::Storage::CreationCollisionOption::FailIfExists)).then([](StorageFolder^ folder) {
		//Do something with folder
	});



	//StorageFolder test = ApplicationData::Current->LocalFolder->CreateFolderAsync("test", CreationCollisionOption::OpenIfExists);

	//Create a new file in the current folder.
	//Raises an exception if the file already exists
	auto createFileTask = create_task(localFolder->CreateFileAsync("text.txt")).then([](StorageFile^ newFile) {

		//Do something with new file

	});
}


void Lab3::MainPage::Continue_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}
