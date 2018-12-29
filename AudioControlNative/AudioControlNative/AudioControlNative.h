#pragma once

#ifdef AUDIO_CONTROL_LIB
#define MSG_EXPORT __declspec(dllexport)
#else 
#define MSG_EXPORT __declspec(dllimport)
#endif

extern "C" {
	MSG_EXPORT float GetMasterVolume();
	MSG_EXPORT void SetMasterVolume(float volume);
}