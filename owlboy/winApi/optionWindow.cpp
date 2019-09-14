#include "stdafx.h"
#include "optionWindow.h"

HRESULT optionWindow::init(void)
{
	_graphics = new Graphics(getMemDC());
	_image = IMAGEMANAGER->addImage("option","image/option.bmp",988,577,true,RGB(255,0,255));
	_backArrow = IMAGEMANAGER->addPngImage("image/backArrow.png");
	for (int i = 0; i < 3; i++)
	{
		_volume[i]._progressBar = new progressBar;
		_volume[i]._progressBar->init("image/volumeBarUp", "image/volumeBarDown", WINSIZEX / 2 - 21, 188 + i * 118, 436, 44);
		_volume[i].rc = RectMakeCenter(_volume[i].x, _volume[i].y, 436, 44);
		_volume[i].volumeValue = 1.0f;
	}
	_optionWindowRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, _image->getWidth(), _image->getHeight());
	_arrowRc = RectMakeCenter(192, 140, _backArrow->GetWidth(), _backArrow->GetHeight());
	return S_OK;
}

void optionWindow::release(void)
{
	for (int i = 0; i < 3; i++)
	{
		_volume[i]._progressBar->release();
		SAFE_DELETE(_volume[i]._progressBar);
	}
}

void optionWindow::update(void)
{
	for (int i = 0; i < 3; i++)
	{
		_volume[i].x = WINSIZEX / 2 + 197;
		_volume[i].y = 232 + i * 118;
		_volume[i]._progressBar->update();
		_volume[i]._progressBar->setGauge(_volume[i].volumeValue, 1);
		_volume[i].rc = RectMakeCenter(_volume[i].x, _volume[i].y, 436, 44);
	}
	
}

void optionWindow::render(void)
{
	_image->render(getMemDC(), _optionWindowRc.left, _optionWindowRc.top);
	IMAGEMANAGER->DrawPng(_graphics, _backArrow, _arrowRc.left, _arrowRc.top, _backArrow->GetWidth(), _backArrow->GetHeight());
	for (int i = 0; i < 3; i++)
	{
		_volume[i]._progressBar->render();
	}
}

void optionWindow::volemSetting(void)
{
	if (PtInRect(&_volume[0].rc, _ptMouse))
	{
		_volume[0].volumeValue = masterVolume();
	}
	else if (PtInRect(&_volume[1].rc, _ptMouse))
	{
		_volume[1].volumeValue = musicVolume();
	}
	else if (PtInRect(&_volume[2].rc, _ptMouse))
	{
		_volume[2].volumeValue = soundVolume();
	}
	OPTIONMANAGER->settingVolume(_volume[1].volumeValue * _volume[0].volumeValue, _volume[2].volumeValue * _volume[0].volumeValue);
}

float optionWindow::masterVolume(void)
{
	float percent = _volume[0].rc.right - _volume[0].rc.left;
	_volume[0].volumeValue = (_ptMouse.x- _volume[0].rc.left) / percent;
	return _volume[0].volumeValue;
}

float optionWindow::musicVolume(void)
{
	float percent = _volume[1].rc.right - _volume[1].rc.left;
	_volume[1].volumeValue = (_ptMouse.x - _volume[1].rc.left) / percent;
	return _volume[1].volumeValue;
}

float optionWindow::soundVolume(void)
{
	float percent = _volume[2].rc.right - _volume[2].rc.left;
	_volume[2].volumeValue = (_ptMouse.x - _volume[2].rc.left) / percent;
	return _volume[2].volumeValue;
}
