#pragma once
#include "gameNode.h"
#include "stage.h"
class endingScene : public gameNode
{
private:
	image* _image;
	image* _image1;//�� ��Ʈ �̹���

	float _bgSpeedX;
	float _bgSpeedF;

	float _rndTimeCount;   //���������� ī����
	float _worldTimeCount; //���� ī����
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

