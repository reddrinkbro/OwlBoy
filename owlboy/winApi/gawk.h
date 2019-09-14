#pragma once
#include "gameNode.h"
#include "effect.h"
#define FRAMECOUNT 0.1f

class gawk : public gameNode
{
private:
	image* _image;
	RECT _rc;
	float _x, _y;
	float _speed;	 //몬스터 이동속도
	float _rndTimeCount;   //몬스터 랜덤프레임 카운터
	float _worldTimeCount; //월드 카운터
	int _currentFrameX;	   //X프레임값
	int _currentFrameY;	   //y프레임값
	int _randomMove;	   //몬스터 움직임 방향
	float _hp;
	bool _isHit;	 //몬스터가 맞았는지
public:
	HRESULT init(float x ,float y);
	void release(void);
	void update(void);
	void render(void);

	//사각형 가져오기
	RECT getRect(void) { return _rc; }
	//몬스터 이동
	void move(void);
	void hit(void);
	void sethit(bool hit) { _isHit = hit; }
	float getHp() { return _hp; }
	void setHp(float hp) { _hp = hp; }
	gawk(){}
	~gawk(){}
};

