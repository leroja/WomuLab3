//
// RoomChooserView.xaml.h
// Declaration of the RoomChooserView class
//

#pragma once

#include "RoomChooserView.g.h"

namespace Lab3
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class RoomChooserView sealed
	{
	public:
		RoomChooserView();
	private:
		void Home_Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void listBox_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
	};
}
