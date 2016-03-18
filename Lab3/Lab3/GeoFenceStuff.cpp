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
using namespace Concurrency;
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

Windows::Devices::Geolocation::Geofencing::Geofence ^ GeoFenceStuff::GenerateGeofence(std::vector<std::string> vec)
{


		Geofence^ geofence;
		BasicGeoposition position;
		position.Latitude = ::atof(vec[2].c_str());
		position.Longitude = ::atof(vec[3].c_str());
		position.Altitude = 0.0;
		double temp = ::atof(vec[26].c_str());
		double radius;
		if (temp == 0) {
			radius = 100;
		}
		else {
			radius = (sqrt(temp)) / 1.5;
		}
		String^ fencekey = convertStdString(vec[0]);

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

Windows::Devices::Geolocation::Geofencing::Geofence ^ GeoFenceStuff::GenerateGeofence(Room ^ room)
{
	Geofence^ geofence = nullptr;

	if (room != nullptr)
	{
		BasicGeoposition position;
		position.Latitude = room->GetLatitude();
		position.Longitude = 0.0; room->GetLongitude();
		position.Altitude = 0.0;
		double radius;
		if (room->GetFloor() == nullptr || room->GetFloor()->GetArea() == 0 ) {
			radius = 100;
		}
		else {
			radius = (sqrt(room->GetFloor()->GetArea())) / 1.5;
		}
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

void GeoFenceStuff::GenerateAllGeofences()
{

	geofences->Clear();
	StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;
	auto createFileTask = create_task(localFolder->GetFilesAsync()).then([=](IVectorView<StorageFile^>^ filesInFolder) {
		for (auto it = filesInFolder->First(); it->HasCurrent; it->MoveNext())
		{

			create_task(FileIO::ReadTextAsync(it->Current)).then([this](task<String^> task)
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

					Geofence^ geofence = GenerateGeofence(test1);

					geofences->InsertAt(0, geofence);
				}
				catch (COMException^ ex)
				{
					OutputDebugString(ex->ToString()->Begin());
				}
			});			
		}
	});
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
			geofenceTask = safe_cast<BackgroundTaskRegistration^>(cur);
			break;
		}

		hascur = iter->MoveNext();
	}
	if (taskRegistered) {
	//	FillEventListBoxWithExistingEvents();
		GenerateAllGeofences();

		// Register for background task completion notifications
		taskCompletedToken = geofenceTask->Completed::add(ref new BackgroundTaskCompletedEventHandler(this, &GeoFenceStuff::OnCompleted));

		try
		{
			// Check the background access status of the application and display the appropriate status message
			switch (BackgroundExecutionManager::GetAccessStatus())
			{
			case BackgroundAccessStatus::Unspecified:
			case BackgroundAccessStatus::Denied:
				rootPage->NotifyUser("Not able to run in background.", NotifyType::ErrorMessage);
				break;

			default:
				rootPage->NotifyUser("Background task is already registered. Waiting for next update...", NotifyType::StatusMessage);
				break;
			}
		}
		catch (Exception^ ex)
		{
			OutputDebugString(ex->ToString()->Begin());
			rootPage->NotifyUser(ex->ToString(), NotifyType::ErrorMessage);
		}

		//UpdateButtonStates(/*registered:*/ true);
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
				GenerateAllGeofences();
			});
		}
		catch (Exception^ ex)
		{
			rootPage->NotifyUser(ex->ToString(), NotifyType::ErrorMessage);
			OutputDebugString(ex->ToString()->Begin());
		}
	}
}

void GeoFenceStuff::addGeofence(Room ^ room)
{

	String^ title = room->GetTitle();
	bool exists;
	unsigned int index = 0;
	Windows::Foundation::Collections::IVector<Windows::Devices::Geolocation::Geofencing::Geofence^>^ vec = geofences;
	Platform::Collections::Vector<Platform::String^>^ geofencesID = ref new Platform::Collections::Vector<Platform::String^>();

	for each (auto var in vec)
	{
		geofencesID->Append(var->Id);
	}

	exists = geofencesID->IndexOf(title, &index);
	
	if (exists)
	{
		geofences->RemoveAt(index);
	}
	Geofence^ geo = GenerateGeofence(room);

	geofences->InsertAt(0, geo);
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

			// do app work here
			// add background events to listbox
		//	FillEventListBoxWithExistingEvents();
		}
		catch (Exception^ ex)
		{
			// The background task had an error
			rootPage->NotifyUser(ex->Message, NotifyType::ErrorMessage);
			OutputDebugString(ex->ToString()->Begin());
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