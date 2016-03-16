//
// RoomChooserView.xaml.cpp
// Implementation of the RoomChooserView class
//

#include "pch.h"
#include "RoomChooserView.xaml.h"
#include "MainPage.xaml.h"
#include "RoomView1.xaml.h"
#include <list>

#include "GeoFenceStuff.h"

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
using namespace Windows::UI::Xaml::Interop;
using namespace std;

using namespace Windows::Storage;
using namespace Windows::Storage::Streams;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace concurrency;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

RoomChooserView::RoomChooserView()
{
	InitializeComponent();
	getAllfiles();
	listBox->ItemsSource = filenames;
}

//StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;
//Concurrency::task<StorageFile^>(localFolder->GetFileAsync("Data.txt")).then([this](StorageFile^ file) {
//	return FileIO::ReadTextAsync(file);
//}).then([this, &res](Concurrency::task<String^>operation) {
//	String^ temp;
//	temp = operation.get();
//	OutputDebugString(temp->Begin());
//});

Platform::Collections::Vector<Platform::String^>^ RoomChooserView::getAllfiles() {
	filenames =  ref new Platform::Collections::Vector<Platform::String^>();
	StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;
	filenames->Clear();
	auto createFileTask = create_task(localFolder->GetFilesAsync()).then([=](IVectorView<StorageFile^>^ filesInFolder) {
		for (auto it = filesInFolder->First(); it->HasCurrent; it->MoveNext())
		{
			String^ test;
			StorageFile^ file;
			file = it->Current;
			test = file->Name;
			filenames->InsertAt(0,test);
		}

	});
	return nullptr;
}
	
	/*GeoFenceStuff^ geo = ref new GeoFenceStuff();

	auto createFileTask = create_task(localFolder->CreateFileAsync("text.txt", CreationCollisionOption::OpenIfExists)).then([this](StorageFile^ newFile) {
		double volume = 10;
		double latitude = 25;
		double longitude = 122;

		String^ title = "Title: " + "Test";
		String^ Desc = "Description: " + "TestDesc";
		String^ Vol = "Volume: " + volume;
		String^ lat = "Latitude: " + latitude;
		String^ lon = "Longitude: " + longitude;
		String^ te = title + Desc + Vol + lat + lon;

		create_task(FileIO::WriteTextAsync(newFile, te)).then([](task<void> task)
		{
		
		});
	});

*/


	//auto getFilesTask = create_task(localFolder->GetFilesAsync()).then([=](IVectorView<StorageFile^>^ filesInFolder) {
	//	//Iterate over the results and print the list of files
	//	// to the visual studio output window
	//	for (auto it = filesInFolder->First(); it->HasCurrent; it->MoveNext())
	//	{
	//		StorageFile^ file = it->Current;

	//		geo->GenerateGeofence(file); /////

	//		String^ output = file->Name + "\n";
	////		OutputDebugString(output->Begin());

	//	}
	//});






	//Room t("hej", "test");
	//Room t2("hej2", "test");
	//Room t3("hej3", "test");
	//Room t4("hej4", "test");
	
	//listBox->Items->Append(t);



void Lab3::RoomChooserView::Home_Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(TypeName(MainPage::typeid));
}


void Lab3::RoomChooserView::listBox_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	Object^ tempSelected = listBox->SelectedItem;

	String^ ayf = listBox->SelectedItem->ToString();

	Room^ selectedRoom;
	//selectedRoom = (Room)tempSelected;


	this->Frame->Navigate(TypeName(RoomView1::typeid), selectedRoom);
}
