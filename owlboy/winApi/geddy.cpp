#include "stdafx.h"
#include "geddy.h"

#include <atlconv.h>

HRESULT geddy::init(void)
{
	_graphics = new Graphics(getMemDC());
	_img = IMAGEMANAGER->addImage("게디", "image/player/게디.bmp", 1100, 1728, true, RGB(255, 0, 255));
	_Arm.img1 = IMAGEMANAGER->addPngImage("image/player/게디팔.png");
	IMAGEMANAGER->addFrameImage("게디소환이펙트","image/게디소환이펙트.bmp", 1264, 192,8,1,true, RGB(255, 0, 255));
	_Arm.angle = PLAYERMANAGER->getCursorAngle();
	_Arm.currentX = 0;
	_Arm.currentY = 0;
	_Arm.count = 0;
	_xGeddy = WINSIZEX / 2 - 50;
	_yGeddy = WINSIZEY / 2;
	
	_ani = new animation;
	_ani->init(_img->getWidth(), _img->getHeight(), 100, 108);
	_ani->setPlayFrame(false, false);

	_effectVolume = 1.0f;

	_geddyMove = GLANDING;
	_geddyReload_R = false;
	_motionChange = 0;
	_isGeddyLeft = false;

	_isHang = false;
	_isCollision = false;
	_geddyUpBang = false;
	_moveAmountY = 0;

	_bangBang = false;

	_bullet = new geddyBullet;
	_bullet->init(1, 600);

	_landingEnd = false;

	_combiDamage = false;

	return S_OK;
}

void geddy::release(void)
{
	_ani->release();
	SAFE_DELETE(_ani);

	_bullet->release();
	SAFE_DELETE(_bullet);
}

