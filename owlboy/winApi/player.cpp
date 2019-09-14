#include "stdafx.h"
#include "player.h"

HRESULT player::init(void)
{
	_img = IMAGEMANAGER->addFrameImage("������","image/������.bmp",2160,3520,12,22,true,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("sprLandingDust", "image/sprLandingDust.bmp", 1264, 100, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("dust", "image/dust.bmp", 736, 40, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("dustL", "image/directDustL.bmp", 480, 52, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("dustR", "image/directDustR.bmp", 480, 52, 6, 1, true, RGB(255, 0, 255));

	//���� ����
	_hp = 10.0f;
	_otusMove = otIDLE;
	_isLeft = false; //�������� �ƴ��� �Ǻ��ϴ� bool�� �ʱ�ȭ
	
	_count = 0;//�����ӿ� ����� ī��Ʈ
	_frameX = _frameY = 0; //������X�� Y�� �ʱ�ȭ
	
	_onceSpin = false; //�ѹ� ȸ���ϴ� ���� ���� bool��
	_attackOn = false; //�÷��̾� ���� bool��

	_gravity = 0.0f;
	_isCollision = false; // ĳ���Ͱ� ������ �浹

	_cursorAngle = 0;

	_geddyOn = false; // �Ե�� ���� Ȯ��
	
	_effectVolume = 1.0f;

	_otusDamageOn = false; // ������ �� ����
	_damageCount = 0;
	return S_OK;
}

void player::release(void)
{
}

void player::update(void)
{
	// ĳ���Ϳ� ���콺���� ���� ���
	_cursorAngle = 180 / 3.14159f * MY_UTIL::getAngle(_x - CAMMANAGER->getX(), _y - CAMMANAGER->getY() + 60, _ptMouse.x, _ptMouse.y);

	// ĳ���� ���¿� ���� ī�޶� ���� �ܾƿ�
	if (CAMMANAGER->getZoom() > 1.01f && _otusMove == otFLY)
	{
		CAMMANAGER->setZoom(CAMMANAGER->getZoom() - 0.01f); // ���
	}
	else if (CAMMANAGER->getZoom() < 1.5f && _otusMove != otFLY)
	{
		CAMMANAGER->setZoom(CAMMANAGER->getZoom() + 0.01f); // Ȯ��
	}
	if (_hp <= 0)
	{
		_otusMove = otDIE;
	}
	// ĳ���Ͱ� �̹� �����ӿ� Y������ �󸶳� �̵�����
	_moveAmountY = 0;

#pragma region Ű�Է�
	// ���� & ����
	
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		if (_otusMove != otFLY)
		{
			if (_otusMove != otJUMP) // ���� ������ �����ϰ� ������ ����.
			{
					
				SOUNDMANAGER->play("2.jump", _effectVolume);
				EFFECTMANAGER->createEffect(IMAGEMANAGER->findImage("dust"), _x, _y + 70);
				_otusMove = otJUMP; // ���� ���·� ��ȯ
				_gravity = 5.0f;
			}
			else // ���� ����. (���� �� �ƴ�)
			{
					
				SOUNDMANAGER->play("5.fly", _effectVolume);
				_otusMove = otFLY; // ���� ���·� ��ȯ
			}
		}
	}

	// ���� �ִ� �߿� WŰ�� ������ ������ ���� �����
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (_otusMove == otFLY)
		{
			_moveAmountY = -PLAYERSPEED;
		}
	}

	// �ϰ�
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_moveAmountY = PLAYERSPEED;
	}
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		SOUNDMANAGER->resume("5.fly");
	}

	// �������� �޸���
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_x -= PLAYERSPEED;
		_isLeft = true;


		if (_otusMove != otJUMP && _otusMove != otFLY && _isCollision && !_attackOn && !_otusDamageOn)
		{
			if (_otusMove != otRUN)
			{
				_otusMove = otRUN;
				EFFECTMANAGER->createEffect(IMAGEMANAGER->findImage("dustL"), _x, _y + 60);
			}
		}
	}

	// �������� idle
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		SOUNDMANAGER->stop("1.run");
		if (_otusMove != otJUMP && _otusMove != otFLY && _isCollision && !_attackOn)
		{
			_otusMove = otIDLE;
		}
	}

	// ���������� �޸���
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_x += PLAYERSPEED;
		_isLeft = false;
		if (_otusMove != otJUMP && _otusMove != otFLY && _isCollision && !_attackOn && !_otusDamageOn)
		{
			if (_otusMove != otRUN)
			{
				_otusMove = otRUN;
				EFFECTMANAGER->createEffect(IMAGEMANAGER->findImage("dustR"), _x, _y + 60);
			}
		}
	}

	// ���������� idle
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		//SOUNDMANAGER->stop("1.run");
		if (_otusMove != otJUMP && _otusMove != otFLY && _isCollision && !_attackOn)
		{
			_otusMove = otIDLE;
		}
	}

	//ȸ�� ����
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (!_geddyOn)
		{
			_otusMove = otSPIN;
		}
	}

	//�״� ���� �׽�Ʈ
	if (KEYMANAGER->isOnceKeyDown('H'))
	{
		_otusMove = otDIE;
		_x += (_isLeft) ? -PLAYERSPEED : PLAYERSPEED;
	}
	
