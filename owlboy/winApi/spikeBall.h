#pragma once
#include "gameNode.h"

class spikeBall : public gameNode
{
private:
	image* _image;
	RECT _rc;
	float _x, _y;
	float _hp;
	float _speed;		   //���� �̵��ӵ�
	float _rndTimeCount;   //���� ���������� ī����
	float _worldTimeCount; //���� ī����
	int _currentFrameX;	   //X�����Ӱ�
	int _randomMove;	   //���� ������ ����
	int _distance;		   //���� �̵��Ÿ�
public:
	HRESULT init(float x,float y);
	void release(void);
	void update(void);
	void render(void);

	//�簢�� ��������
	RECT getRect(void) { return _rc; }
	int getX(void) { return _x; }
	int getY(void) { return _y; }
	//���� �̵�
	void move(void);
	float getHp(void) { return _hp; }
	void setHp(float hp) { _hp = hp; }
	spikeBall(){}
	~spikeBall(){}
};

