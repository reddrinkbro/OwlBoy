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
	_bossShield = new bossShield; //���� �����Ҵ�
	_bossShield->init();
	_bossBullet = new bossBullet; //�Ѿ� ���� �Ҵ�
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
	_bossState = MOVE;		//���󿡼� Ǯ������ ó�� ����
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
	//���д� �°ų� ������ ���и� �ٽ� �����Ҷ������� �۵�
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
		//�̵�
		case MOVE:
		{
			bossMove();
			break;
		}
		//�¾�����
		case HIT:
		{
			bossHit();
			break;
		}
		//���������� ���
		case MOVESHIELD:
		{
			bossMoveShield();
			break;
		}
		//�ѽ�
		case SHOOTING:
		{
			bossShooting();
			break;
		}
		//��������
		case SHIELDEQIP:
		{
			bossShieldEqip();
			break;
		}
		//����
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
				//ó�� ������X���� 0���� �ʱ�ȭ �ϱ����� �۾�
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
			_bossState = MOVESHIELD;			//�����ڿ��� ���и� �ٽ� �����Ϸ� ������	
		}
		
	}
}

void boss::bossMoveShield(void)
{
	//������ ���ؼ� ���а� �ִ� �������� �̵��ؾ���
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
			//�浹�� ���� ����
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
			//���� ������ �ٽ� �̵�
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
			//������ ������ �����ִ� ����
			
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
