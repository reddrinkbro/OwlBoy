#pragma once
#include "gameNode.h"

#define FRAMECOUNT 0.1f

enum state
{
	FLYING =0,				    //방패가 공중에 있는가
	FALL,					//방패가 땅에 떨어졌는가
};
struct tagShield
{
	image * _image;
	RECT _rc;
	float _x, _y;
	float _angle;
	float _isLeft;
	bool _isFall;
};
class bossShield : public gameNode
{
private:
	vector<tagShield> _vShield;
	vector<tagShield>::iterator _viShield;
	int _state;				//방패의 현재 상태
	float _count;
	float _time;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void appear(float x, float y, bool isLeft);			//방패 생성
	void shieldFlying(void);							//공중에서 방패 함수
	void shieldFalling(void);							//땅에 떨어졌을때 방패 프레임
	void shieldCatch(void);								//보스가 방패를 잡았을때 상태 바꾸기위한 함수
	void bumpGround(void);								//땅에 부딪혔을때

	vector<tagShield> getVShield(void) { return _vShield; }

	bossShield(){}
	~bossShield(){}
};

