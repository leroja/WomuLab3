#include "pch.h"
#include "GeoFenceStuff.h"



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



GeoFenceStuff::GeoFenceStuff()
{
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

			}
			catch (COMException^ ex)
			{

			}
		});
	}
	
	//position.Latitude = 0.0; // get from room
	//position.Longitude = 0.0; // get from room
	//position.Altitude = 0.0;
	//double radius = 0.0; // get radius from room
	//String^ fencekey = ""; // get fencekey from room

	//MonitoredGeofenceStates mask = static_cast<MonitoredGeofenceStates>(0);
	//mask = mask | MonitoredGeofenceStates::Entered;
	//mask = mask | MonitoredGeofenceStates::Exited;


	//Geocircle^ geocircle = ref new Geocircle(position, radius);
	//TimeSpan dwelltime;
	//dwelltime.Duration = 1;

	//geofence = ref new Geofence(fencekey, geocircle, mask, false, dwelltime);


	// test  /// ta bort 
	Geolocator^ geolocator = ref new Geolocator;

	BasicGeoposition position;
	geolocator->DesiredAccuracy = PositionAccuracy::High;
	task<Geoposition^> geopositionTask(geolocator->GetGeopositionAsync());
	geopositionTask.then([this, &position, &geofence](task<Geoposition^> getPosTask)
	{
		try
		{
			// Get will throw an exception if the task was canceled or failed with an error
			Geoposition^ pos = getPosTask.get();

			auto Lati = pos->Coordinate->Point->Position.Latitude;
			auto Longi = pos->Coordinate->Point->Position.Longitude;
			position.Latitude = Lati;
			position.Longitude = Longi;
			position.Altitude = 0.0;
			double radius = 1000.0;
			String^ fencekey = "test";

			MonitoredGeofenceStates mask = static_cast<MonitoredGeofenceStates>(0);
			mask = mask | MonitoredGeofenceStates::Entered;
			mask = mask | MonitoredGeofenceStates::Exited;


			Geocircle^ geocircle = ref new Geocircle(position, radius);
			TimeSpan dwelltime;
			dwelltime.Duration = 1;

			geofence = ref new Geofence(fencekey,geocircle,mask,false,dwelltime);

		}
		catch (task_canceled&)
		{

		}
		catch (Exception^ ex)
		{

		}
	});

	return geofence;
}

Platform::Collections::Vector<Windows::Devices::Geolocation::Geofencing::Geofence^>^ GeoFenceStuff::GenerateAllGeofences()
{
	StorageFolder^ roamingFolder = ApplicationData::Current->RoamingFolder;
	StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;
	auto createFileTask = create_task(localFolder->GetFilesAsync()).then([=](IVectorView<StorageFile^>^ filesInFolder) {
		//Iterate over the results and print the list of files
		// to the visual studio output window
		for (auto it = filesInFolder->First(); it->HasCurrent; it->MoveNext())
		{
			StorageFile^ file = it->Current;

			String^ output = file->Name + "\n";
			OutputDebugString(output->Begin());

			Geofence^ geofence = GenerateGeofence(file);
			geofences->InsertAt(0, geofence);
			
		}
	});

	return nullptr;
	//return list;
}

void GeoFenceStuff::RegisterBackgroundTask()
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
			geofenceTaskBuilder->TaskEntryPoint = "BackgroundTask.GeofenceBackgroundTask.";

			// Create a new location trigger
			auto trigger = ref new LocationTrigger(LocationTriggerType::Geofence);

			// Associate the location trigger with the background task builder
			geofenceTaskBuilder->SetTrigger(trigger);

			// If it is important that there is user presence and/or
			// internet connection when OnCompleted is called
			// the following could be called before calling Register()
			// SystemCondition^ condition = ref new SystemCondition(SystemConditionType::UserPresent | SystemConditionType::InternetAvailable);
			// geofenceTaskBuilder->AddCondition(condition);

			// Register the background task
			geofenceTask = geofenceTaskBuilder->Register();

			// Register for background task completion notifications
	//		taskCompletedToken = geofenceTask->Completed::add(ref new BackgroundTaskCompletedEventHandler(this, &GeoFenceStuff::OnCompleted));


			// Check the background access status of the application and display the appropriate status message
			switch (backgroundAccessStatus)
			{
			case BackgroundAccessStatus::Unspecified:
			case BackgroundAccessStatus::Denied:
				//rootPage->NotifyUser("Not able to run in background. Application must be added to the lock screen.",
				//	NotifyType::ErrorMessage);
				break;

			default:
				//rootPage->NotifyUser("Background task registered.", NotifyType::StatusMessage);

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
		//rootPage->NotifyUser(ex->ToString(), NotifyType::ErrorMessage);

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
			//rootPage->NotifyUser("Access to location is denied.", NotifyType::ErrorMessage);
			break;
		case GeolocationAccessStatus::Unspecified:
			//rootPage->NotifyUser("Unspecified error!", NotifyType::ErrorMessage);
			break;
		}
	});
}