#include "stdafx.h"
#include "optionManager.h"

HRESULT optionManager::init()
{
	_musicVolume = 1.0f;
	_soundVolume = 1.0f;
	return S_OK;
}

void optionManager::release(void)
{
}

void optionManager::settingVolume(float musicVolume, float soundVolume)
{
	_musicVolume = musicVolume;
	_soundVolume = soundVolume;
}
