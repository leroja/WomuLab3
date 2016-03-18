#include "pch.h"
#include "GeoFenceStuff.h"
#include <cmath>

#include <string>
#include <vector>
#include <sstream>

using namespace Lab3;
using namespace Platform;
using namespace Windows::Devices::Enumeration;
using namespace Windows::Devices::Geolocation;
using namespace Windows::Devices::Geolocation::Geofencing;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;
using namespace concurrency;
using namespace Windows::ApplicationModel::Background;
using namespace std;


GeoFenceStuff::GeoFenceStuff()
{
	rootPage = MainPage::Current;
	geofences = GeofenceMonitor::Current->Geofences;
}


GeoFenceStuff::~GeoFenceStuff()
{
}

Windows::Devices::Geolocation::Geofencing::Geofence ^ GeoFenceStuff::GenerateGeofence(Windows::Storage::StorageFile^ file)
{
	Geofence^ geofence = nullptr;

	if (file != nullptr)
	{
		create_task(FileIO::ReadTextAsync(file)).then([this, file](task<String^> task)
		{
			try
			{
				String^ fileContent = task.get();

				string t1;
				vector<string> test1;
				std::wstring fooW(fileContent->Begin());
				std::string fooA(fooW.begin(), fooW.end());
				stringstream ss(fooA);
				while (getline(ss, t1)) {
					test1.push_back(t1);
				}


				Geofence^ geofence;
				BasicGeoposition position;
				position.Latitude = ::atof(test1[2].c_str());
				position.Longitude = ::atof(test1[3].c_str());
				position.Altitude = 0.0;
				double temp = ::atof(test1[26].c_str());
				double radius = (sqrt(temp)) / 1.5;
				String^ fencekey = convertStdString(test1[0]);

				MonitoredGeofenceStates mask = static_cast<MonitoredGeofenceStates>(0);
				mask = mask | MonitoredGeofenceStates::Entered;
				mask = mask | MonitoredGeofenceStates::Exited;


				Geocircle^ geocircle = ref new Geocircle(position, radius);
				TimeSpan dwelltime;
				dwelltime.Duration = 10000000;
				bool singleUse = false;

				geofence = ref new Geofence(fencekey, geocircle, mask, singleUse, dwelltime);

				return geofence;

			}
			catch (COMException^ ex)
			{

			}
		});
	}
	return geofence;
}

Windows::Devices::Geolocation::Geofencing::Geofence ^ GeoFenceStuff::GenerateGeofence(Room ^ room)
{
	Geofence^ geofence = nullptr;

	if (room != nullptr)
	{
		BasicGeoposition position;
		position.Latitude = room->GetLatitude();
		position.Longitude = 0.0; room->GetLongitude();
		position.Altitude = 0.0;
		double radius = (sqrt(room->GetFloor()->GetArea()))/1.5;
		String^ fencekey = room->GetTitle();

		MonitoredGeofenceStates mask = static_cast<MonitoredGeofenceStates>(0);
		mask = mask | MonitoredGeofenceStates::Entered;
		mask = mask | MonitoredGeofenceStates::Exited;


		Geocircle^ geocircle = ref new Geocircle(position, radius);
		TimeSpan dwelltime;
		dwelltime.Duration = 10000000;
		bool singleUse = false;

		geofence = ref new Geofence(fencekey, geocircle, mask, singleUse, dwelltime);

		return geofence;
	}
	return geofence;
}

Platform::Collections::Vector<Windows::Devices::Geolocation::Geofencing::Geofence^>^ GeoFenceStuff::GenerateAllGeofences()
{
	//StorageFolder^ roamingFolder = ApplicationData::Current->RoamingFolder;

	geofences->Clear();
	StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;
	auto createFileTask = create_task(localFolder->GetFilesAsync()).then([=](IVectorView<StorageFile^>^ filesInFolder) {
		for (auto it = filesInFolder->First(); it->HasCurrent; it->MoveNext())
		{
			StorageFile^ file = it->Current;
			Geofence^ geofence = GenerateGeofence(file);

			geofences->InsertAt(0, geofence);
			
		}
	});

	return nullptr;
}

