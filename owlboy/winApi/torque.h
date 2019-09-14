#pragma once
#include "gameNode.h"
#include "bullet.h"
enum torqueState
{
	TORQUE_RELOAD = 0,   //������ ������
	TORQUE_MOVE,		 //�����϶�
	TORQUE_ATTACK		 //�����Ҷ�
};
class torque : public gameNode
{
private:
	torqueBullet * _bullet;
	image* _image;
	RECT _rc;
	torqueState _torqueState;
	float _x, _y;
	float _speed;		   //���� �̵��ӵ�
	float _rndTimeCount;   //���� ���������� ī����
	float _worldTimeCount; //���� ī����
	float _hp;			   //���� ü��
	float _reloadTime;	   //�����ð�
	float _distance;	   //�̵��Ÿ�
	bool _isHit;		   //���Ͱ� �¾Ҵ���
	bool _isAttack;		   //���Ͱ� ����������
	int _currentFrameX;	   //X�����Ӱ�
	int _currentFrameY;	   //y�����Ӱ�
	int _randomMove;	   //���� ������ ����
	int _state;			   //���� ����
public:
	HRESULT init(string strKey, float x, float y);
	void release(void);
	void update(void);
	void render(void);
	void reload(void);
	void attack(void);
	void fire(void);
	//�簢�� ��������
	RECT getRect(void) { return _rc; }
	//���� �̵�
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

