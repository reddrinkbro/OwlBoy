#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init(void)
{
	_loading = new loading;
	_loading->init();

	//이미지 및 사운드 로딩
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release(void)
{
	SAFE_DELETE(_loading);
}

void loadingScene::update(void)
{
	_loading->update();

	if (_loading->loadingDone())
	{
		//로딩이 완료되면 씬 변경
		SCENEMANAGER->changeScene("start");
	}
}

void loadingScene::render(void)
{
	_loading->render();
}

//로딩이미지 함수
void loadingScene::loadingImage(void)
{
	//_loading->loadImage()
	//_loading->loadFrameImage()

	for (int i = 0; i < 1000; i++)
	{
		_loading->loadImage("테스트", WINSIZEX, WINSIZEY);
	}
}

//로딩사운드 함수
void loadingScene::loadingSound(void)
{
}
