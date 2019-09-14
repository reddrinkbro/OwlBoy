#pragma once
#include "gameNode.h"
#include "stage.h"
class endingScene : public gameNode
{
private:
	image* _image;
	image* _image1;//맵 폰트 이미지

	float _bgSpeedX;
	float _bgSpeedF;

	float _rndTimeCount;   //랜덤프레임 카운터
	float _worldTimeCount; //월드 카운터
	int _otusFrameX, _otusFrameY;
	
	bool _isPlaySound;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	endingScene(){}
	~endingScene(){}
};

