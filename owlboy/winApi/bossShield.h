#pragma once
#include "gameNode.h"

#define FRAMECOUNT 0.1f

enum state
{
	FLYING =0,				    //���а� ���߿� �ִ°�
	FALL,					//���а� ���� �������°�
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
	int _state;				//������ ���� ����
	float _count;
	float _time;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void appear(float x, float y, bool isLeft);			//���� ����
	void shieldFlying(void);							//���߿��� ���� �Լ�
	void shieldFalling(void);							//���� ���������� ���� ������
	void shieldCatch(void);								//������ ���и� ������� ���� �ٲٱ����� �Լ�
	void bumpGround(void);								//���� �ε�������

	vector<tagShield> getVShield(void) { return _vShield; }

	bossShield(){}
	~bossShield(){}
};

