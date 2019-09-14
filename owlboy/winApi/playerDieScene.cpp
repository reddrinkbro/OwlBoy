#include "stdafx.h"
#include "playerDieScene.h"
#include "dungeon.h"
#include "bossScene.h"
#include "endingScene.h"
HRESULT playerDieScene::init(void)
{
	_image = IMAGEMANAGER->addImage("BlackBackground", "image/playerDieScene.bmp", WINSIZEX, WINSIZEY);
	return S_OK;
}

void playerDieScene::release(void)
{
	
}

void playerDieScene::update(void)
{
	PLAYERMANAGER->update();
	if (PLAYERMANAGER->getOtusState() == otIDLE)
	{
		SCENEMANAGER->release();
		SCENEMANAGER->addScene("����", new dungeon);
		SCENEMANAGER->addScene("������������", new bossScene);
		SCENEMANAGER->addScene("�÷��̾���", new playerDieScene);
		SCENEMANAGER->addScene("������", new endingScene);
		SCENEMANAGER->changeScene("����");
		PLAYERMANAGER->setHp(10);
	}
}

void playerDieScene::render(void)
{
	_image->render(getMemDC());
	PLAYERMANAGER->render();
}
