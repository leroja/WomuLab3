#pragma once

#include "pch.h"

ref class GeofenceBackgroundTask sealed : public Windows::ApplicationModel::Background::IBackgroundTask
{
public:
	GeofenceBackgroundTask();


	virtual void Run(Windows::ApplicationModel::Background::IBackgroundTaskInstance^ taskInstance);
	void Invoke(Windows::Foundation::IAsyncAction^ asyncInfo, Windows::Foundation::AsyncStatus asyncStatus);


private:
	void OnCanceled(Windows::ApplicationModel::Background::IBackgroundTaskInstance^ taskInstance, Windows::ApplicationModel::Background::BackgroundTaskCancellationReason reason);
	void GetGeofenceStateChangedReports(Windows::Devices::Geolocation::Geoposition^ pos);
	void DoToast(int numEventsOfInterest, Platform::String^ eventName);
	void FillEventCollectionWithExistingEvents();
	void SaveExistingEvents();
	void AddEventDescription(Platform::String^ eventDescription);
	~GeofenceBackgroundTask();

	Concurrency::cancellation_token_source geopositionTaskTokenSource;
	Platform::Collections::Vector<Platform::String^>^ geofenceBackgroundEvents;
};