void GeoFenceStuff::RegisterBackgroundTask()
{
	boolean taskRegistered = false;
	Platform::String^ exampleTaskName = "GeoBackgroundTask";

	auto iter = BackgroundTaskRegistration::AllTasks->First();
	auto hascur = iter->HasCurrent;

	while (hascur)
	{
		auto cur = iter->Current->Value;

		if (cur->Name == exampleTaskName)
		{
			taskRegistered = true;
			break;
		}

		hascur = iter->MoveNext();
	}
	if (taskRegistered) {

	}
	else
	{

		try
		{
			// Get permission for a background task from the user. If the user has already answered once,
			// this does nothing and the user must manually update their preference via PC Settings.
			task<BackgroundAccessStatus> requestAccessTask(BackgroundExecutionManager::RequestAccessAsync());
			requestAccessTask.then([this](BackgroundAccessStatus backgroundAccessStatus)
			{
				
				// Regardless of the answer, register the background task. If the user later adds this application
				// to the lock screen, the background task will be ready to run.

				// Create a new background task builder
				BackgroundTaskBuilder^ geofenceTaskBuilder = ref new BackgroundTaskBuilder();

				geofenceTaskBuilder->Name = "GeoBackgroundTask";
				//geofenceTaskBuilder->TaskEntryPoint = "BackgroundTask.Background";
				geofenceTaskBuilder->TaskEntryPoint = "BackgroundTask.GeofenceBackgroundTask";

				// Create a new location trigger
				auto trigger = ref new LocationTrigger(LocationTriggerType::Geofence);

				// Associate the location trigger with the background task builder
				geofenceTaskBuilder->SetTrigger(trigger);


				// Register the background task
				geofenceTask = geofenceTaskBuilder->Register();

				// Register for background task completion notifications
				taskCompletedToken = geofenceTask->Completed::add(ref new BackgroundTaskCompletedEventHandler(this, &GeoFenceStuff::OnCompleted));


				// Check the background access status of the application and display the appropriate status message
				switch (backgroundAccessStatus)
				{
				case BackgroundAccessStatus::Unspecified:
				case BackgroundAccessStatus::Denied:
					rootPage->NotifyUser("Not able to run in background. Application must be added to the lock screen.",
						NotifyType::ErrorMessage);
					break;

				default:
					rootPage->NotifyUser("Background task registered.", NotifyType::StatusMessage);

					// Need tp request access to location
					// This must be done with background task registeration
					// because the background task cannot display UI
					RequestLocationAccess();
					break;
				}
			});
		}
		catch (Exception^ ex)
		{
			rootPage->NotifyUser(ex->ToString(), NotifyType::ErrorMessage);

		}
	}
}

void GeoFenceStuff::RequestLocationAccess()
{
	task<GeolocationAccessStatus> geolocationAccessRequestTask(Windows::Devices::Geolocation::Geolocator::RequestAccessAsync());
	geolocationAccessRequestTask.then([this](task<GeolocationAccessStatus> accessStatusTask)
	{
		auto accessStatus = accessStatusTask.get();

		switch (accessStatus)
		{
		case GeolocationAccessStatus::Allowed:
			break;
		case GeolocationAccessStatus::Denied:
			rootPage->NotifyUser("Access to location is denied.", NotifyType::ErrorMessage);
			break;
		case GeolocationAccessStatus::Unspecified:
			rootPage->NotifyUser("Unspecified error!", NotifyType::ErrorMessage);
			break;
		}
	});
}

void GeoFenceStuff::OnCompleted(BackgroundTaskRegistration^ task, Windows::ApplicationModel::Background::BackgroundTaskCompletedEventArgs^ args)
{
	// Update the UI with progress reported by the background task
	// We need to dispatch to the UI thread to display the output
	Windows::UI::Core::CoreDispatcher^ Dispatcher;
	Dispatcher->RunAsync(
		CoreDispatcherPriority::Normal,
		ref new DispatchedHandler(
			[this, args]()
	{
		try
		{
			// Throw an exception if the background task had an unrecoverable error
			args->CheckResult();

			// Update the UI with the completion status of the background task
			auto settings = ApplicationData::Current->LocalSettings->Values;
			if (settings->HasKey("Status"))
			{
				rootPage->NotifyUser(safe_cast<String^>(settings->Lookup("Status")), NotifyType::StatusMessage);
			}

			// add background events to listbox
		//	FillEventListBoxWithExistingEvents();
		}
		catch (Exception^ ex)
		{
			// The background task had an error
			rootPage->NotifyUser(ex->Message, NotifyType::ErrorMessage);
		}
	},
			CallbackContext::Any
		)
		);
}


Platform::String^ GeoFenceStuff::convertStdString(std::string e) {
	std::wstring widestr = std::wstring(e.begin(), e.end());

	const wchar_t* wchart = widestr.c_str();
	return ref new String(wchart);

}