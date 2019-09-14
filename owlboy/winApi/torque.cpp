#include "stdafx.h"
#include "torque.h"

HRESULT torque::init(string strKey, float x, float y)
{
	_image = IMAGEMANAGER->findImage(strKey);
	_x = x;
	_y = y;
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(),_image->getFrameHeight());
	_worldTimeCount = TIMEMANAGER->getWorldTime();
	_currentFrameX = 0;
	_currentFrameY = 0;
	_rndTimeCount = RND->getFromFloatTo(0.04f, 0.1f);
	_speed = 1.0f;
	_hp = 20;
	_isHit = false;
	_state = TORQUE_MOVE;
	_reloadTime = 3.0f;
	_distance = 350;
	_randomMove = RND->getInt(2);
	_isAttack = false;
	_bullet = new torqueBullet;
	_bullet->init(1, 500);
	return S_OK;
}

void torque::release(void)
{
	_bullet->release();
	SAFE_DELETE(_bullet);
}

void torque::update(void)
{
	float distance = getDistance(_x, _y, PLAYERMANAGER->getX(), PLAYERMANAGER->getY());
	if (_isHit)
	{
		hit();
	}
	else if (_state == TORQUE_RELOAD)
	{
		reload();
	}
	else if (_state == TORQUE_MOVE)
	{
		move();
	}
	else
	{
		
		attack();
	}
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	if (_currentFrameX >= 3)
	{
		_bullet->update();
	}
	
	if (distance < 350 && _reloadTime == 3.0f)
	{
		fire();
		_isAttack = true;
	}

	playerHit();
}

void torque::render(void)
{
	_image->frameRender(getMemDC(), _rc.left - CAMMANAGER->getX(), _rc.top - CAMMANAGER->getY(), _currentFrameX, _currentFrameY);
	if (_state == TORQUE_ATTACK && _currentFrameX >=2)
	{
		_bullet->render();
	}
}

void torque::reload(void)
{
	float distance = getDistance(_x, _y, PLAYERMANAGER->getX(), PLAYERMANAGER->getY());
	if (_rndTimeCount + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime() + 0.1f;
		if (PLAYERMANAGER->getX() > _x) //플레이어가 몬스터 오른쪽에 있을때
		{
			if (_currentFrameY != 0)
			{
				_currentFrameY = 0;
				_currentFrameX = 0;
			}
		}
		else
		{
			if (_currentFrameY != 4)
			{
				_currentFrameY = 4;
				_currentFrameX = 0;
			}
		}
		_currentFrameX++;
		if (_currentFrameX >= 5)
		{
			_currentFrameX = 0;
			
		}
	}
	_reloadTime -= 0.01f;
	if (_reloadTime < 0)
	{
		_reloadTime = 3.0f;
		if (distance < 1500)
		{
			fire();
		}
		else
		{
			_state = TORQUE_MOVE;
			_isAttack = false;
		}
	}
}

void torque::move(void)
{
	if (_rndTimeCount + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime() + 0.1f;
		if (_randomMove == 1)
		{
			_currentFrameY = 1;
		}
		else
		{
			_currentFrameY = 5;			
		}
		_currentFrameX++;
		if (_currentFrameX >= 5)
		{
			_currentFrameX = 0;
		}
	}
	if (_randomMove == 0)
	{
		_x -= _speed;
		_distance--;
	}
	else
	{
		_x += _speed;
		_distance--;
	}
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
		_distance = RND->getFromIntTo(400,600);
		
	}
	//벽에 부딪히면
	if (_rc.left < -250)
	{
		_randomMove = 1;
		_distance = RND->getFromIntTo(600, 700);
		
	}
}

void torque::hit(void)
{
	//_isAttack = true;
	if (_rndTimeCount + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime() +0.1f;
		if (PLAYERMANAGER->getX() > _x) //플레이어가 몬스터 오른쪽에 있을때
		{
			if (_currentFrameY != 3)
			{
				_currentFrameY = 3;
				_currentFrameX = 0;
			}
		}
		else
		{
			if (_currentFrameY != 7)
			{
				_currentFrameY = 7;
				_currentFrameX = 0;
			}
		}
		_currentFrameX++;
		if (_currentFrameX >=3)
		{
			_currentFrameX = 3;
			_isHit = false;
			_hp -= 5;
		}
	}
}

void torque::playerLook(void)
{
	fire();
	
}

void torque::playerHit(void)
{
	RECT _rcTemp;
	//torque 총알 충돌
	for (int i = 0; i <_bullet->getBulletVector().size(); i++)
	{
		if (IntersectRect(&_rcTemp, &PLAYERMANAGER->playerHitRect(), &CollisionAreaResizing(_bullet->getBulletVector()[i].rc,10,0,10,10)))
		{
			_bullet->removeBullet(i);
			PLAYERMANAGER->setHp(PLAYERMANAGER->getHp() - 1.0f);
			PLAYERMANAGER->setOtusDamageOn(true);
			_state = TORQUE_RELOAD;
			break;
		}
	}
}

void torque::attack(void)
{
	if (_rndTimeCount + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		if(_currentFrameX !=1) _worldTimeCount = TIMEMANAGER->getWorldTime() + 0.1f;
		else  _worldTimeCount = TIMEMANAGER->getWorldTime() + 1.0f;
		if (PLAYERMANAGER->getRect().left > _x) //플레이어가 몬스터 오른쪽에 있을때
		{
			if (_currentFrameY != 2)
			{
				_currentFrameY = 2;
				_currentFrameX = 0;
			}
		}
		else
		{
			if (_currentFrameY != 6)
			{
				_currentFrameY = 6;
				_currentFrameX = 0;
			}
		}
		_currentFrameX++;
		if (_image->getMaxFrameX() < _currentFrameX)
		{
			_currentFrameX = 0;
			_state = TORQUE_RELOAD;
		}
	}
}

void torque::fire(void)
{
	float angle = getAngle(_x, _y, PLAYERMANAGER->getX(), PLAYERMANAGER->getY());
	if(_currentFrameX ==2) _bullet->fire(_x, _y, angle);
	_state = TORQUE_ATTACK;
}
