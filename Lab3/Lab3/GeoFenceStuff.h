#pragma once

#include "MainPage.xaml.h"
#include "pch.h"

ref class GeoFenceStuff sealed
{
public:
	GeoFenceStuff();
	virtual ~GeoFenceStuff();


	//Windows::Devices::Geolocation::Geofencing::Geofence^ GenerateGeofence(Windows::Storage::StorageFile^ file);

	//Platform::Collections::Vector<Windows::Devices::Geolocation::Geofencing::Geofence^>^ GenerateAllGeofences();
	void RegisterBackgroundTask();

private:
	Windows::Devices::Geolocation::Geofencing::Geofence^ GenerateGeofence(Windows::Storage::StorageFile^ file);
	void RequestLocationAccess();
	Platform::Collections::Vector<Windows::Devices::Geolocation::Geofencing::Geofence^>^ GenerateAllGeofences();
	void OnCompleted(Windows::ApplicationModel::Background::BackgroundTaskRegistration^ sender, Windows::ApplicationModel::Background::BackgroundTaskCompletedEventArgs^ e);

	Windows::Foundation::Collections::IVector<Windows::Devices::Geolocation::Geofencing::Geofence^>^ geofences;

	Windows::ApplicationModel::Background::BackgroundTaskRegistration^ geofenceTask;
	Windows::Foundation::EventRegistrationToken taskCompletedToken;
	Lab3::MainPage^ rootPage;
};

