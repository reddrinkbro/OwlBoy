#pragma once
#include "singletonBase.h"
class optionManager : public singletonBase<optionManager>
{
private:
	float _musicVolume;
	float _soundVolume;
public:
	HRESULT init();
	void release(void);
	void settingVolume(float musicVolume, float soundVolume);
	float getMusicVolume(void) { return _musicVolume; }
	float getSoundVolume(void) { return _soundVolume; }
	optionManager(){}
	~optionManager(){}
};

