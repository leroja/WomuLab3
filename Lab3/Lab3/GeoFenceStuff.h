#pragma once

#include "MainPage.xaml.h"
#include "Room.h"
#include "pch.h"

ref class GeoFenceStuff sealed
{
public:
	GeoFenceStuff();
	virtual ~GeoFenceStuff();


	//Windows::Devices::Geolocation::Geofencing::Geofence^ GenerateGeofence(Windows::Storage::StorageFile^ file);

	//void GenerateAllGeofences();
	void RegisterBackgroundTask();
	void addGeofence(Room^ room);

	//Windows::Devices::Geolocation::Geofencing::Geofence^ GenerateGeofence(Room^ room);

private:
	Windows::Devices::Geolocation::Geofencing::Geofence^ GenerateGeofence(std::vector<std::string> vec);
	Windows::Devices::Geolocation::Geofencing::Geofence^ GenerateGeofence(Room^ room);
	void RequestLocationAccess();
	void GenerateAllGeofences();
	void OnCompleted(Windows::ApplicationModel::Background::BackgroundTaskRegistration^ sender, Windows::ApplicationModel::Background::BackgroundTaskCompletedEventArgs^ e);

	Windows::Foundation::Collections::IVector<Windows::Devices::Geolocation::Geofencing::Geofence^>^ geofences;

	Windows::ApplicationModel::Background::BackgroundTaskRegistration^ geofenceTask;
	Windows::Foundation::EventRegistrationToken taskCompletedToken;
	Lab3::MainPage^ rootPage;




	Platform::String^ convertStdString(std::string e);
};

