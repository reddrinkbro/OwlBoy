#pragma once
#include "gameNode.h"
#include "bossShield.h"
#include "bullet.h"
#include "progressBar.h"

#define FRAMECOUNT 0.1f

enum bossState			//��������
{
	STAND = 0,			//������ ������
	MOVE,				//�̵�
	SHOOTING,			//�Ѿ��� ��
	SHIELDEQIP,			//���� ��������
	MOVESHIELD,			//���������� �̵�
	JUMP,				//����
	HIT,				//�¾�����
	CHANGE,				//�ö��׻��·� ���ϱ�
	BOSS_DIE			//���
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
	int _startingCount;		//ó�� �����Ҷ� ������������ ī����
	float _speed;
	bool _isFly;			//�����ִ°�
	bool _isStart;			//������ ������°� �ƴ���
	bool _isLeft;			//�����ΰ�
	bool _isAbleHit;		//�ǰ��� �Ǵ°�
	bool _playBossSound;	//������ ���� �ѱ�
public:
	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);
	void bossStart(void);		//�����϶� ����
	void bossFrame(void);		//���� �Լ� ����
	void bossMove(void);		//���� �̵�
	void bossHit(void);			//���� �¾�����
	void bossMoveShield(void);	//������ ���������� �̵�
	void bossShieldEqip(void);	//���� ���� ����
	void bossJump(void);		//���� ����
	void bossShooting(void);	//���� �ѽ�
	void bossChageFly(void);	//�ö��� ���·� �ٲ�
	void decreaseHp(void);		//Hp ����
	void bossDie(void);			//���� ���
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

