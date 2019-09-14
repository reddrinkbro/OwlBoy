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
	float _speed;	 //���� �̵��ӵ�
	float _rndTimeCount;   //���� ���������� ī����
	float _worldTimeCount; //���� ī����
	int _currentFrameX;	   //X�����Ӱ�
	int _currentFrameY;	   //y�����Ӱ�
	int _randomMove;	   //���� ������ ����
	float _hp;
	bool _isHit;	 //���Ͱ� �¾Ҵ���
public:
	HRESULT init(float x ,float y);
	void release(void);
	void update(void);
	void render(void);

	//�簢�� ��������
	RECT getRect(void) { return _rc; }
	//���� �̵�
	void move(void);
	void hit(void);
	void sethit(bool hit) { _isHit = hit; }
	float getHp() { return _hp; }
	void setHp(float hp) { _hp = hp; }
	gawk(){}
	~gawk(){}
};

