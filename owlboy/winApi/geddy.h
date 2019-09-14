#pragma once
#include "gameNode.h"
#include "animation.h"
#include "bullet.h"

#define GEDDYSPEED 2
enum GEDDYMOVING
{
	GIDLE,
	GHANG,
	GRELOAD,
	GMOVE,
	GJUMP,
	GLANDING,
	GHANGUP,
	GHANGDOWN
};
//�Ե� �� ����ü
struct Arm
{
	Image* img1;
	float angle;
	int currentX;
	int currentY;
	int count;
};

class geddy : public gameNode
{
private:
	Graphics * _graphics;
	Arm _Arm;
	image* _img;
	geddyBullet* _bullet;
	animation* _curPlayAnim;
	animation* _ani;//�Ե� ��
	animation* _ani3;//�Ե� ��ȯ ����Ʈ

	image* _imgGeddy;//�Ե� ��ȯ ����Ʈ

	RECT _rc;
	RECT _rc1;
	int _xGeddy;
	int _yGeddy;

	bool _geddyEf;

	float _moveAmountY;

	bool _isHang;

	bool _isGeddyLeft;

	GEDDYMOVING _geddyMove;
	bool _geddyReload_R;//������ ��� on/off�� bool��
	int _motionChange; //��� �ٲٴ� ī��Ʈ....�� ����....
	bool _playGeddyMotion;
	bool _geddyUpBang;

	bool _bangBang; //�Ե� ���� ������ �ƴ���...

	bool _isCollision;

	float _angle;

	bool _landingEnd;
	float _effectVolume;

	bool _combiDamage;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void fire(void);

	void hang();

	bool getIsCollision() { return _isCollision; }
	void setIsCollision(bool b) { _isCollision = b; }

	bool getCombiDamage() { return _combiDamage; }
	void setCombiDamage(bool e) { _combiDamage = e; }

	int getX() { return _xGeddy; }
	void setX(int i) { _xGeddy = i; }
	int getY() { return _yGeddy; }
	void setY(int i) { _yGeddy = i; }

	int* getXpointer() { return &_xGeddy; }
	int* getYpointer() { return &_yGeddy; }

	bool getIsGeddyLeft() { return _isGeddyLeft; }
	void setIsGeddyLeft(bool a) { _isGeddyLeft = a; }

	bool getIsHang() { return _isHang; }
	void setIsHang(bool f) { _isHang = f; }

	RECT getRect() { return _rc; }
	geddyBullet* getBullet(void) { return _bullet; }
	void setVolume(float effectVolume) { _effectVolume = effectVolume; }
	geddy() {}
	~geddy() {}
};

