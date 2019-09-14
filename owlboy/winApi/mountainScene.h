#pragma once
#include "gameNode.h"
#include "pixelCollision.h"

class mountainScene : public gameNode
{
private:
	pixelCollision* _pixel;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	mountainScene() {}
	~mountainScene() {}
};

