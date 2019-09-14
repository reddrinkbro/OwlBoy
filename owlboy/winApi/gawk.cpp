#include "stdafx.h"
#include "gawk.h"

HRESULT gawk::init(float x, float y)
{
	_image = IMAGEMANAGER->addFrameImage("Gawk", "image/Gawk.bmp", 972, 840, 6, 6, true, RGB(255, 0, 255));
	_x = x;
	_y = y;
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(),_image->getFrameHeight());
	_worldTimeCount = TIMEMANAGER->getWorldTime();
	_currentFrameX = 0;
	_currentFrameY = 0;
	_rndTimeCount = RND->getFromFloatTo(0.04f, 0.1f);
	_speed = 1.2f;
	_hp = 15;
	_isHit = false;
	return S_OK;
}

void gawk::release(void)
{
}

void gawk::update(void)
{
	if (_isHit)
	{
		hit();
	}
	else
	{
		move();
	}

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

void gawk::render(void)
{
	_image->frameRender(getMemDC(), _rc.left - CAMMANAGER->getX(), _rc.top - CAMMANAGER->getY(),_currentFrameX,_currentFrameY);
}

void gawk::move(void)
{
	float angle;
	if (_rndTimeCount + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		_currentFrameX++;
		if (_ptMouse.x >_x) //플레이어가 몬스터 오른쪽에 있을때
		{
			_currentFrameY = 1;
		}
		else
		{
			_currentFrameY = 4;
		}
		if (_image->getMaxFrameX() < _currentFrameX)
		{
			_currentFrameX = 0;
		}
	}
	//각도를 구해서 플레이어의 방향으로 이동
	angle = getAngle(_x, _y, PLAYERMANAGER->getX(), PLAYERMANAGER->getY());
	_x += cosf(angle)*_speed;
	_y += -sinf(angle)*_speed;
}

void gawk::hit(void)
{
	float angle = getAngle(_x, _y, PLAYERMANAGER->getX(), PLAYERMANAGER->getY());
	if (_rndTimeCount + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		if (angle > PI / 2 && angle <=PI + PI / 2) //플레이어가 몬스터 오른쪽에 있을때
		{
			if (_currentFrameY != 2)
			{
				_currentFrameY = 2;
				_currentFrameX = 0;
			}
		}
		else
		{
			if (_currentFrameY != 5)
			{
				_currentFrameY = 5;
				_currentFrameX = 0;
			}
		}
		_currentFrameX++;
		if (_currentFrameX >= 3)
		{
			_currentFrameX = 0;
			_isHit = false;
		}
	}
	
	//방향에 따른 몬스터 밀리도록 구현
	_x -= cosf(angle)*_speed ;
	_y -= -sinf(angle)*_speed ;
}
