#include "stdafx.h"
#include "soundTestScene.h"

HRESULT soundTestScene::init(void)
{
	IMAGEMANAGER->addImage("FFX", "FFX.bmp", WINSIZEX, WINSIZEY);

	return S_OK;
}

void soundTestScene::release(void)
{
}

void soundTestScene::update(void)
{
	SOUNDMANAGER->update();
}

void soundTestScene::render(void)
{
	IMAGEMANAGER->render("FFX", getMemDC());
}
