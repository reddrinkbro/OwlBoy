#include "stdafx.h"
#include "mountainScene.h"

HRESULT mountainScene::init(void)
{
	IMAGEMANAGER->addImage("mountain", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_pixel = new pixelCollision;
	_pixel->init();

	return S_OK;
}

void mountainScene::release(void)
{
	SAFE_DELETE(_pixel);
}

void mountainScene::update(void)
{
	_pixel->update();
}

void mountainScene::render(void)
{
	IMAGEMANAGER->findImage("mountain")->render(getMemDC());

	_pixel->render();
}