void geddy::update(void)
{
	_Arm.angle = PLAYERMANAGER->getCursorAngle();
	
	//합체 후 게디 총알 발사
	if (_isHang && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_bangBang = true;

		if (_isGeddyLeft == false)
		{
			_bullet->fire(_xGeddy + 20, _yGeddy + 35, PLAYERMANAGER->getCursorAngle());
		}

		if (_isGeddyLeft == true)
		{
			_bullet->fire(_xGeddy + 70, _yGeddy + 35, PLAYERMANAGER->getCursorAngle());
		}
	}

	//합체
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		if (_isHang)
		{
			_isHang = false;
			PLAYERMANAGER->setGeddyOn(false);
			_geddyMove = GLANDING;
		}
		else if (!_isHang&& MY_UTIL::getDistance(PLAYERMANAGER->getX(), PLAYERMANAGER->getY(), _xGeddy, _yGeddy) < 120)
		{
			hang();
		}
	}

	if (_isHang)
	{
		_xGeddy = PLAYERMANAGER->getX() - 48;
		_yGeddy = PLAYERMANAGER->getY() + 8;
	}
	else
	{
		if (_isCollision)
		{
			_geddyMove = GIDLE;

			_moveAmountY = 0;
		}
		else
		{
			if (_geddyMove != GIDLE)
			{
				_geddyMove = GLANDING;

				if (_moveAmountY < 5.0f) _moveAmountY += 0.1f;

				_yGeddy += _moveAmountY;
			}
		}
	}

	_rc = RectMake(_xGeddy, _yGeddy, 100, 105);

	//총 쏘는 모션 test
	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		_bangBang = true;
	}

	//변환되는지 확인위한 키
	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		_geddyReload_R = true;
	}

	if (_geddyReload_R == true) // 재장전 애니매이션 실행이 끝나게 만드는 bool 값 사용~~~
	{
		_motionChange++;
		if (_motionChange == 150)
		{
			_geddyReload_R = false;
			_geddyMove = GHANG;
			_motionChange = 0;
		}
	}
	if (_isHang)
	{
		if (PLAYERMANAGER->getCursorAngle() <= 90 || PLAYERMANAGER->getCursorAngle() >= 270)
		{
			_isGeddyLeft = false;
		}
		else
		{
			_isGeddyLeft = true;
		}
	}
	//cout << _isCollision << endl;
	if (_isHang)
	{
		//정방향 오른쪽 조준발사
		if (PLAYERMANAGER->getCursorAngle() >= 315 || PLAYERMANAGER->getCursorAngle() < 45 || (PLAYERMANAGER->getCursorAngle() >= 135 && PLAYERMANAGER->getCursorAngle() < 225))
		{
			_geddyMove = GMOVE;
		}

		//위방향 조준 발사
		else if (PLAYERMANAGER->getCursorAngle() >= 45 && PLAYERMANAGER->getCursorAngle() < 135)
		{
			_geddyMove = GHANGUP;
		}

		//아랫방향 조준 발사
		else if (PLAYERMANAGER->getCursorAngle() >= 225 && PLAYERMANAGER->getCursorAngle() < 315)
		{
			_geddyMove = GHANGDOWN;
		}
	}

	// 게디 오투스 위로 소환
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		hang();
		EFFECTMANAGER->createEffect(IMAGEMANAGER->findImage("게디소환이펙트"), PLAYERMANAGER->getX(), PLAYERMANAGER->getY() + 40);
	}
	
	if (PLAYERMANAGER->getOtusDamageOn())
	{
		_isHang = false;
		PLAYERMANAGER->setGeddyOn(false);
		_geddyMove = GLANDING;
	}




	//============================================================================
	//============================================================================
	//geddy switch문 정리
	//============================================================================
	//============================================================================

	switch (_geddyMove)
	{

	//게디 idle
	case GIDLE:
	{
		if (_isGeddyLeft == false)
		{
			_ani->setPlayFrame(0, 0,false, false);
		}

		if (_isGeddyLeft == true)
		{
			_ani->setPlayFrame(11, 11, false, false);
		}
	}
	break;

	//게디 매달리기 
	case GHANG:
	{
		if (_isGeddyLeft == false)
		{
			_ani->setPlayFrame(22, 26, false, false);
		}

		if (_isGeddyLeft == true)
		{
			_ani->setPlayFrame(33, 37, false, false);
		}
	}
	break;

	//게디 재장전
	case GRELOAD:
	{
		if (_isGeddyLeft == false)
		{
			_ani->setPlayFrame(44, 54, false, false);
		}

		if (_isGeddyLeft == true)
		{
			_ani->setPlayFrame(55, 65, false, false);
		}
	}
	break;

	//게디 정방향 조준...
	case GMOVE:
	{
		if (_isGeddyLeft == false)
		{
			_ani->setPlayFrame(66, 70, false, false);
		}

		if (_isGeddyLeft == true)
		{
			_ani->setPlayFrame(77, 81, false, false);
		}
	}
	break;

	//게디 점프
	case GJUMP:
	{
		if (_isGeddyLeft == false)
		{
			_ani->setPlayFrame(88, 88, false, false);
		}

		if (_isGeddyLeft == true)
		{
			_ani->setPlayFrame(99, 99, false, false);
		}
	}
	break;

	//게디 착지
	case GLANDING:
	{
		if (_isGeddyLeft == false)
		{
			if (!_isCollision)
			{
				_ani->setPlayFrame(110, 110, false, false);
			}
			else
			{
				_ani->setPlayFrame(111, 112, false, false);
				//_geddyMove = GIDLE;
			}
		}

		if (_isGeddyLeft == true)
		{
			if (!_isCollision)
			{
				_ani->setPlayFrame(121, 121, false, false);
			}
			else
			{
				_ani->setPlayFrame(122, 123, false, false);
				//_geddyMove = GIDLE;
			}
		}
	}
	break;

	//게디 위로 조준...
	case GHANGUP:
	{
		if (_isGeddyLeft == false)
		{
			_ani->setPlayFrame(132, 136, false, false);
		}

		if (_isGeddyLeft == true)
		{
			_ani->setPlayFrame(143, 147, false, false);
			
		}
	}
	break;

	//게디 아래로 조준...
	case GHANGDOWN:
	{
		if (_isGeddyLeft == false)
		{
			_ani->setPlayFrame(154, 158, false, false);
		}

		if (_isGeddyLeft == true)
		{
			_ani->setPlayFrame(165, 169, false, false);
		}
	}
	break;

	}

	//총을 쌌을때 실행...
	if (_bangBang == true)
	{
	//	fire();
		if (_isGeddyLeft == false)
		{
			if (_Arm.currentY != 0)
			{
				_Arm.currentX = 0;
				_Arm.currentY = 0;
			}
			_Arm.count++;
			if (_Arm.count % 9 == 0)
			{
				_Arm.currentX++;
				if (_Arm.currentX >= 4)
				{
					_Arm.currentX = 0;
					_bangBang = false;
					
				}
			}

		}
		else
		{
			if (_Arm.currentY != 1)
			{
				_Arm.currentX = 0;
				_Arm.currentY = 1;
			}
			_Arm.count++;
			if (_Arm.count % 9 == 0)
			{
				_Arm.currentX++;
				if (_Arm.currentX >= 4)
				{
					_Arm.currentX = 0;
					_bangBang = false;
					
				}
			}
		}
	}

	//총을 안쏘고 있을때....
	if (_bangBang == false)
	{
		if (_isGeddyLeft == false)
		{
			_Arm.currentX = 0;
			_Arm.currentY = 0;
		}

		if (_isGeddyLeft == true)
		{
			_Arm.currentX = 0;
			_Arm.currentY = 1;
		}
	}


	_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 8);

	_bullet->update();
}

