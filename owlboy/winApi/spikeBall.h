#pragma once
#include "gameNode.h"

class spikeBall : public gameNode
{
private:
	image* _image;
	RECT _rc;
	float _x, _y;
	float _hp;
	float _speed;		   //몬스터 이동속도
	float _rndTimeCount;   //몬스터 랜덤프레임 카운터
	float _worldTimeCount; //월드 카운터
	int _currentFrameX;	   //X프레임값
	int _randomMove;	   //몬스터 움직임 방향
	int _distance;		   //몬스터 이동거리
public:
	HRESULT init(float x,float y);
	void release(void);
	void update(void);
	void render(void);

	//사각형 가져오기
	RECT getRect(void) { return _rc; }
	int getX(void) { return _x; }
	int getY(void) { return _y; }
	//몬스터 이동
	void move(void);
	float getHp(void) { return _hp; }
	void setHp(float hp) { _hp = hp; }
	spikeBall(){}
	~spikeBall(){}
};

