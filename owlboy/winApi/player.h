#pragma once
#include "singletonbase.h"

//�÷��̾� �̵� ������
#define PLAYERSPEED 2
#define GRAVITYOTUS 0.1f 

enum OTUSMOVING
{
	otIDLE,
	otRUN,
	otJUMP,
	otCOMBI,
	otFLY,
	otDAMAGE,
	otSPIN,
	otDIE
};

class player : public singletonBase <player>
{
private:
	HDC _hdc;
	
	image* _img;
	image* _endImg;
	RECT _rc;
	RECT _rc1;
	RECT _rcAtk;
	RECT _rcHit;
	int _x;
	int _y;
	OTUSMOVING _otusMove;
	int _count;
	int _frameX , _frameY;
	bool _isLeft; //�������� �ƴ��� �Ǻ��ϴ� bool��
	bool _onceSpin; //�ѹ� ȸ������ ���� bool��
	bool _attackOn; //�����ѹ���....
	bool _isCollision; // �÷��̾ ������ �浹��?

	float _moveAmountY;
	float _gravity;

	float _cursorAngle;

	bool _geddyOn;

	float _effectVolume;

	float _hp;
	bool _otusDamageOn;
	bool _otusIn;

	int _damageCount;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//������
	HRESULT endSceneInit(void);
	void endSceneUpdate(void);
	void endRender(void);

	void setHDC(HDC hdc) { _hdc = hdc; }

	image* getImg() { return _img; }

	int getX() { return _x; }
	void setX(int x) { _x = x; }
	int getY() { return _y; }
	void setY(int y) { _y = y; }

	int* getXpointer() { return &_x; }
	int* getYpointer() { return &_y; }

	RECT playerAttackRect(void) { return _rcAtk; }
	RECT playerHitRect(void) { return _rcHit; }
	RECT getRect() { return _rc; }
	bool getIsCollision() { return _isCollision; }
	void setIsCollision(bool b) { _isCollision = b; }

	bool getOtusDamageOn() { return _otusDamageOn; }
	void setOtusDamageOn(bool r) { _otusDamageOn = r; }

	bool getOtusIn() { return _otusIn; }
	void setOtusIn(bool q) { _otusIn = q; }
	
	float getMoveAmountY() { return _moveAmountY; }

	void setGeddyOn(bool b) { _geddyOn = b; }
	bool getGeddyOn() { return _geddyOn; }

	OTUSMOVING getOtusState() { return _otusMove; }
	void setOtusState(OTUSMOVING o) { _otusMove = o; }

	bool getIsLeft() { return _isLeft; }
	void setIsLeft (bool g) { _isLeft = g; }

	float getCursorAngle() { return _cursorAngle; }

	void setVolume(float effectVolume) { _effectVolume = effectVolume; }

	float getHp(void) { return _hp; }
	void setHp(float hp) { _hp = hp; }

	player() {}
	~player() {}
};