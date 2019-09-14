#pragma once
#include "gameNode.h"
#include "bullet.h"
enum torqueState
{
	TORQUE_RELOAD = 0,   //가만히 있을때
	TORQUE_MOVE,		 //움직일때
	TORQUE_ATTACK		 //공격할때
};
class torque : public gameNode
{
private:
	torqueBullet * _bullet;
	image* _image;
	RECT _rc;
	torqueState _torqueState;
	float _x, _y;
	float _speed;		   //몬스터 이동속도
	float _rndTimeCount;   //몬스터 랜덤프레임 카운터
	float _worldTimeCount; //월드 카운터
	float _hp;			   //몬스터 체력
	float _reloadTime;	   //장전시간
	float _distance;	   //이동거리
	bool _isHit;		   //몬스터가 맞았는지
	bool _isAttack;		   //몬스터가 공격중인지
	int _currentFrameX;	   //X프레임값
	int _currentFrameY;	   //y프레임값
	int _randomMove;	   //몬스터 움직임 방향
	int _state;			   //몬스터 상태
public:
	HRESULT init(string strKey, float x, float y);
	void release(void);
	void update(void);
	void render(void);
	void reload(void);
	void attack(void);
	void fire(void);
	//사각형 가져오기
	RECT getRect(void) { return _rc; }
	//몬스터 이동
	void move(void);
	void hit(void);
	void playerLook(void);
	float getHp(void) { return _hp; }
	void setHp(float hp) { _hp = hp; }
	bool getIsHit(void) { return _isHit; }
	void setIsHit(bool isHit) { _isHit = isHit; }
	void playerHit(void);
	torque(){}
	~torque(){}
};

