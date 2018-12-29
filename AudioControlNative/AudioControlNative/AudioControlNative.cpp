
#include "stdafx.h"
#include <mmdeviceapi.h>
#include <endpointvolume.h>

#include "AudioControlNative.h"

void SetMasterVolume(float volume)
{
	IMMDeviceEnumerator *deviceEnumerator = NULL;
	IMMDevice *defaultDevice = NULL;
	IAudioEndpointVolume *endpointVolume = NULL;

	CoInitialize(NULL);

	if (CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator) == S_OK)
	{
		if (deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice) == S_OK)
		{
			if (defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume) == S_OK)
			{
				endpointVolume->SetMasterVolumeLevelScalar((float)volume, NULL);
				endpointVolume->Release();
			}

			defaultDevice->Release();
		}

		deviceEnumerator->Release();
	}

	CoUninitialize();
}

float GetMasterVolume()
{
	float currentVolume = 0;
	IMMDeviceEnumerator *deviceEnumerator = NULL;
	IMMDevice *defaultDevice = NULL;
	IAudioEndpointVolume *endpointVolume = NULL;

	CoInitialize(NULL);

	if (CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator) == S_OK)
	{
		if (deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice) == S_OK)
		{
			if (defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume) == S_OK)
			{
				endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);
				endpointVolume->Release();
			}

			defaultDevice->Release();
		}

		deviceEnumerator->Release();
	}

	CoUninitialize();

	return currentVolume;
}