#include "stdafx.h"
#include "titleScene.h"

HRESULT titleScene::init(void)
{
	_graphics = new Graphics(getMemDC());

	_titleOtus._image = IMAGEMANAGER->addPngImage("image/sprOtus.png");
	_grass._image = IMAGEMANAGER->addPngImage("image/OtusHouseBottom.png");
	_logo = IMAGEMANAGER->addPngImage("image/OwlboyLogo.png");
	_image = IMAGEMANAGER->addImage("배경", "image/title.bmp", WINSIZEX, WINSIZEY,true,RGB(255,255,255));
	_centerCloud = IMAGEMANAGER->addImage("하늘", "image/sprSky.bmp", WINSIZEX, WINSIZEY);
	_continueButton = IMAGEMANAGER->addImage("continueButton", "image/continueButton.bmp", 90, 22, true, RGB(255, 0, 255));
	_optionButton = IMAGEMANAGER->addImage("optionButton", "image/optionButton.bmp", 78, 26, true, RGB(255, 0, 255));
	_exitButton = IMAGEMANAGER->addImage("exitButton", "image/exitButton.bmp", 108, 26, true, RGB(255, 0, 255));

	_titleOtus._count = 0.1f;
	_titleOtus._currentX = 0;
	_grass._count = 0.1f;
	_grass._currentX = 0;
	_x = WINSIZEX / 2 -70;
	_y = WINSIZEY / 2;
	_logoRc = RectMakeCenter(_x, _y, _logo->GetWidth(), _logo->GetHeight());
	
	SOUNDMANAGER->addSound("001.mainTitle", "sound/Owlboy Main Title.mp3", true, true);
	
	_isPlaySound = true;
	_isShowOption = false;
	_optionWindow = new optionWindow;
	_optionWindow->init();
	return S_OK;
}

void titleScene::release(void)
{
	_optionWindow->release();
	SAFE_DELETE(_optionWindow);
}

void titleScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		playGame();
		exitGame();
		openOption();
		closeOption();
		_optionWindow->volemSetting();
	}
	if (_isPlaySound)
	{
		SOUNDMANAGER->play("001.mainTitle",OPTIONMANAGER->getMusicVolume());

		_isPlaySound = false;
	}
	
	if (_titleOtus._count + 0.2f < TIMEMANAGER->getWorldTime())
	{
		_titleOtus._count = TIMEMANAGER->getWorldTime();
		_titleOtus._currentX ++;
		if (_titleOtus._currentX > 4)
		{
			_titleOtus._currentX = 0;
		}
	}
	if (_grass._count + 0.2f < TIMEMANAGER->getWorldTime())
	{
		_grass._count = TIMEMANAGER->getWorldTime();
		_grass._currentX++;
		if (_grass._currentX > 4)
		{
			_grass._currentX = 0;
		}
	}
	if (_y > 200)
	{
		_y--;
	}
	_logoRc = RectMakeCenter(_x, _y, _logo->GetWidth(), _logo->GetHeight());
	_continueRc = RectMakeCenter(WINSIZEX/2, WINSIZEY / 2 + 50, _continueButton->getWidth(), _continueButton->getHeight());
	_optionRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 130, _optionButton->getWidth(), _optionButton->getHeight());
	_exitRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 210, _exitButton->getWidth(), _exitButton->getHeight());
	if (_isShowOption) _optionWindow->update();
	volumeApplying();
}

void titleScene::render(void)
{
	_centerCloud->render(getMemDC());
	IMAGEMANAGER->DrawPng(_graphics, _logo, _logoRc.left, _logoRc.top);
	_image->render(getMemDC());
	IMAGEMANAGER->DrawPng(_graphics, _titleOtus._image, 0, WINSIZEY / 2 - 180, _titleOtus._currentX,0, 1470, 137, 6, 1);
	IMAGEMANAGER->DrawPng(_graphics, _grass._image, 42, WINSIZEY / 2 + 210, _titleOtus._currentX,0, 1404, 94, 6, 1);
	if (_y <= 200)
	{
		_continueButton->render(getMemDC(), _continueRc.left, _continueRc.top);
		_optionButton->render(getMemDC(), _optionRc.left, _optionRc.top);
		_exitButton->render(getMemDC(), _exitRc.left, _exitRc.top);
	}
	if (_isShowOption)
	{
		_optionWindow->render();
	}
}
// 게임 시작
void titleScene::playGame(void)
{
	if (PtInRect(&_continueRc, _ptMouse) && !_isShowOption)
	{
		SOUNDMANAGER->stop("001.mainTitle");
		SCENEMANAGER->changeScene("튜토리얼");
	}
}
//옵션 열기
void titleScene::openOption(void)
{
	if (PtInRect(&_optionRc, _ptMouse))
	{
		_isShowOption = true;
	}
}
//옵션 닫기
void titleScene::closeOption(void)
{
	if (PtInRect(&_optionWindow->getBackArrowRect(), _ptMouse))
	{
		_isShowOption = false;
	}
}
//게임 끄기
void titleScene::exitGame(void)
{
	if (PtInRect(&_exitRc, _ptMouse) && !_isShowOption)
	{
		PostQuitMessage(0);
	}
}
//볼륨 조절한것 적응
void titleScene::volumeApplying(void)
{
	SOUNDMANAGER->setVolume("001.mainTitle", OPTIONMANAGER->getMusicVolume());
}
