//
// WallView1.xaml.cpp
// Implementation of the WallView1 class
//

#include "pch.h"
#include "WallView1.xaml.h"
#include "MainPage.xaml.h"
#include "ChangePicView.xaml.h"
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
using namespace Windows::Storage;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

WallView1::WallView1()
{
	InitializeComponent();
	Area->Text = "test";
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
	StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;

	title = Title->Text;
	description = Description->Text;

	this->wall->setTitle(title);
	this->wall->setDescription(description);




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


void Lab3::WallView1::Back_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->GoBack();
}


void Lab3::WallView1::Home_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(MainPage::typeid));
}


void Lab3::WallView1::ChangePicture_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Platform::String^ title, ^ description;

	title = Title->Text;
	description = Description->Text;

	this->wall->setTitle(title);
	this->wall->setDescription(description);
	this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(ChangePicView::typeid),wall);
}
