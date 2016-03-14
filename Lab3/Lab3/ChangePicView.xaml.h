//
// ChangePicView.xaml.h
// Declaration of the ChangePicView class
//

#pragma once

#include "ChangePicView.g.h"

namespace Lab3
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class ChangePicView sealed
	{
	public:
		ChangePicView();
	private:
		void NewPic_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OldPic_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Back_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
