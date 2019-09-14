#pragma once
#include "stage.h"

class dungeon : public stage
{
private:

	image* _imageBush1;
	image* _imageBush2;
	image* _imageBush3;
	image* _imageBush4;
	image* _imageDoor;
	image* _imageButton;

	bool _isPlaySound;
	RECT _rc[2]; //바닥충돌하는 사각형 x
	
	//버튼충돌
	RECT _rcButton, _rcPush,_rcTemp;
	//문 열렸을때
	RECT _doorOpenRc[2];
	//문 닫혔을때
	RECT _doorCloseRc;


	RECT _nextScene;
	

	float _rndTimeCount;   //랜덤프레임 카운터
	float _worldTimeCount; //월드 카운터
	int _bushFrameX;
	int _buttonFrameX;
	int _doorFrameX;
	int _bushCount;
	int _buttonCount;
	int _doorCount;
	int _pushCount;

	bool _buttonStop;
	bool _doorStart;
	bool _doorOk;
	bool _buttonOn;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void nextScene(void);
	virtual void bulletColllsionArea(void);
	void otusAttackCollisionArea(void);
	dungeon(){}
	~dungeon(){}
};

