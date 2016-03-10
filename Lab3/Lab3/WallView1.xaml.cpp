//
// WallView1.xaml.cpp
// Implementation of the WallView1 class
//

#include "pch.h"
#include "WallView1.xaml.h"
#include "MainPage.xaml.h"

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

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

WallView1::WallView1()
{
	InitializeComponent();
	Area->Text = "test";
}



void Lab3::WallView1::Save_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

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

}
