#include "pch.h"
#include "Background.h"



using namespace Concurrency;
using namespace Platform;
using namespace Windows::ApplicationModel::Background;
using namespace Windows::Data::Json;
using namespace Windows::Data::Xml::Dom;
using namespace Windows::Devices::Geolocation;
using namespace Windows::Devices::Geolocation::Geofencing;
using namespace Windows::Foundation;
using namespace Windows::Globalization::DateTimeFormatting;
using namespace Windows::Storage;
using namespace Windows::UI::Notifications;


Background::Background()
{

}


Background::~Background()
{

}


void Background::Run(IBackgroundTaskInstance^ taskInstance)
{
	// Get the deferral object from the task instance
	Platform::Agile<BackgroundTaskDeferral> deferral(taskInstance->GetDeferral());

	// Associate a cancellation handler with the background task
	taskInstance->Canceled += ref new BackgroundTaskCanceledEventHandler(this, &Background::OnCanceled);

	Geolocator^ geolocator = ref new Geolocator();

	task<Geoposition^> geopositionTask(geolocator->GetGeopositionAsync(), geopositionTaskTokenSource.get_token());
	geopositionTask.then([this, deferral, geolocator](task<Geoposition^> getPosTask)
	{
		DateTimeFormatter^ dateFormatter = ref new DateTimeFormatter("longtime");
		auto settings = ApplicationData::Current->LocalSettings;

		try
		{
			// Get will throw an exception if the task was canceled or failed with an error
			Geoposition^ pos = getPosTask.get();

			// Write to LocalSettings to indicate that this background task ran
			settings->Values->Insert("Status", "Time: " + dateFormatter->Format(pos->Coordinate->Timestamp));
			settings->Values->Insert("Latitude", pos->Coordinate->Point->Position.Latitude.ToString());
			settings->Values->Insert("Longitude", pos->Coordinate->Point->Position.Longitude.ToString());
			settings->Values->Insert("Accuracy", pos->Coordinate->Accuracy.ToString());
		}
		catch (Platform::AccessDeniedException^)
		{
			// Write to LocalSettings to indicate that this background task ran
			settings->Values->Insert("Status", "Disabled");
			settings->Values->Insert("Latitude", "No data");
			settings->Values->Insert("Longitude", "No data");
			settings->Values->Insert("Accuracy", "No data");
		}
		catch (task_canceled&)
		{
		}
		catch (Exception^ ex)
		{
			settings->Values->Insert("Latitude", "No data");
			settings->Values->Insert("Longitude", "No data");
			settings->Values->Insert("Accuracy", "No data");

#if (WINAPI_FAMILY == WINAPI_FAMILY_PC_APP)
			// If there are no location sensors GetGeopositionAsync()
			// will timeout -- that is acceptable.

			if (ex->HResult == HRESULT_FROM_WIN32(WAIT_TIMEOUT))
			{
				settings->Values->Insert("Status", "Operation accessing location sensors timed out. Possibly there are no location sensors.");
			}
			else
#endif
			{
				settings->Values->Insert("Status", ex->ToString());
			}
		}

		// Indicate that the background task has completed
		deferral->Complete();
	});
}

// Handles background task cancellation
void Background::OnCanceled(IBackgroundTaskInstance^ taskInstance, BackgroundTaskCancellationReason reason)
{
	// Cancel the async operation
	geopositionTaskTokenSource.cancel();
}