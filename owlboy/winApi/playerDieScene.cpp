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
		SCENEMANAGER->addScene("던전", new dungeon);
		SCENEMANAGER->addScene("보스스테이지", new bossScene);
		SCENEMANAGER->addScene("플레이어사망", new playerDieScene);
		SCENEMANAGER->addScene("엔딩씬", new endingScene);
		SCENEMANAGER->changeScene("던전");
		PLAYERMANAGER->setHp(10);
	}
}

void playerDieScene::render(void)
{
	_image->render(getMemDC());
	PLAYERMANAGER->render();
}
