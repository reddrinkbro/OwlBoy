#include "stdafx.h"
#include "dungeon.h"

HRESULT dungeon::init(void)
{
	stage::init();

	_bg = IMAGEMANAGER->addImage("dungeon", "image/dungeon.bmp",7680,1600);
	CAMMANAGER->setCamLimit(-640, 5750, -600, 175);

	_imageBush1 = IMAGEMANAGER->addFrameImage("던전부쉬1", "image/object/부쉬.bmp", 2176, 126, 16, 1, true, RGB(255, 0, 255));
	_imageBush2 = IMAGEMANAGER->addFrameImage("던전부쉬2", "image/object/부쉬.bmp", 2176, 126, 16, 1, true, RGB(255, 0, 255));
	_imageBush3= IMAGEMANAGER->addFrameImage("던전부쉬3", "image/object/부쉬.bmp", 2176, 126, 16, 1, true, RGB(255, 0, 255));
	_imageBush4 = IMAGEMANAGER->addFrameImage("던전부쉬4", "image/object/부쉬.bmp", 2176, 126, 16, 1, true, RGB(255, 0, 255));

	_imageDoor = IMAGEMANAGER->addFrameImage("문", "image/object/문3.bmp", 2464*1.5, 394*1.5, 11, 1, true, RGB(255, 0, 255));
	_imageButton = IMAGEMANAGER->addFrameImage("버튼","image/object/버튼.bmp",2584,86,17,1,true,RGB(255,0,255));	
	
	_isPlaySound = true;

	_enemyManager = new enemyManager;
	_enemyManager->init(true);

	//문열림 버튼
	_rcButton = RectMakeCenter(4273, 625,105, 60);
	//문열린 후 아래 충돌렉트
	_doorOpenRc[0] = RectMake(3750, 510, 200, 100);
	vWall.push_back(wall(_doorOpenRc[0], true));
	//문열린 후 위 충돌렉트
	_doorOpenRc[1] = RectMake(3756, 100, 250, 215);
	vWall.push_back(wall(_doorOpenRc[1], true));
	//문 닫혔을때 충돌렉트
	_doorCloseRc = RectMake(4020, 190, 10, 500);

	//프레임
	_bushFrameX = 0;
	_buttonFrameX = 0;
	_doorFrameX = 0;
	
	//카운트
	_bushCount = 0;
	_buttonCount = 0;
	_pushCount = 0;
	_doorCount = 0;
	_doorStart = false;
	_buttonStop = false;
	_buttonOn = false;

	RECT temp = RectMake(-700, 640, 8100, 50);
	vWall.push_back(wall(temp,true));

	RECT temp1 = RectMake(-700, -400, 6000, 50);
	vWall.push_back(wall(temp1, true));

	RECT temp2 = RectMake(3500, -350, 4000, 350);
	vWall.push_back(wall(temp2, true));

	RECT temp3 = RectMake(3950, 0, 3100, 190);
	vWall.push_back(wall(temp3, true));

	RECT temp4 = RectMake(3400, -350, 100, 240);
	vWall.push_back(wall(temp4, true));

	//테스트용임.
	PLAYERMANAGER->setX(6800);
	PLAYERMANAGER->setY(560);
	PLAYERMANAGER->setGeddyOn(false);

	_geddy->setIsHang(false);
	_geddy->setIsGeddyLeft(true);
	
	_geddy->setX(6720);
	_geddy->setY(560);

	CAMMANAGER->init();
	CAMMANAGER->setCamLimit(-640, 5750, -600, 175);

	PLAYERMANAGER->setOtusState(otIDLE);

	_nextScene = RectMakeCenter(-730, 0, 50, 1600);

	return S_OK;
}

void dungeon::release(void)
{
	_enemyManager->release();
	SAFE_DELETE(_enemyManager);

	stage::release();
}

