//
// WallView1.xaml.h
// Declaration of the WallView1 class
//

#pragma once

#include "WallView1.g.h"

namespace Lab3
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class WallView1 sealed
	{
	public:
		WallView1();
	private:
		void acel(void);
		
		void Save_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Back_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Home_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void ChangePicture_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		Wall^ wall;
		void ReadingChangedOriginal(Windows::Devices::Sensors::Accelerometer^ sender, Windows::Devices::Sensors::AccelerometerReadingChangedEventArgs^ e);
		Windows::Devices::Sensors::Accelerometer^ meter;
		Windows::Foundation::EventRegistrationToken readingTokenOriginal;

	protected:
		virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
	};
}
