//
// RoomChooserView.xaml.cpp
// Implementation of the RoomChooserView class
//

#include "pch.h"
#include "RoomChooserView.xaml.h"
#include "MainPage.xaml.h"
#include "RoomView1.xaml.h"
#include <list>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>


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


void Lab3::RoomChooserView::Home_Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(TypeName(MainPage::typeid));
}


void Lab3::RoomChooserView::listBox_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	Object^ tempSelected = listBox->SelectedItem;
	String^ ayf = listBox->SelectedItem->ToString();
	StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;
	concurrency::task<StorageFile^>(localFolder->GetFileAsync(ayf)).then([this](StorageFile^ testfile) {
		return FileIO::ReadTextAsync(testfile);
	}).then([this](concurrency::task<String^> op) {
		String^ test;	
		string t1;
		vector<string> test1;
		test = op.get();
		std::wstring fooW(test->Begin());
		std::string fooA(fooW.begin(), fooW.end());
		stringstream ss(fooA);
		while (getline(ss,t1)) {
			test1.push_back(t1);
		}
		Room^ selectedRoom = ref new Room();

		
		selectedRoom->setTitle(convertStdString(test1[0]));
		selectedRoom->setDescription(convertStdString(test1[1]));
		selectedRoom->setLatitude(::atof(test1[2].c_str()));
		selectedRoom->setLongitude(::atof(test1[3].c_str()));

		selectedRoom->GetWall1()->setTitle(convertStdString(test1[4]));
		selectedRoom->GetWall1()->setDescription(convertStdString(test1[5]));
		selectedRoom->GetWall1()->setArea(::atof(test1[6].c_str()));
		//selectedRoom->GetWall1()->setImage     (convertStdString(test1[7]));

		selectedRoom->GetWall2()->setTitle(convertStdString(test1[8]));
		selectedRoom->GetWall2()->setDescription(convertStdString(test1[9]));
		selectedRoom->GetWall2()->setArea(::atof(test1[10].c_str()));
		//selectedRoom->GetWall1()->setImage    (convertStdString(test1[11]));

		selectedRoom->GetWall3()->setTitle(convertStdString(test1[12]));
		selectedRoom->GetWall3()->setDescription(convertStdString(test1[13]));
		selectedRoom->GetWall3()->setArea(::atof(test1[14].c_str()));
		//selectedRoom->GetWall1()->setImage	(convertStdString(test1[15]));

		selectedRoom->GetWall4()->setTitle(convertStdString(test1[16]));
		selectedRoom->GetWall4()->setDescription(convertStdString(test1[17]));
		selectedRoom->GetWall4()->setArea(::atof(test1[18].c_str()));
		//selectedRoom->GetWall1()->setImage	(convertStdString(test1[19]));

		selectedRoom->GetCeiling()->setTitle(convertStdString(test1[20]));
		selectedRoom->GetCeiling()->setDescription(convertStdString(test1[21]));
		selectedRoom->GetCeiling()->setArea(::atof(test1[22].c_str()));
		//selectedRoom->GetWall1()->setImage	(convertStdString(test1[23]));

		selectedRoom->GetFloor()->setTitle(convertStdString(test1[24]));
		selectedRoom->GetFloor()->setDescription(convertStdString(test1[25]));
		selectedRoom->GetFloor()->setArea(::atof(test1[26].c_str()));
		//selectedRoom->GetWall1()->setImage	(convertStdString(test1[27]));


		this->Frame->Navigate(TypeName(RoomView1::typeid), selectedRoom);

	});
}
Platform::String^ RoomChooserView::convertStdString(std::string e) {
	std::wstring widestr = std::wstring(e.begin(), e.end());

	const wchar_t* wchart = widestr.c_str();
	return ref new String(wchart);

}