void dungeon::update(void)
{
	//프레임
	if (_rndTimeCount + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		_bushCount++;
		if (_doorOk)
		{
			_buttonCount++;
		}

		//10
		//부쉬 프레임
		if (_bushCount % 10 == 0)
		{
			_bushFrameX++;
		}	
		
		if (_imageBush1->getMaxFrameX() < _bushFrameX)
		{
			_bushFrameX = 0;
		}
		if (_buttonOn)
		{
			//버튼 프레임
			if (!_buttonStop)
			{
				PLAYERMANAGER->setIsCollision(true);
				//버튼 프레임
				if (_buttonCount % 20 == 0)
				{
					_buttonFrameX++;
				}
				if (_imageButton->getMaxFrameX() < _buttonFrameX)
				{
					_buttonStop = true;
					if (_buttonCount >= 500)
					{
						_doorStart = true;
					}
				}
			}
			if (_doorStart)
			{
				_doorCount++;
				//문 프레임
				if (_doorCount % 20 == 0)
				{
					_doorFrameX++;
				}

				if (_imageDoor->getMaxFrameX() < _doorFrameX)
				{
				
				}
			}
		}
	}

	//버튼 충돌_1
	if (IntersectRect(&_rcTemp, &_geddy->getRect(), &_rcButton))
	{
		_geddy->setY(_geddy->getY() - (_rcTemp.bottom - _rcTemp.top));
		if (_rcButton.top - 10 < _geddy->getRect().bottom)
		{
			//_geddy->getY()
			_buttonOn = true;
			_pushCount++;
			if (_pushCount % 55 == 1)
			{		
				if (_rcButton.top <= 655)
				{
					_rcButton.top += 4;
					
				}
				else
				{
					_doorOk = true;
				}

			}
		}
	}
	
	//문통과 x
	if (IntersectRect(&_rcTemp, &PLAYERMANAGER->getRect(), &_doorCloseRc))
	{
		PLAYERMANAGER->setX(PLAYERMANAGER->getX() -(_rcTemp.left - _rcTemp.right));
	}
	//문통과 o
	if (_buttonOn && _doorFrameX >= _imageDoor->getMaxFrameX())
	{
		_doorCloseRc = RectMake(0, 0, 0, 0);
	}

	//문 오픈 후 아래 충돌렉트
	if (IntersectRect(&_rcTemp, &PLAYERMANAGER->getRect(), &_doorOpenRc[0]))
	{
		PLAYERMANAGER->setY(PLAYERMANAGER->getY() - (_rcTemp.bottom - _rcTemp.top));
		PLAYERMANAGER->setIsCollision(true);
	}

	//문 오픈 후 위 충돌렉트
	if (IntersectRect(&_rcTemp, &PLAYERMANAGER->getRect(), &_doorOpenRc[1]))
	{
		if (_doorOpenRc[1].bottom > PLAYERMANAGER->getRect().top && _doorOpenRc[1].left < PLAYERMANAGER->getRect().left && _doorOpenRc[1].right > PLAYERMANAGER->getRect().right)
		{
			PLAYERMANAGER->setY(PLAYERMANAGER->getY() - (_rcTemp.top- _rcTemp.bottom));
		}
		

	}

	if (_isPlaySound)
	{
		SOUNDMANAGER->play("004.Vellie Cave", _backgroundVolume);
		_isPlaySound = false;
	}

	_enemyManager->update(_doorStart);

	playMoveLimit("right", 7000);
	playMoveLimit("up", -400);
	stage::update();
	nextScene();
	bulletColllsionArea();
	otusAttackCollisionArea();
}

void dungeon::render(void)
{
	_bg->render(getMemDC(), -640- CAMMANAGER->getX(),-600- CAMMANAGER->getY());
	_enemyManager->render();

	//부쉬
	_imageBush1->frameRender(getMemDC(), 900 - CAMMANAGER->getX(), 520 - CAMMANAGER->getY(), _bushFrameX, 0);
	_imageBush2->frameRender(getMemDC(), 200 - CAMMANAGER->getX(), 520 - CAMMANAGER->getY(), _bushFrameX, 0);
	_imageBush3->frameRender(getMemDC(), 2400 - CAMMANAGER->getX(), 520 - CAMMANAGER->getY(), _bushFrameX, 0);
	_imageBush4->frameRender(getMemDC(), -500 - CAMMANAGER->getX(), 520 - CAMMANAGER->getY(), _bushFrameX, 0);

	//버튼
	_imageButton->frameRender(getMemDC(), 4200 - CAMMANAGER->getX(), 570 - CAMMANAGER->getY(), _buttonFrameX, 0);
	//문
	_imageDoor->frameRender(getMemDC(), 3750 - CAMMANAGER->getX(), 120 - CAMMANAGER->getY(), _doorFrameX, 0);

	PLAYERMANAGER->render();
	stage::render();
	
}

void dungeon::nextScene(void)
{
	RECT _rcTemp;
	if (IntersectRect(&_rcTemp, &_nextScene, &PLAYERMANAGER->getRect()))
	{
		SCENEMANAGER->changeScene("보스스테이지");
		SOUNDMANAGER->stop("004.Vellie Cave");
	}
}

