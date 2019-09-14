#pragma once
#include "gameNode.h"
class playerDieScene : public gameNode
{
private:
	image* _image;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	playerDieScene(){}
	~playerDieScene(){}
};

