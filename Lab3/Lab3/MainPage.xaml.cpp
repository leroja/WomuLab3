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

	//StorageFolder^ tests = KnownFolders::DocumentsLibrary;
	/*textBlock->Text = tests->ToString();*/

	//Get the app's local folder
	StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;
	textBlock->Text = localFolder->Path;
	String^ desiredName = "Subfolder";

	StorageFolder^ appFolder = Windows::ApplicationModel::Package::Current->InstalledLocation;

	auto ctF = create_task(localFolder->CreateFolderAsync(desiredName, CreationCollisionOption::OpenIfExists)).then([](StorageFolder^ folder) {
		//Do something with folder

	});
	

	StorageFile^ tsts;
	
	//Create a new file in the current folder.
	//Raises an exception if the file already exists
	auto createFileTask = create_task(localFolder->CreateFileAsync("text.txt", CreationCollisionOption::OpenIfExists)).then([](StorageFile^ newFile) {
		
		
		

		String^ te = "test tets";

		create_task(FileIO::WriteTextAsync(newFile, te)).then([](task<void> task)
		{
			
		});
		//Do something with new file


	});
	
	this->file = tsts;
}


void Lab3::MainPage::Continue_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}


void Lab3::MainPage::button1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	StorageFile^ file = this->file;
	if (file != nullptr)
	{
		create_task(FileIO::ReadTextAsync(file)).then([this, file](task<String^> task)
		{
			try
			{
				String^ fileContent = task.get();
				test(fileContent);
			}
			catch (COMException^ ex)
			{
				
			}
		});
	}
	else
	{
		
	}
}

void MainPage::test(Platform::String^ content) {

	
	textBlock1->Text = content;

	
}

void MainPage::testtest(Windows::Storage::StorageFile^ newFile) {

	this->file = newFile;
}