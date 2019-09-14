#pragma once
#include "stage.h"

struct mist
{
	RECT _rc;
	float _x, _y;
	float _speed;
};
class tutorial : public stage
{
private:

	Graphics* graphics;
private:
	image* _image;
	mist _mist[8];
	bool _isPlaySound;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void DrawPng(Image * tempimage, int x, int y);

	void nextScene(void);
	void moveMist(void);

	tutorial() {}
	~tutorial() {}
};

