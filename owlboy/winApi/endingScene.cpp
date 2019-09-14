#include "stdafx.h"
#include "endingScene.h"

HRESULT endingScene::init(void)
{
	_image = IMAGEMANAGER->addImage("endingScene", "image/endingScene.bmp", 2560, 800);
	_image1 = IMAGEMANAGER->addImage("엔딩폰트", "image/엔딩폰트.bmp", 640, 3200, true, RGB(255,0,255));



	_bgSpeedX = 0.0f;
	_bgSpeedF = 0.0f;
	PLAYERMANAGER->endSceneInit();
	PLAYERMANAGER->setX(WINSIZEX / 2);
	PLAYERMANAGER->setY(WINSIZEY / 2 + 300);
	
	_isPlaySound = true;
	return S_OK;
}

void endingScene::release(void)
{
	
}

void endingScene::update(void)
{
	PLAYERMANAGER->endSceneUpdate();
	if (_isPlaySound)
	{
		SOUNDMANAGER->play("006 ending",OPTIONMANAGER->getMusicVolume());
		_isPlaySound = false;
	}
	_bgSpeedX++;
	_bgSpeedF++;
	

	if (_bgSpeedX > 2100)
	{
		SCENEMANAGER->changeScene("시작화면");
		SOUNDMANAGER->stop("006 ending");
	}

}
 
void endingScene::render(void)
{
	_image->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY),_bgSpeedX,0);
	PLAYERMANAGER->endRender();
	_image1->loopRender(getMemDC(), &RectMake(640, 0, WINSIZEX, WINSIZEY), 0, _bgSpeedF);
}
