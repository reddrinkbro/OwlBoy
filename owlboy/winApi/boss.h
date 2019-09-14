#pragma once
#include "gameNode.h"
#include "bossShield.h"
#include "bullet.h"
#include "progressBar.h"

#define FRAMECOUNT 0.1f

enum bossState			//보스상태
{
	STAND = 0,			//가만히 있을때
	MOVE,				//이동
	SHOOTING,			//총알을 쏠때
	SHIELDEQIP,			//방패 장착상태
	MOVESHIELD,			//방패쪽으로 이동
	JUMP,				//점프
	HIT,				//맞았을대
	CHANGE,				//플라잉상태로 변하기
	BOSS_DIE			//사망
};
class boss : public gameNode
{
private:
	bossState _bossState;
	image* _bossStart;
	image* _boss;
	image* _bossHpBar;
	bossShield* _bossShield;
	bossBullet* _bossBullet;
	progressBar* _progressBar;
	RECT _rc;

	float _x, _y;
	float _hp;
	float _count;
	int _startingCount;		//처음 시작할때 루프돌기위한 카운터
	float _speed;
	bool _isFly;			//날고있는가
	bool _isStart;			//보스가 석상상태가 아닌지
	bool _isLeft;			//왼쪽인가
	bool _isAbleHit;		//피격이 되는가
	bool _playBossSound;	//보스맵 사운드 켜기
public:
	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);
	void bossStart(void);		//석상일때 보스
	void bossFrame(void);		//보스 함수 모음
	void bossMove(void);		//보스 이동
	void bossHit(void);			//보스 맞았을때
	void bossMoveShield(void);	//보스가 방패쪽으로 이동
	void bossShieldEqip(void);	//보스 방패 장착
	void bossJump(void);		//보스 점프
	void bossShooting(void);	//보스 총쏠때
	void bossChageFly(void);	//플라잉 상태로 바꿈
	void decreaseHp(void);		//Hp 감소
	void bossDie(void);			//보스 사망
	bossShield* getShield(void) { return _bossShield; }
	bossBullet* getBullet(void) { return _bossBullet; }
	bool getPlayBossSound(void) { return _playBossSound; }
	void setPlayBossSound(bool playBossSound) { _playBossSound = playBossSound; }
	bossState getBossState(void) { return _bossState; }
	void setBossState(bossState state) { _bossState = state; }
	RECT getRect(void) { return _rc; }
	bool getIsStart(void) { return _isStart; }
	boss(){}
	~boss(){}
};

