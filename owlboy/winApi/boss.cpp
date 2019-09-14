#include "stdafx.h"
#include "boss.h"

HRESULT boss::init(float x, float y)
{
	_bossStart = IMAGEMANAGER->addFrameImage("bossStart", "image/bossStart.bmp", 1302, 246, 5, 1, true, RGB(255, 0, 255));
	_boss = IMAGEMANAGER->addFrameImage("boss", "image/boss.bmp", 2080, 9184, 8, 36, true, RGB(255, 0, 255));
	_bossHpBar = IMAGEMANAGER->addImage("bossHpBar","image/bossHpBar.bmp", 716, 72, true, RGB(255, 0, 255));
	
	_x = x;
	_y = y;

	_rc = RectMake(_x, _y - 20, _boss->getFrameWidth() - 90, _boss->getFrameHeight() - 110);
	_bossShield = new bossShield; //방패 동적할당
	_bossShield->init();
	_bossBullet = new bossBullet; //총알 동적 할당
	_bossBullet->init(2, 1000);
	_progressBar = new progressBar;
	_progressBar->init("image/bossHpBarTop", "image/bossHpBarBottom", WINSIZEX/2 -316, 50, 632, 60);
	_hp = 500;
	_count = 0.1f;
	_speed = 10.0f;
	_startingCount = 3;
	_isStart = false;
	_isLeft = false;
	_isFly = false;
	_isAbleHit = false;
	_bossState = MOVE;		//석상에서 풀려나고 처음 상태
	_playBossSound = false;
	return S_OK;
}

void boss::release(void)
{
	_bossShield->release();
	SAFE_DELETE(_bossShield);
	_bossBullet->release();
	SAFE_DELETE(_bossBullet);
	_progressBar->release();
	SAFE_DELETE(_progressBar);
}

void boss::update(void)
{
	if (!_isStart)
	{
		bossStart();
	}
	else
	{
		bossFrame();
	}
	if (_hp < 300 && !_isFly)
	{
		_isAbleHit = false;
	}
	_rc = RectMake(_x, _y - 20, _boss->getFrameWidth() - 90, _boss->getFrameHeight() - 110);
	//방패는 맞거나 보스가 방패를 다시 장착할때까지만 작동
	_bossShield->update();			
	_bossBullet->update();
	_progressBar->setGauge(_hp, 500);
	_progressBar->update();
	
}

void boss::render(void)
{
	if (_isStart)
	{
		_bossHpBar->render(getMemDC(), WINSIZEX / 2 - 358, 75);
		_progressBar->render();
		_boss->frameRender(getMemDC(), _rc.left - 45, _rc.top -110);
	}
	else
	{
		_bossStart->frameRender(getMemDC(), _rc.left-10 , _rc.top -70);
	}
	_bossShield->render();	
	_bossBullet->render();
	EFFECTMANAGER->repeatedRender();
}