void dungeon::bulletColllsionArea(void)
{
	RECT _rcTemp;
	//gawk 충돌
	for (int i = 0; i < _geddy->getBullet()->getBulletVector().size(); i++)
	{
		for (int j = 0; j < _enemyManager->getGawk().size(); j++)
		{
			if (IntersectRect(&_rcTemp, &_geddy->getBullet()->getBulletVector()[i].rc, &CollisionAreaResizing(_enemyManager->getGawk()[j]->getRect(), 25, 60, 50, 25)))
			{
				_geddy->getBullet()->removeBullet(i);
				_enemyManager->getGawk()[j]->sethit(true);
				_enemyManager->getGawk()[j]->setHp(_enemyManager->getGawk()[j]->getHp() - 5);
				SOUNDMANAGER->play("7.monsterHit", 1.0f);
				EFFECTMANAGER->createEffect(IMAGEMANAGER->findImage("flair"), _rcTemp.left, _rcTemp.top);
				if (_enemyManager->getGawk()[j]->getHp() <= 0)
				{
					EFFECTMANAGER->createEffect(IMAGEMANAGER->findImage("explosion"),
						_enemyManager->getGawk()[j]->getRect().left + (_enemyManager->getGawk()[j]->getRect().right - _enemyManager->getGawk()[j]->getRect().left) / 2,
						_enemyManager->getGawk()[j]->getRect().top + (_enemyManager->getGawk()[j]->getRect().bottom - _enemyManager->getGawk()[j]->getRect().top) / 2);
					_enemyManager->removeGawk(j);
				}
				break;
			}
		}
	}
	//spikeball 충돌
	for (int i = 0; i < _geddy->getBullet()->getBulletVector().size(); i++)
	{
		for (int j = 0; j < _enemyManager->getspikeBall().size(); j++)
		{
			if (IntersectRect(&_rcTemp, &_geddy->getBullet()->getBulletVector()[i].rc, &CollisionAreaResizing(_enemyManager->getspikeBall()[j]->getRect(), 30, 30, 30, 30)))
			{
				_geddy->getBullet()->removeBullet(i);
				_enemyManager->getspikeBall()[j]->setHp(_enemyManager->getspikeBall()[j]->getHp() - 5);
				SOUNDMANAGER->play("7.monsterHit", 1.0f);
				EFFECTMANAGER->createEffect(IMAGEMANAGER->findImage("flair"), _rcTemp.left, _rcTemp.top);
				if (_enemyManager->getspikeBall()[j]->getHp() <= 0)
				{
					EFFECTMANAGER->createEffect(IMAGEMANAGER->findImage("explosion"),
						_enemyManager->getspikeBall()[j]->getRect().left + (_enemyManager->getspikeBall()[j]->getRect().right - _enemyManager->getspikeBall()[j]->getRect().left) / 2 ,
						_enemyManager->getspikeBall()[j]->getRect().top + (_enemyManager->getspikeBall()[j]->getRect().bottom - _enemyManager->getspikeBall()[j]->getRect().top) / 2);
					_enemyManager->removeSpikeBall(j);
				}
				break;
			}
		}
	}
	//torque 충돌
	for (int i = 0; i < _geddy->getBullet()->getBulletVector().size(); i++)
	{
		for (int j = 0; j < _enemyManager->getTorque().size(); j++)
		{
			if (IntersectRect(&_rcTemp, &_geddy->getBullet()->getBulletVector()[i].rc, &CollisionAreaResizing(_enemyManager->getTorque()[j]->getRect(), 60, 30, 60, 0)))
			{
				_geddy->getBullet()->removeBullet(i);
				_enemyManager->getTorque()[j]->setIsHit(true);
				SOUNDMANAGER->play("7.monsterHit", 1.0f);
				_enemyManager->getTorque()[j]->setHp(_enemyManager->getTorque()[j]->getHp() - 5);
				EFFECTMANAGER->createEffect(IMAGEMANAGER->findImage("flair"), _rcTemp.left, _rcTemp.top);
				if (_enemyManager->getTorque()[j]->getHp() <= 0)
				{
					EFFECTMANAGER->createEffect(IMAGEMANAGER->findImage("explosion"),
						_enemyManager->getTorque()[j]->getRect().left + (_enemyManager->getTorque()[j]->getRect().right - _enemyManager->getTorque()[j]->getRect().left) / 2,
						_enemyManager->getTorque()[j]->getRect().top + (_enemyManager->getTorque()[j]->getRect().bottom - _enemyManager->getTorque()[j]->getRect().top) / 2);
					_enemyManager->removeTorque(j);
				}
				break;
			}
		}
	}
}

void dungeon::otusAttackCollisionArea(void)
{
	RECT _rcTemp;
	for (int i = 0; i < _enemyManager->getGawk().size(); i++)
	{
		if (IntersectRect(&_rcTemp, &CollisionAreaResizing(_enemyManager->getGawk()[i]->getRect(), 0, 60, 50, 25), &PLAYERMANAGER->playerAttackRect()) && PLAYERMANAGER->getOtusState()== otSPIN)
		{
			_enemyManager->getGawk()[i]->sethit(true);
		
		}
	}
	for (int i = 0; i < _enemyManager->getTorque().size(); i++)
	{
		if (IntersectRect(&_rcTemp, &CollisionAreaResizing(_enemyManager->getTorque()[i]->getRect(), 60, 30, 60, 0), &PLAYERMANAGER->playerAttackRect()) && PLAYERMANAGER->getOtusState() == otSPIN)
		{
			_enemyManager->getTorque()[i]->setIsHit(true);

		}
	}
}
