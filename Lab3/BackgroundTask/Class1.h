#pragma once



#include "pch.h"
#include <agile.h>

using namespace Windows::ApplicationModel::Background;
using namespace Windows::System::Threading;


namespace BackgroundTask
{
	public ref class Class1 sealed : public IBackgroundTask
    {
    public:
        Class1();
		
		virtual void Run(IBackgroundTaskInstance^ taskInstance);

		void OnCanceled(IBackgroundTaskInstance^ taskInstance, BackgroundTaskCancellationReason reason);
	private:
		~Class1();

		BackgroundTaskCancellationReason CancelReason;
		volatile bool CancelRequested;
		Platform::Agile<Windows::ApplicationModel::Background::BackgroundTaskDeferral> TaskDeferral;
		ThreadPoolTimer^ PeriodicTimer;
		unsigned int Progress;
		IBackgroundTaskInstance^ TaskInstance;


		//
		Concurrency::cancellation_token_source geopositionTaskTokenSource;
    };



	public ref class GeofenceBackgroundTask sealed : public Windows::ApplicationModel::Background::IBackgroundTask
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


}