void geddy::render(void)
{
	if (KEYMANAGER->isToggleKey('0'))
	{
		RectangleMake(getMemDC(), _rc);
	}

	 
	_img->aniRender(getMemDC(), _xGeddy - CAMMANAGER->getX(), _yGeddy - CAMMANAGER->getY(), _ani);
	

	if (_isHang == true)
	{
		if (_isGeddyLeft == true)//왼쪽일때 팔 출력
		{
			Matrix mat;
			mat.RotateAt(-_Arm.angle + 180, PointF(float(_xGeddy + 65 - CAMMANAGER->getX()), float(_yGeddy + 50 - CAMMANAGER->getY())));
			_graphics->SetTransform(&mat);
			IMAGEMANAGER->DrawPng(_graphics, _Arm.img1, _xGeddy - 15 - CAMMANAGER->getX(), _yGeddy + 45 - CAMMANAGER->getY(), _Arm.currentX, _Arm.currentY, 400, 64, 5, 2);
			}

		if (_isGeddyLeft == false)//오른쪽일때 팔 출력
		{
			Matrix mat;
			mat.RotateAt(-_Arm.angle, PointF(float(_xGeddy + 35 - CAMMANAGER->getX()), float(_yGeddy + 50 - CAMMANAGER->getY())));
			_graphics->SetTransform(&mat);
			IMAGEMANAGER->DrawPng(_graphics, _Arm.img1, _xGeddy + 35 - CAMMANAGER->getX(), _yGeddy + 45 - CAMMANAGER->getY(), _Arm.currentX, _Arm.currentY, 400, 64, 5, 2);
		}
	}
	_bullet->render();
}

void geddy::fire(void)
{
	_bullet->fire(_xGeddy, _yGeddy,PLAYERMANAGER->getCursorAngle());
}

void geddy::hang()
{
	_isHang = true;
	PLAYERMANAGER->setGeddyOn(true);
	PLAYERMANAGER->setOtusState(otFLY);
	if (PLAYERMANAGER->getIsCollision()) PLAYERMANAGER->setY(PLAYERMANAGER->getY() - 40);
}