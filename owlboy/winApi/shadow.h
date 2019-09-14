#pragma once
#include "gameNode.h"

struct shadowStruct
{
	int* originX;
	int* originY;
	int offsetX, offsetY;
	int finalX, finalY;

	RECT detectRect; // �浹������ ��Ʈ
	RECT interRect; // ������ ��Ʈ
	RECT shadowRect; // �׸��� ��Ʈ

	shadowStruct(int* oriX, int* oriY, int offX, int offY)
	{
		originX = oriX;
		originY = oriY;
		offsetX = offX;
		offsetY = offY;
		interRect = { 0,0,0,0 };
	}
};

class shadow : public gameNode
{
private:

public:
	vector<shadowStruct*> vShadow;
	vector<shadowStruct*>::iterator viShadow;

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	shadow() {}
	~shadow() {}
};

