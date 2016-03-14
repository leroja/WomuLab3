#pragma once
ref class GeoFenceStuff sealed
{
public:
	GeoFenceStuff();
	virtual ~GeoFenceStuff();

private:
	Windows::Devices::Geolocation::Geofencing::Geofence^ GenerateGeofence();
	Platform::Collections::Vector<Windows::Devices::Geolocation::Geofencing::Geofence^>^ GenerateAllGeofences();

};

