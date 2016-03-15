//
// ChangePicView.xaml.cpp
// Implementation of the ChangePicView class
//

#include "pch.h"
#include "ChangePicView.xaml.h"
#include "Wall.h"
#include "WallView1.xaml.h"

using namespace Lab3;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Storage;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::Media::Capture;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

ChangePicView::ChangePicView()
{
	InitializeComponent();
}



void Lab3::ChangePicView::NewPic_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	CameraCaptureUI^ camera = ref new CameraCaptureUI();

	concurrency::task<StorageFile^>(camera->CaptureFileAsync(CameraCaptureUIMode::Photo)).then([this](StorageFile^ file)
	{
		if (file == nullptr) {
			return;
		}
		concurrency::task<Streams::IRandomAccessStream^>(file->OpenAsync(FileAccessMode::Read)).then([this](Streams::IRandomAccessStream^ stream) {
			setPic(stream);
			//this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(WallView1::typeid), this->wall);
			this->Frame->GoBack();
		});
	});
}


void Lab3::ChangePicView::OldPic_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Image t1;
	auto picker = ref new Windows::Storage::Pickers::FileOpenPicker();
	picker->ViewMode = Windows::Storage::Pickers::PickerViewMode::Thumbnail;
	picker->SuggestedStartLocation = Windows::Storage::Pickers::PickerLocationId::PicturesLibrary;
	picker->FileTypeFilter->Append(".jpg");
	picker->FileTypeFilter->Append(".jpeg");
	picker->FileTypeFilter->Append(".PNG");
	concurrency::task<StorageFile^>(picker->PickSingleFileAsync()).then([this](StorageFile^ file)
	{
		if (file == nullptr) {
			return;
		}
		concurrency::task<Streams::IRandomAccessStream^>(file->OpenAsync(FileAccessMode::Read)).then([this](Streams::IRandomAccessStream^ stream) {
			setPic(stream);	
			//this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(WallView1::typeid), this->wall);
			this->Frame->GoBack();
		});
	});

}


void Lab3::ChangePicView::Back_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(WallView1::typeid), this->wall);
}

void Lab3::ChangePicView::setPic(Windows::Storage::Streams::IRandomAccessStream ^ stream)
{
	BitmapImage^ bitmapImage = ref new BitmapImage();
	bitmapImage->SetSource(stream);
	Image^ image = ref new Image();
	image->Source = bitmapImage;
	this->wall->setWallImage(image);
}

void Lab3::ChangePicView::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs ^ e)
{
	this->wall = (Wall^)e->Parameter;
}
