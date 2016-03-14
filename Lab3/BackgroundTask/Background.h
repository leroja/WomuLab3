#pragma once

#include "pch.h"

ref class Background sealed : public Windows::ApplicationModel::Background::IBackgroundTask
{
public:
	Background();

	// Inherited via IBackgroundTask
	virtual void Run(Windows::ApplicationModel::Background::IBackgroundTaskInstance ^taskInstance);

private:
	void OnCanceled(Windows::ApplicationModel::Background::IBackgroundTaskInstance^ taskInstance, Windows::ApplicationModel::Background::BackgroundTaskCancellationReason reason);
	~Background();

	Concurrency::cancellation_token_source geopositionTaskTokenSource;
};

