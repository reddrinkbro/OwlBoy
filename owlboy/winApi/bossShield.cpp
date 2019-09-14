#include "stdafx.h"
#include "bossShield.h"

HRESULT bossShield::init(void)
{
	_count = 0.2f;
	_time = 0;
	return S_OK;
}

void bossShield::release(void)
{
}

void bossShield::update(void)
{
	if (_state == FLYING)	//방패가 공중에 있을때
	{
		shieldFlying();
	}
	else if (_state == FALL) //방패가 땅에 떨어졌을때
	{
		shieldFalling();
	}
	for (_viShield = _vShield.begin(); _viShield != _vShield.end(); ++_viShield)
	{
		_viShield->_rc = RectMakeCenter(_viShield->_x, _viShield->_y, _viShield->_image->getFrameWidth() - 40, _viShield->_image->getFrameHeight() - 40);
	}
}

void bossShield::render(void)
{
	for (_viShield = _vShield.begin(); _viShield != _vShield.end(); ++_viShield)
	{
		_viShield->_image->frameRender(getMemDC(), _viShield->_rc.left, _viShield->_rc.top);
	}
	
}
//방패 생성
void bossShield::appear(float x, float y, bool isLeft)
{
	if (_vShield.size() >= 1) return;

	tagShield _shield;
	ZeroMemory(&_shield, sizeof(tagShield));
	_shield._image = new image;
	_shield._image->init("image/bossShield.bmp", 2328, 502, 9, 2, true, RGB(255, 0, 255));
	_shield._isLeft = isLeft;
	_shield._x = x;
	_shield._y = y;
	_shield._rc = RectMakeCenter(_shield._x, _shield._y, _shield._image->getFrameWidth(), _shield._image->getFrameHeight());
	_shield._angle = PI / 3;
	_shield._isFall = false;
	_vShield.push_back(_shield);
	_state = FLYING;
}

void bossShield::shieldFlying(void)
{
	_time+=0.1f;
	for (_viShield = _vShield.begin(); _viShield != _vShield.end(); ++_viShield)
	{
		if (_count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
		{
			_count = TIMEMANAGER->getWorldTime();

			_viShield->_image->setFrameY(0);
			_viShield->_image->setFrameX(_viShield->_image->getFrameX() + 1);
			if (_viShield->_image->getFrameX() >= 8)
			{
				_viShield->_image->setFrameX(0);
			}

		}
		if (_viShield->_isFall)
		{
			_state = FALL;
			_time = 0;
		}
		//왼쪽으로 이동
		if (_viShield->_isLeft && _viShield->_rc.left > 70)
		{
			_viShield->_x -= 6;
		}
		//오른쪽으로 이동
		else if (!_viShield->_isLeft &&_viShield->_rc.right < WINSIZEX - 70)
		{
			_viShield->_x += 6;
		}
		//중력에 따른 y값 변화
		if (_viShield->_rc.bottom < WINSIZEY - 100)
		{
			_viShield->_y += -(sinf(_viShield->_angle) * 4 - (GRAVITY * _time));
		}
	}
}
//방패 떨어질때 프레임
void bossShield::shieldFalling(void)
{
	for (_viShield = _vShield.begin(); _viShield != _vShield.end(); ++_viShield)
	{
		if (_count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
		{
			_count = TIMEMANAGER->getWorldTime();
			if (_viShield->_image->getFrameY() != 1)
			{
				_viShield->_image->setFrameY(1);
				_viShield->_image->setFrameX(1);
			}
			_viShield->_image->setFrameX(_viShield->_image->getFrameX() + 1);
			if (_viShield->_image->getFrameX() >= _viShield->_image->getMaxFrameX())
			{
				_viShield->_image->setFrameX(_viShield->_image->getMaxFrameX());
			}
		}
	}
}
//방패를 집었을때 방패를 삭제
void bossShield::shieldCatch(void)
{
	_vShield.erase(_vShield.begin());
}
//땅에 방패가 떨어졌을때 상태 바꿈
void bossShield::bumpGround(void)
{
	for (_viShield = _vShield.begin(); _viShield != _vShield.end(); ++_viShield)
	{
		_viShield->_isFall = true;
	}
}
