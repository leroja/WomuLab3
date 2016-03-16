//
// RoomView1.xaml.h
// Declaration of the RoomView1 class
//

#pragma once

#include "RoomView1.g.h"

namespace Lab3
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class RoomView1 sealed
	{
	public:
		RoomView1();
	private:
		void Floor_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Ceiling_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Wall4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Wall3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Wall2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Wall1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		Room^ room;
		void button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void HomeButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void SaveButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
	private:
		void Updatelatlong_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
