#include "stdafx.h"
#include "spikeBall.h"

HRESULT spikeBall::init(float x, float y)
{
	_image = IMAGEMANAGER->addFrameImage("spikeBall", "image/Spikeball.bmp", 924, 144, 7, 1, true, RGB(255, 0, 255));
	_x = x;
	_y = y;
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	_speed = 0.7f;
	_worldTimeCount = TIMEMANAGER->getWorldTime();
	_currentFrameX = 0;
	_rndTimeCount = RND->getFromFloatTo(0.04f, 0.1f);
	_randomMove = RND->getInt(2);
	_distance = 300;
	_hp = 15;
	return S_OK;
}

void spikeBall::release(void)
{
}

void spikeBall::update(void)
{
	if (_rndTimeCount + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		_currentFrameX++;
		if (_image->getMaxFrameX() < _currentFrameX)
		{
			_currentFrameX = 0;
		}
	}
	move();
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

void spikeBall::render(void)
{
	_image->frameRender(getMemDC(), _rc.left - CAMMANAGER->getX(), _rc.top - CAMMANAGER->getY(),_currentFrameX,0);
}

void spikeBall::move(void)
{

	//위로 이동
	if (_randomMove == 0)
	{
		_y -= _speed;
		_distance--;
	}
	//아래로 이동
	else
	{
		_y+= _speed;
		_distance--;
	}
	//이동을 다하면 방향을 바꾼다
	if (_distance < 0)
	{
		if (_randomMove == 0)
		{
			_randomMove = 1;
		}
		else
		{
			_randomMove = 0;
		}
		//다시 이동거리 설정
		_distance = 600;
	}
}