#include "stdafx.h"
#include "bossScene.h"

HRESULT bossScene::init(void)
{
	_image = IMAGEMANAGER->addImage("bossStage", "image/bossStage.bmp", WINSIZEX, WINSIZEY);
	_fadeOutImage = IMAGEMANAGER->addImage("BlackBackground", "image/playerDieScene.bmp", WINSIZEX, WINSIZEY);
	
	CAMMANAGER->setCamLimit(0, 0, 0, 0);
	
	_rc[0] = RectMake(0, WINSIZEY - 100, WINSIZEX, 100);
	vWall.push_back(wall(_rc[0],false));
	_rc[1] = RectMake(0, 0, 90, 200);  //왼쪽 위
	vWall.push_back(wall(_rc[1], true));
	_rc[2] = RectMake(WINSIZEX - 120, 0, 120, 200); //오른쪽 위
	vWall.push_back(wall(_rc[2], true));
	_graphics = new Graphics(getMemDC());

	PLAYERMANAGER->setX(1000);
	PLAYERMANAGER->setY(600);
	PLAYERMANAGER->setGeddyOn(false);
	PLAYERMANAGER->setOtusState(otIDLE);

	stage::init();


	_geddy->setIsHang(false);
	_geddy->setIsGeddyLeft(true);

	_geddy->setX(1000);
	_geddy->setY(600);

	_waterfall.image = IMAGEMANAGER->addPngImage("image/waterfall.png");
	_waterfall._currentX = 0;
	_enemyManager = new enemyManager;
	_enemyManager->init(false);
	_fadeCount = 0;
	_isPlaySound = true;
	CAMMANAGER->setZoom(1.0f);
	return S_OK;
}

void bossScene::release(void)
{
	_enemyManager->release();
	SAFE_DELETE(_enemyManager);
	stage::release();
}

void bossScene::update(void)
{
	if (_enemyManager->getBoss()->getPlayBossSound())
	{
		SOUNDMANAGER->play("005.Turtle Guardian", _backgroundVolume);
		_enemyManager->getBoss()->setPlayBossSound(false);
	}
	_enemyManager->update(false);
	shieldCollision();
	if (_waterfall.count + 0.2f < TIMEMANAGER->getWorldTime())
	{
		_waterfall.count = TIMEMANAGER->getWorldTime();
		_waterfall._currentX++;
		if (_waterfall._currentX > 2)
		{
			_waterfall._currentX = 0;
		}
	}
	playMoveLimit("right", WINSIZEX - 70);
	playMoveLimit("left", 70);
	playMoveLimit("up", 60);
	playerCollision();
	if (_enemyManager->getBoss()->getIsStart())
	{
		bossPlayerCollsion();
	}
	stage::update();
	CAMMANAGER->setZoom(1.0f);
	if (_enemyManager->getBoss()->getBossState() == BOSS_DIE)
	{
		_fadeCount ++;
		if (_fadeCount >= 255)
		{
			SCENEMANAGER->changeScene("엔딩씬");
			SOUNDMANAGER->stop("005.Turtle Guardian");
		}
	}
}

void bossScene::render(void)
{
	_image->render(getMemDC(), -CAMMANAGER->getX(), -CAMMANAGER->getY());
	IMAGEMANAGER->DrawPng(_graphics, _waterfall.image, WINSIZEX / 2 - 155, WINSIZEY / 2 + 12, _waterfall._currentX, 0, 66, 280, 3, 1);
	IMAGEMANAGER->DrawPng(_graphics, _waterfall.image, WINSIZEX / 2 + 155, WINSIZEY / 2 + 12, _waterfall._currentX, 0, 66, 280, 3, 1);
	// 적 그리기
	_enemyManager->render();
	PLAYERMANAGER->render();
	stage::render();
	_fadeOutImage->alphaRender(getMemDC(), _fadeCount);
}

void bossScene::shieldCollision(void)
{
	RECT _rcTemp;
	//방패가 땅에 떨어졌을때
	for (int i = 0; i < _enemyManager->getBoss()->getShield()->getVShield().size(); i++)
	{
		if (_rc[0].top < _enemyManager->getBoss()->getShield()->getVShield()[i]._rc.bottom)
		{
			_enemyManager->getBoss()->getShield()->bumpGround();
		}
	}
}

void bossScene::playerCollision(void)
{
	RECT _rcTemp;
	if (PLAYERMANAGER->getX() < _rc[1].right)
	{
		if (IntersectRect(&_rcTemp, &_rc[1], &PLAYERMANAGER->getRect()))
		{
			PLAYERMANAGER->setX(_rc[1].right);
		}
	}
	if (PLAYERMANAGER->getX() > _rc[2].left)
	{
		if (IntersectRect(&_rcTemp, &_rc[2], &PLAYERMANAGER->getRect()))
		{
			PLAYERMANAGER->setX(_rc[2].left);
		}
	}
}

void bossScene::bossPlayerCollsion(void)
{
	RECT _rcTemp;
	//플레이어 -> 보스
	for (int i = 0; i < _geddy->getBullet()->getBulletVector().size(); i++)
	{
		if (IntersectRect(&_rcTemp, &CollisionAreaResizing(_enemyManager->getBoss()->getRect(),20,0,20,0), &_geddy->getBullet()->getBulletVector()[i].rc))
		{
			_geddy->getBullet()->removeBullet(i);
			_enemyManager->getBoss()->decreaseHp();
			break;
		}
	}
	//보스 -> 플레이어
	for (int i = 0; i < _enemyManager->getBoss()->getBullet()->getBulletVector().size(); i++)
	{
		if (IntersectRect(&_rcTemp, &_enemyManager->getBoss()->getBullet()->getBulletVector()[i].rc, &PLAYERMANAGER->getRect())&& !PLAYERMANAGER->getOtusDamageOn())
		{
			_enemyManager->getBoss()->getBullet()->removeBullet(i);
			PLAYERMANAGER->setOtusState(otDAMAGE);
			PLAYERMANAGER->setHp(PLAYERMANAGER->getHp() - 1);
			PLAYERMANAGER->setOtusDamageOn(true);
			break;
		}
	}
	if (IntersectRect(&_rcTemp, &_enemyManager->getBoss()->getRect(), &PLAYERMANAGER->playerHitRect())&& !PLAYERMANAGER->getOtusDamageOn())
	{
		PLAYERMANAGER->setOtusState(otDAMAGE);
		PLAYERMANAGER->setHp(PLAYERMANAGER->getHp() - 1);
		PLAYERMANAGER->setOtusDamageOn(true);
	}
	if (IntersectRect(&_rcTemp, &_enemyManager->getBoss()->getRect(), &PLAYERMANAGER->playerAttackRect()) && PLAYERMANAGER->getOtusState() == otSPIN)
	{		
		_enemyManager->getBoss()->setBossState(HIT);
	}
}
