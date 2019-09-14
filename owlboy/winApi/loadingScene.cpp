#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init(void)
{
	_loading = new loading;
	_loading->init();

	//�̹��� �� ���� �ε�
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
		//�ε��� �Ϸ�Ǹ� �� ����
		SCENEMANAGER->changeScene("start");
	}
}

void loadingScene::render(void)
{
	_loading->render();
}

//�ε��̹��� �Լ�
void loadingScene::loadingImage(void)
{
	//_loading->loadImage()
	//_loading->loadFrameImage()

	for (int i = 0; i < 1000; i++)
	{
		_loading->loadImage("�׽�Ʈ", WINSIZEX, WINSIZEY);
	}
}

//�ε����� �Լ�
void loadingScene::loadingSound(void)
{
}
