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

void Lab3::RoomView1::Floor_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(WallView1::typeid));
}


void Lab3::RoomView1::Roof_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
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
	this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(WallView1::typeid));
}



void Lab3::RoomView1::HomeButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(MainPage::typeid));
}


void Lab3::RoomView1::SaveButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	string title, description, temp;
	double Volume;
	StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;

	temp = ConvertToString(RoomVolume->Text);
	title = ConvertToString(RoomTitle->Text);
	description = ConvertToString(RoomDescription->Text);
	Volume = ::atof(temp.c_str());

	this->room.SetTitle(title);
	this->room.SetDescription(description);
}

std::string RoomView1::ConvertToString(Platform::String^ ps)
{
	std::wstring fooW(ps->Begin());
	std::string fooA(fooW.begin(), fooW.end());
	return fooA;
}