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
//게디 팔 구조체
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
	animation* _ani;//게디 몸
	animation* _ani3;//게디 소환 이펙트

	image* _imgGeddy;//게디 소환 이펙트

	RECT _rc;
	RECT _rc1;
	int _xGeddy;
	int _yGeddy;

	bool _geddyEf;

	float _moveAmountY;

	bool _isHang;

	bool _isGeddyLeft;

	GEDDYMOVING _geddyMove;
	bool _geddyReload_R;//재장전 모션 on/off용 bool값
	int _motionChange; //모션 바꾸는 카운트....용 변수....
	bool _playGeddyMotion;
	bool _geddyUpBang;

	bool _bangBang; //게디가 총을 쌋는지 아닌지...

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

