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


GeoFenceStuff::GeoFenceStuff()
{
}


GeoFenceStuff::~GeoFenceStuff()
{
}

Windows::Devices::Geolocation::Geofencing::Geofence ^ GeoFenceStuff::GenerateGeofence()
{
	Geofence^ geofence = nullptr;


	return geofence;
}

Platform::Collections::Vector<Windows::Devices::Geolocation::Geofencing::Geofence^>^ GeoFenceStuff::GenerateAllGeofences()
{

	StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;
	auto createFileTask = create_task(localFolder->GetFilesAsync()).then([=](IVectorView<StorageFile^>^ filesInFolder) {
		//Iterate over the results and print the list of files
		// to the visual studio output window
		for (auto it = filesInFolder->First(); it->HasCurrent; it->MoveNext())
		{
			StorageFile^ file = it->Current;

			String^ output = file->Name + "\n";
			OutputDebugString(output->Begin());

			Geofence^ geofence = GenerateGeofence();
			
		}
	});

	return nullptr;

}
