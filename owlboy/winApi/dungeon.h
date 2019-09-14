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
	RECT _rc[2]; //�ٴ��浹�ϴ� �簢�� x
	
	//��ư�浹
	RECT _rcButton, _rcPush,_rcTemp;
	//�� ��������
	RECT _doorOpenRc[2];
	//�� ��������
	RECT _doorCloseRc;


	RECT _nextScene;
	

	float _rndTimeCount;   //���������� ī����
	float _worldTimeCount; //���� ī����
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

