#include "stdafx.h"
#include "bullet.h"

HRESULT bossBullet::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;
	return S_OK;
}

void bossBullet::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->image);
	}

	_vBullet.clear();
}

void bossBullet::update(void)
{
	move();
}

void bossBullet::render(void)
{
	draw();
}

void bossBullet::fire(float x, float y, float angle)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.image = new image;
	bullet.image->init("image/bossBullet.bmp", 16, 18, true, RGB(255, 0, 255));
	bullet.speed = RND->getFromFloatTo(3.0f, 5.0f);
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.angle = angle;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.image->getWidth(), bullet.image->getHeight());
		
	_vBullet.push_back(bullet);
}

void bossBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->image->render(getMemDC(), _viBullet->rc.left,
			_viBullet->rc.top);
	}
}

void bossBullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle)*_viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle)*_viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y + _viBullet->image->getHeight(),
			_viBullet->image->getWidth(), _viBullet->image->getHeight());

		//사거리 밖으로 나갔음
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			EFFECTMANAGER->createEffect(IMAGEMANAGER->findImage("bossBulletEffect"), _viBullet->x, _viBullet->y);
			SAFE_DELETE(_viBullet->image);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			//카운트 시간이 0이 되면 발사한다
			++_viBullet;
		}
	}
}
//총알 삭제
void bossBullet::removeBullet(int arrNum)
{
	SAFE_DELETE(_vBullet[arrNum].image);

	_vBullet.erase(_vBullet.begin() + arrNum);
}


//===========================================================
//게디 총알
//===========================================================

HRESULT geddyBullet::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;
	return S_OK;
}

void geddyBullet::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->image);
	}

	_vBullet.clear();
}

void geddyBullet::update(void)
{
	move();
}

void geddyBullet::render(void)
{
	draw();
}

void geddyBullet::fire(int x, int y, float angle)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.image = new image;
	bullet.image->init("image/게디총알.bmp", 208, 26, 8, 1, true, RGB(255, 0, 255));
	bullet.speed = 10.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.angle = angle;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.image->getFrameWidth(), bullet.image->getFrameHeight());

	_vBullet.push_back(bullet);
}

void geddyBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->image->frameRender(getMemDC(), _viBullet->rc.left - CAMMANAGER->getX(),
			_viBullet->rc.top - CAMMANAGER->getY(), _frameX, _frameY);
	}

	if (_frameY != 0)
	{
		_frameX = 0;
		_frameY = 0;
	}
	_countBullet++;
	if (_countBullet % 8 == 0)
	{
		_frameX++;
		if (_frameX > 4)
		{
			_frameX = 0;
		}
	}
}

void geddyBullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle / 180 * PI)*_viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle / 180 * PI)*_viBullet->speed;
		if (_viBullet->angle < 90 || _viBullet->angle > 270)
		{
			_viBullet->rc = RectMakeCenter(_viBullet->x + 20, _viBullet->y + _viBullet->image->getFrameHeight(),
				_viBullet->image->getFrameWidth(), _viBullet->image->getFrameHeight());
		}
		else
		{
			_viBullet->rc = RectMakeCenter(_viBullet->x , _viBullet->y + _viBullet->image->getFrameHeight(),
				_viBullet->image->getFrameWidth(), _viBullet->image->getFrameHeight());
		}
		//사거리 밖으로 나갔음
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			SAFE_DELETE(_viBullet->image);
			EFFECTMANAGER->createEffect(IMAGEMANAGER->findImage("flair"), _viBullet->x, _viBullet->y);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}

void geddyBullet::removeBullet(int arrNum)
{
	
	SAFE_DELETE(_vBullet[arrNum].image);

	_vBullet.erase(_vBullet.begin() + arrNum);
}

//============================================================================
//============================================================================
// 바위
//============================================================================
//============================================================================
HRESULT torqueBullet::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;
	return S_OK;
}

void torqueBullet::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->image);
	}

	_vBullet.clear();
}

void torqueBullet::update(void)
{
	move();
}

void torqueBullet::render(void)
{
	draw();
}

void torqueBullet::fire(float x, float y, float angle)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.image = new image;
	bullet.image->init("image/rock.bmp", 46, 42, true, RGB(255, 0, 255));
	bullet.speed = 5.0f;
	if (angle <PI / 2 || angle> PI + PI / 2) bullet.x = bullet.fireX = x-60;
	else bullet.x = bullet.fireX = x+60;
	bullet.y = bullet.fireY = y;
	bullet.angle = angle;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.image->getWidth(), bullet.image->getHeight());

	_vBullet.push_back(bullet);
}

void torqueBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->image->render(getMemDC(), _viBullet->rc.left-CAMMANAGER->getX(),
			_viBullet->rc.top-CAMMANAGER->getY());
	}
}

void torqueBullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle)*_viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle)*_viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y + _viBullet->image->getHeight(),
			_viBullet->image->getWidth(), _viBullet->image->getHeight());

		//사거리 밖으로 나갔음
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			SAFE_DELETE(_viBullet->image);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}

void torqueBullet::removeBullet(int arrNum)
{
	SAFE_DELETE(_vBullet[arrNum].image);

	_vBullet.erase(_vBullet.begin() + arrNum);
}