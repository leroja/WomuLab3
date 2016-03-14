//
// RoomChooserView.xaml.cpp
// Implementation of the RoomChooserView class
//

#include "pch.h"
#include "RoomChooserView.xaml.h"
#include "MainPage.xaml.h"
#include "RoomView1.xaml.h"
#include <list>

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

	StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;



	auto getFilesTask = create_task(localFolder->GetFilesAsync()).then([=](IVectorView<StorageFile^>^ filesInFolder) {
		//Iterate over the results and print the list of files
		// to the visual studio output window
		for (auto it = filesInFolder->First(); it->HasCurrent; it->MoveNext())
		{
			StorageFile^ file = it->Current;
			String^ output = file->Name + "\n";
			OutputDebugString(output->Begin());

		}
	});






	//Room t("hej", "test");
	//Room t2("hej2", "test");
	//Room t3("hej3", "test");
	//Room t4("hej4", "test");
	
	//listBox->Items->Append(t);

}


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
