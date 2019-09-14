#pragma once
#include "gameNode.h"
#include "progressBar.h"
struct volume
{
	progressBar* _progressBar;
	RECT rc;
	float x, y;
	float volumeValue;
};
class optionWindow : public gameNode
{
private:
	Graphics * _graphics;
	image * _image;
	Image* _backArrow;
	volume _volume[3];
	RECT _optionWindowRc;
	RECT _arrowRc;
	
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void volemSetting(void);
	float masterVolume(void);
	float musicVolume(void);
	float soundVolume(void);
	//뒤로가기버튼 가져오기
	RECT getBackArrowRect(void) { return _arrowRc; }
	optionWindow(){}
	~optionWindow(){}
};

