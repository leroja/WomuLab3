#pragma once
ref class GeoFenceStuff sealed
{
public:
	GeoFenceStuff();
	virtual ~GeoFenceStuff();


	Windows::Devices::Geolocation::Geofencing::Geofence^ GenerateGeofence(Windows::Storage::StorageFile^ file);

	//Platform::Collections::Vector<Windows::Devices::Geolocation::Geofencing::Geofence^>^ GenerateAllGeofences();
	void RegisterBackgroundTask();

private:
	//Windows::Devices::Geolocation::Geofencing::Geofence^ GenerateGeofence(Windows::Storage::StorageFile^ file);
	void RequestLocationAccess();
	Platform::Collections::Vector<Windows::Devices::Geolocation::Geofencing::Geofence^>^ GenerateAllGeofences();

	Windows::Foundation::Collections::IVector<Windows::Devices::Geolocation::Geofencing::Geofence^>^ geofences;

	Windows::ApplicationModel::Background::BackgroundTaskRegistration^ geofenceTask;
	Windows::Foundation::EventRegistrationToken taskCompletedToken;
};

