#pragma once
#include "gameNode.h"
#include "stage.h"
struct waterfall
{
	Image* image;
	float count;
	int _currentX;
};
class bossScene : public stage
{
private:
	image* _image;
	image* _fadeOutImage;
	enemyManager* _enemyManager;
	RECT _rc[3];
	waterfall _waterfall;
	Graphics* _graphics;
	bool _isPlaySound;
	int _fadeCount;			//���̵�ƿ� �ϱ� ���� ����
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	//�ٴڰ� ���� ���� �浹
	void shieldCollision(void);
	void playerCollision(void);

	void bossPlayerCollsion(void);
	bossScene(){}
	~bossScene(){}
};