void boss::bossStart(void)
{
	if (_count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
	{
		_bossStart->setFrameX(_bossStart->getFrameX() + 1);
		if (_bossStart->getFrameX() >= _bossStart->getMaxFrameX())
		{
			_bossStart->setFrameX(0);
			_startingCount--;
			_count = TIMEMANAGER->getWorldTime() + 0.7;
		}
		else
		{
			_count = TIMEMANAGER->getWorldTime();
		}
	}
	if (_startingCount < 0)
	{
		_boss->setFrameY(1);
		_isStart = true;
		_playBossSound = true;
	}
}

void boss::bossFrame(void)
{
	switch (_bossState)
	{
		case BOSS_DIE:
		{
			bossDie();
			break;
		}
		//이동
		case MOVE:
		{
			bossMove();
			break;
		}
		//맞았을때
		case HIT:
		{
			bossHit();
			break;
		}
		//방패쪽으로 디오
		case MOVESHIELD:
		{
			bossMoveShield();
			break;
		}
		//총쏠때
		case SHOOTING:
		{
			bossShooting();
			break;
		}
		//방패장착
		case SHIELDEQIP:
		{
			bossShieldEqip();
			break;
		}
		//점프
		case JUMP:
		{
			bossJump();
			break;
		}
		case CHANGE:
		{
			bossChageFly();
			break;
		}
	}
}

void boss::bossMove(void)
{
	if (_count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
	{
		_count = TIMEMANAGER->getWorldTime();
		if (!_isLeft)
		{
			if (!_isFly)
			{
				_boss->setFrameY(3);
			}
			else
			{
				_boss->setFrameY(11);
			}
			_x += _speed;
			if (_rc.right > WINSIZEX-110)
			{
				_isLeft = true;
			}
		}
		else
		{
			if (!_isFly)
			{
				_boss->setFrameY(21);
			}
			else
			{
				_boss->setFrameY(29);
			}
			_x -= _speed;
			if (_rc.left <80)
			{
				_isLeft = false;
			}
		}
		_boss->setFrameX(_boss->getFrameX() + 1);
		if (_boss->getFrameX() >=_boss->getMaxFrameX())
		{
			_boss->setFrameX(0);
		}
	}
	_bossState = SHOOTING;
}

void boss::bossHit(void)
{
	_bossShield->appear(_x, _y, _isLeft);
	_isAbleHit = true;
	if (_count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
	{
		_count = TIMEMANAGER->getWorldTime();
		if (!_isLeft)
		{
			if (!_isFly)
			{
				//처음 프레임X값을 0으로 초기화 하기위한 작업
				if (_boss->getFrameY() != 15)
				{
					_boss->setFrameY(15);
					_boss->setFrameX(0);
				}
			}
			else
			{
				if (_boss->getFrameY() != 16)
				{
					_boss->setFrameY(16);
					_boss->setFrameX(0);
				}
			}
		}
		else
		{
			if (!_isFly)
			{
				if (_boss->getFrameY() != 33)
				{
					_boss->setFrameY(33);
					_boss->setFrameX(0);
				}
			}
			else
			{
				if (_boss->getFrameY() != 34)
				{
					_boss->setFrameY(34);
					_boss->setFrameX(0);
				}
			}
		}
		_boss->setFrameX(_boss->getFrameX() + 1);
		if (_boss->getFrameX() >= 5)
		{
			_boss->setFrameX(0);
			_bossState = MOVESHIELD;			//맞은뒤에는 방패를 다시 장착하러 가야함	
		}
		
	}
}

void boss::bossMoveShield(void)
{
	//각도를 구해서 방패가 있는 방향으로 이동해야함
	float angle;
	for (int i = 0; i < _bossShield->getVShield().size(); i++)
	{
		angle = getAngle(_rc.left, _rc.top, _bossShield->getVShield()[i]._x, _bossShield->getVShield()[i]._y);
	}
	RECT _rcTemp;
	if (angle > 5)
	{
		_isLeft = false;
	}
	else
	{
		_isLeft = true;
	}
	if (_count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
	{
		_count = TIMEMANAGER->getWorldTime();
		if (!_isLeft)
		{
			if (!_isFly)
			{
				_boss->setFrameY(7);
			}
			else
			{
				_boss->setFrameY(13);
			}
		}
		else
		{
			if (!_isFly)
			{
				_boss->setFrameY(25);
			}
			else
			{
				_boss->setFrameY(31);
			}
		}
		_boss->setFrameX(_boss->getFrameX() + 1);
		if (_boss->getFrameX() >= _boss->getMaxFrameX())
		{
			_boss->setFrameX(0);
		}
		_x += cosf(angle) * _speed;
		if(_rc.bottom < WINSIZEY - 100) _y += -sinf(angle) * _speed;
	}

	for (int i = 0; i < _bossShield->getVShield().size(); i++)
	{
		if (IntersectRect(&_rcTemp, &CollisionAreaResizing(_rc, 80, 80), &CollisionAreaResizing(_bossShield->getVShield()[i]._rc, 80, 80)))
		{
			//충돌후 방패 장착
			_bossState = SHIELDEQIP;
			_bossShield->shieldCatch();
		}
	}
}

void boss::bossShieldEqip(void)
{
	_isAbleHit = false;
	if (_count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
	{
		_count = TIMEMANAGER->getWorldTime();
		if (!_isLeft)
		{
			if (!_isFly)
			{
				if (_boss->getFrameY() != 5)
				{
					_boss->setFrameY(5);
					_boss->setFrameX(0);
				}
			}
			else
			{
				if (_boss->getFrameY() != 12)
				{
					_boss->setFrameY(12);
					_boss->setFrameX(0);
				}
			}
		}
		else
		{
			if (!_isFly)
			{
				if (_boss->getFrameY() != 23)
				{
					_boss->setFrameY(23);
					_boss->setFrameX(0);
				}
			}
			else
			{
				if (_boss->getFrameY() != 30)
				{
					_boss->setFrameY(30);
					_boss->setFrameX(0);
				}
			}
		}
		_boss->setFrameX(_boss->getFrameX() + 1);
		if (_boss->getFrameX() >= _boss->getMaxFrameX())
		{
			_boss->setFrameX(0);
			//방패 장착후 다시 이동
			if (_hp < 300 && !_isFly)
			{
				_bossState = JUMP;
			}
			else
			{
				_bossState = MOVE;
			}
		}
	}
}

void boss::bossJump(void)
{
	if (_count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
	{
		_count = TIMEMANAGER->getWorldTime();
		if (!_isLeft)
		{
			_boss->setFrameY(9);
		}
		else
		{
			_boss->setFrameY(27);
		}
		_boss->setFrameX(_boss->getFrameX() + 1);
		if (_boss->getFrameX() >= 1)
		{
			_boss->setFrameX(1);
			//점프후 무조건 날고있는 상태
			
		}
	}
	if (_y <= WINSIZEY / 2)
	{
		_isFly = true;
		_bossState = CHANGE;
	}
	else
	{
		_y -= _speed / 2;
	}
}

void boss::bossShooting(void)
{
	if (_hp <= 0) return;
	float angle = getAngle(_x, _y, PLAYERMANAGER->getX(), PLAYERMANAGER->getY());
	_bossBullet->fire(_x , _y, angle);
	if (_count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
	{
		_count = TIMEMANAGER->getWorldTime();
		if (!_isLeft)
		{
			if (!_isFly)
			{
				_boss->setFrameY(4);
			}
			else
			{
				_boss->setFrameY(14);
			}
			_x += _speed;
			if (_rc.right > WINSIZEX - 110)
			{
				_isLeft = true;
			}
		}
		else
		{
			if (!_isFly)
			{
				_boss->setFrameY(22);
			}
			else
			{
				_boss->setFrameY(32);
			}
			_x -= _speed;
			if (_rc.left <80)
			{
				_isLeft = false;
			}
		}
		_boss->setFrameX(_boss->getFrameX() + 1);
		if (_boss->getFrameX() >= _boss->getMaxFrameX())
		{
			_boss->setFrameX(0);
		}
	}
}

void boss::bossChageFly(void)
{
	if (_count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
	{
		_count = TIMEMANAGER->getWorldTime() +0.1f;
		if (!_isLeft)
		{
			_boss->setFrameY(10);
		}
		else
		{
			_boss->setFrameY(28);
		}
		_boss->setFrameX(_boss->getFrameX() + 1);
		if (_boss->getFrameX() >= 6)
		{
			_boss->setFrameX(6);
			_bossState = MOVE;
		}
	}
}

void boss::decreaseHp(void)
{
	if (_isAbleHit)
	{
		_hp -= 50;
	}
	if (_hp <= 0)
	{
		_bossState = BOSS_DIE;
	}
}

void boss::bossDie(void)
{
	if (!_isLeft)
	{
		if (_boss->getFrameY() == 17) return;
		_boss->setFrameY(17);
		_boss->setFrameX(0);
		
		for (int i = 0; i < 3; i++)
		{
			EFFECTMANAGER->createEffect(IMAGEMANAGER->findImage("explosion_big"), RND->getFromFloatTo(_rc.left, _rc.right), RND->getFromFloatTo(_rc.top, _rc.bottom));
			EFFECTMANAGER->createEffect(IMAGEMANAGER->findImage("flameExplode"), RND->getFromFloatTo(_rc.left,_rc.right), RND->getFromFloatTo(_rc.top,_rc.bottom));
		}
	}
	else
	{
		if (_boss->getFrameY() == 35) return;
		_boss->setFrameY(35);
		_boss->setFrameX(0);
		for (int i = 0; i < 3; i++)
		{
			EFFECTMANAGER->createEffect(IMAGEMANAGER->findImage("explosion_big"), RND->getFromFloatTo(_rc.left, _rc.right), RND->getFromFloatTo(_rc.top, _rc.bottom));
			EFFECTMANAGER->createEffect(IMAGEMANAGER->findImage("flameExplode"), RND->getFromFloatTo(_rc.left, _rc.right), RND->getFromFloatTo(_rc.top, _rc.bottom));
		}
	}
}