#pragma endregion

	// ���� �ִ°� �ƴϸ� �߷�.
	if (_otusMove != otFLY)
	{
		_moveAmountY = -_gravity;

		if (_gravity > -5.0f)
		{
			_gravity -= 0.1f;
		}
	}
	if (_otusMove != otDIE)
	{
		_y += _moveAmountY;
	}
	

	// ������ �浹�ϸ� ���̵� ���·� ��ȯ.
	if (PLAYERMANAGER->getIsCollision())
	{
		if (_moveAmountY > 0 && (_otusMove == otFLY || _otusMove == otJUMP) && !_geddyOn)
		{
			if (_otusMove != otIDLE)
			{
				_otusMove = otIDLE;
				_gravity = 0;
				EFFECTMANAGER->createEffect(IMAGEMANAGER->findImage("sprLandingDust"), _x, _y + 50);
			}
		}
	}

	// ������ ��/���� ���
	if (getOtusDamageOn())
	{
		if (_otusDamageOn = true)
		{
			_otusMove = otDAMAGE;
			_damageCount++;
		}
		if (_damageCount == 100)
		{
			_damageCount = 0;
			_otusMove = otIDLE;
			_otusDamageOn = false;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('U'))
	{
		_hp--;
	}


	//���� enum�� ����
	switch (_otusMove)
	{
	case otIDLE: //idle ����
	{
		SOUNDMANAGER->stop("5.fly");
		if (_isLeft)
		{
			_count++;

			if (_frameX != 1)
			{
				_frameY = 1;
				_frameX = 1;
			}

			if (_count % 50 == 0)
			{
				_frameX++;
				if (_frameX > 2)
				{
					_frameX = 1;
				}
			}
		}
		else
		{
			_count++;

			if (_frameY != 0)
			{
				_frameY = 0;
				_frameX = 1;
			}

			if (_count % 50 == 0)
			{
				_frameX++;
				if (_frameX > 2)
				{
					_frameX = 1;
				}
			}
		}
	}
	break;

	case otRUN: //�޸���
	{
		if (!_attackOn)
		{
			if (_isLeft)
			{
				if (_frameY != 3)
				{
					if (!SOUNDMANAGER->isPauseSound("1.run"))
					{
						SOUNDMANAGER->play("1.run", _effectVolume);
					}
					else
					{
						SOUNDMANAGER->resume("1.run");
					}
					_frameY = 3;
					_frameX = 0;
				}

				_count++;
				if (_count % 10 == 0)
				{
					_frameX++;
					if (_frameX > 8)
					{
						_frameX = 0;
					}
				}
			}
			else
			{
				if (_frameY != 2)
				{
					if (!SOUNDMANAGER->isPauseSound("1.run"))
					{
						SOUNDMANAGER->play("1.run", _effectVolume);
					}
					else
					{
						SOUNDMANAGER->resume("1.run");
					}
					_frameY = 2;
					_frameX = 0;
				}

				_count++;
				if (_count % 10 == 0)
				{
					_frameX++;
					if (_frameX > 8)
					{
						_frameX = 0;
					}
				}
			}

		}
	}
	break;

	case otJUMP://����
	{
		SOUNDMANAGER->stop("1.run");
		if (_moveAmountY < 0)
		{
			if (_isLeft)
			{
				if (_frameY != 5)
				{
					_frameY = 5;
					_frameX = 0;
				}

				_count++;
				if (_count % 10 == 0)
				{
					_frameX++;
					if (_frameX > 2)
					{
						_frameX = 0;
					}
				}
			}
			else
			{
				if (_frameY != 4)
				{
					_frameY = 4;
					_frameX = 0;
				}

				_count++;
				if (_count % 10 == 0)
				{
					_frameX++;
					if (_frameX > 2)
					{
						_frameX = 0;
					}
				}
			}
		}
		else
		{
			if (_isLeft)
			{
				if (_frameY != 7)
				{
					_frameY = 7;
					_frameX = 0;
				}

				_count++;
				if (_count % 10 == 0)
				{
					_frameX++;
					if (_frameX > 4)
					{
						SOUNDMANAGER->play("3.landing", _effectVolume);
						_frameX = 2;
;					}
				}
			}
			else
			{
				if (_frameY != 6)
				{
					_frameY = 6;
					_frameX = 0;
				}

				_count++;
				if (_count % 10 == 0)
				{
					_frameX++;
					if (_frameX > 4)
					{
						SOUNDMANAGER->play("3.landing", _effectVolume);
						_frameX = 2;
					}
				}
			}
		}

	}
	break;
	
	case otCOMBI://��ü �ٶ� ����
	{

	}
	break;

	case otFLY: // ����
	{
		if (_geddyOn)
		{
			if (_isLeft)
			{
				_frameY = 9;
				_count++;
				if (_count % 10 == 0)
				{
					_frameX++;
					if (_frameX > 7)
					{
						_frameX = 0;
					}
				}
			}
			else
			{
				_frameY = 8;
				_count++;
				if (_count % 10 == 0)
				{
					_frameX++;
					if (_frameX > 7)
					{
						_frameX = 0;
					}
				}
			}
		}
		else
		{

			if (_moveAmountY <= 0)
			{
				if (_isLeft)
				{
					if (_frameY != 11)
					{
						_frameY = 11;
						_frameX = 0;
					}

					_count++;
					if (_count % 15 == 0)
					{
						_frameX++;
						if (_frameX > 5)
						{
							_frameX = 0;
						}
					}
				}
				else
				{
					if (_frameY != 10)
					{
						_frameY = 10;
						_frameX = 0;
					}

					_count++;
					if (_count % 15 == 0)
					{
						_frameX++;
						if (_frameX > 5)
						{
							_frameX = 0;
						}
					}
				}
			}
			else
			{

				if (_isLeft)
				{
					if (_frameY != 13)
					{
						SOUNDMANAGER->pause("5.fly");
						_frameY = 13;
						_frameX = 0;
					}

					_count++;
					if (_count % 10 == 0)
					{
						_frameX++;
						if (_frameX > 2)
						{
							_frameX = 0;
						}
					}
				}
				else
				{
					if (_frameY != 12)
					{
						SOUNDMANAGER->pause("5.fly");
						_frameY = 12;
						_frameX = 0;
					}

					_count++;
					if (_count % 10 == 0)
					{
						_frameX++;
						if (_frameX > 2)
						{
							_frameX = 0;
						}
					}
				}
			}
		}
	}
	break;
	
	case otDAMAGE: //������
	{
		if (_isLeft)
		{
			_frameY = 15;
			_count++;
			if (_count % 10 == 0)
			{
				_frameX++;
				if (_frameX > 5)
				{
					_frameX = 0;
				}
			}
		}
		else
		{
			_frameY = 14;
			_count++;
			if (_count % 10 == 0)
			{
				_frameX++;
				if (_frameX > 5)
				{
					_frameX = 0;
				}
				
			}
		}
	}
	break;

	case otSPIN: //ȸ�� ����
	{
		SOUNDMANAGER->stop("5.fly");

		if (_isLeft)
		{
			if (_frameY != 17 && !_attackOn)
			{
				SOUNDMANAGER->play("4.attack", _effectVolume);
				_frameY = 17;
				_frameX = 0;
				_attackOn = true;
			}
			_count++;
			if (_count % 16 == 0)
			{
				_frameX++;
				if (_frameX > 4)
				{
					_frameX = 0;
					_attackOn = false;
					_otusMove = otIDLE;
				}
			}
		}
		else
		{
			if (_frameY != 16 && !_attackOn)
			{
				SOUNDMANAGER->play("4.attack", _effectVolume);
				_frameY = 16;
				_frameX = 0;
				_attackOn = true;
			}
			_count++;
			if (_count % 16 == 0)
			{
				_frameX++;
				if (_frameX > 4)
				{
					_frameX = 0;
					_attackOn = false;
					_otusMove = otIDLE;
				}
			}
		}

	}
	break;

	case otDIE: //�ױ�
	{
		if (_isLeft)
		{
			if (_frameY !=21)
			{
				_frameY = 21;
				_frameX = 0;
			}
			
			_count++;

			if (_count % 20 == 0 && _frameX <10)
			{
				_frameX++;
			}
			else if (_count % 100 == 0 && _frameX >= 10)
			{
				_frameX++;
			}
			if (_frameX > 11)
			{
				_frameX = 0;
				_otusMove = otIDLE;
			}
			
		}
		else
		{
			if (_frameY != 20)
			{
				_frameY = 20;
				_frameX = 0;
			}
			_count++;
			if (_count % 20 == 0 && _frameX <10)
			{
				_frameX++;
			}
			else if (_count % 100 == 0 && _frameX >= 10)
			{
				_frameX++;
			}
			if (_frameX > 11)
			{
				_frameX = 0;
				_otusMove = otIDLE;
			}
			
		}
	}
	break;
	}

	if (_geddyOn)
	{
		_rc = RectMakeCenter(_x, _y + 50, _img->getFrameWidth() - 100, _img->getFrameHeight() - 25);
		_rcHit = CollisionAreaResizing(_rc, 0, -10, 0, 60);
	}
	else
	{
		_rc = RectMakeCenter(_x, _y + 40, _img->getFrameWidth() - 100, _img->getFrameHeight() - 80);
		if (_otusMove == otFLY)
		{
			_rcHit = CollisionAreaResizing(_rc, 0, -30, 0, 25);
		}
		else
		{
			_rcHit = _rc;
		}
	}

	if (_isLeft == false)//������ ���ݿ뷺Ʈ ��ġ��ȭ
	{
		_rcAtk = CollisionAreaResizing(_rc, 30, 0, -70, 0);
	}
	else if (_isLeft == true)
	{
		_rcAtk = CollisionAreaResizing(_rc, -70, 0, 30, 0);
	}
	
}

void player::render(void)
{
	_img->frameRender(_hdc, _x - (_img->getFrameWidth()/2) - CAMMANAGER->getX(), (int)(_y - (_img->getFrameHeight()/2) - CAMMANAGER->getY()), _frameX, _frameY);

	//������ ���ݷ�Ʈ ���
	if (KEYMANAGER->isToggleKey('7'))
	{
		RectangleMake(_hdc, MoveRect(_rcHit, -CAMMANAGER->getX(), -CAMMANAGER->getY()));
	}
}


//������
HRESULT player::endSceneInit(void)
{
	_endImg = IMAGEMANAGER->addFrameImage("������2", "image/������.bmp", 2160 * 2, 3520 * 2, 12, 22, true, RGB(255, 0, 255));

	return S_OK;
}
void player::endSceneUpdate(void)
{
	_frameY = 2;
	_count++;
	if (_count % 20 == 0)
	{
		_frameX++;
		if (_frameX > 8)
		{
			_frameX = 0;
		}
	}
}
void player::endRender(void)
{
	_endImg->frameRender(_hdc, WINSIZEX/2 -350 ,WINSIZEY/2 , _frameX, _frameY);
}
