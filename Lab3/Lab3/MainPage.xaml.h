//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace Lab3
{
	public enum class NotifyType
	{
		StatusMessage,
		ErrorMessage
	};



	/// <summary>
	///
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	private:
		void NewRoom_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Continue_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

	internal:
		static MainPage^ Current;
		void NotifyUser(Platform::String^ strMessage, NotifyType type);
	};
}
