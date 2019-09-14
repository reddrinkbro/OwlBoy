#include "stdafx.h"
#include "village.h"

HRESULT village::init(void)
{
	stage::init();
	_imageSky = IMAGEMANAGER->addImage("�����ϴ�", "image/skyScreen.bmp", 2560,4000);
	_imageGrass1 = IMAGEMANAGER->addFrameImage("�ܵ�", "image/object/�ܵ�.bmp", 480, 32, 5, 1, true, RGB(255, 0, 255));
	_imageGrass2 = IMAGEMANAGER->addFrameImage("�ܵ�2", "image/object/�ܵ�2.bmp", 480, 32, 5, 1, true, RGB(255, 0, 255));
	_imageGrass3 = IMAGEMANAGER->addFrameImage("�ܵ�3", "image/object/�ܵ�3.bmp", 480, 32, 5, 1, true, RGB(255, 0, 255));
	_imageGrass4 = IMAGEMANAGER->addFrameImage("�ܵ�4", "image/object/�ܵ�4.bmp", 480, 32, 5, 1, true, RGB(255, 0, 255));
	_imageBush1 = IMAGEMANAGER->addFrameImage("�ν�", "image/object/�ν�.bmp", 320, 40, 8, 1, true, RGB(255, 0, 255));
	_imageBush2 = IMAGEMANAGER->addFrameImage("�ν�2", "image/object/�ν�2.bmp", 832, 88, 8, 1, true, RGB(255, 0, 255));
	_imageTree1 = IMAGEMANAGER->addFrameImage("����", "image/object/����.bmp", 560, 52, 8, 1, true, RGB(255, 0, 255));
	_bg = IMAGEMANAGER->addImage("����", "image/����.bmp", 2560, 4000, true, RGB(255, 0, 255));
	CAMMANAGER->setCamLimit(-640, 630, -600, 2345);
	
	_isPlaySound = true;
	for (int i = 0; i < 9; i++)
	{
		if (i % 3 == 0)
		{
			_cloud[i].image = IMAGEMANAGER->addImage("����1", "image/cloud1.bmp", 380, 212,true,RGB(255,0,255));
			_cloud[i].x = RND->getFloat(-2560);
			_cloud[i].y = RND->getFloat(4000);
			_cloud[i].rc = RectMakeCenter(_cloud[i].x, _cloud[i].y, _cloud[i].image->getWidth(), _cloud[i].image->getHeight());
			_cloud[i].speed = RND->getFromFloatTo(1.0f, 2.0f);
		}
		else if (i % 3 == 1)
		{
			_cloud[i].image = IMAGEMANAGER->addImage("����2", "image/cloud2.bmp", 848, 266, true, RGB(255, 0, 255));
			_cloud[i].x = RND->getFloat(-2560);
			_cloud[i].y = RND->getFloat(4000);
			_cloud[i].rc = RectMakeCenter(_cloud[i].x, _cloud[i].y, _cloud[i].image->getWidth(), _cloud[i].image->getHeight());
			_cloud[i].speed = RND->getFromFloatTo(1.0f, 2.0f);
		}
		else
		{
			_cloud[i].image = IMAGEMANAGER->addImage("����2", "image/cloud2.bmp", 690, 602, true, RGB(255, 0, 255));
			_cloud[i].x = RND->getFloat(-2560);
			_cloud[i].y = RND->getFloat(4000);
			_cloud[i].rc = RectMakeCenter(_cloud[i].x, _cloud[i].y, _cloud[i].image->getWidth(), _cloud[i].image->getHeight());
			_cloud[i].speed = RND->getFromFloatTo(1.0f, 2.0f);
		}
	}
	
	vWall.push_back(wall({ -600, 675, -320, 720 }, false));
	vWall.push_back(wall({ 210, 971, 612, 1025 }, false));
	vWall.push_back(wall({ 1006, 997, 1900, 1050 }, false));
	vWall.push_back(wall({ -580, 1195, -108, 1250 }, false));
	vWall.push_back(wall({ -560, 2625, 40, 2690 }, false));
	vWall.push_back(wall({ 1506, 2667, 1900, 2760 }, false));
	vWall.push_back(wall({ 1450, 1680, 1700, 1735 }, false));
	vWall.push_back(wall({ 1392, 1995, 1830, 2050 }, false));
	
	_worldTimeCount = TIMEMANAGER->getWorldTime();
	_rndTimeCount = RND->getFromFloatTo(0.04f, 0.1f);
	//�ܵ� ������
	_grassFrameX = 0;
	_bushFrameX = 0;
	_treeFrameX = 0;
	_count = 0;

	PLAYERMANAGER->setIsLeft(true);
	PLAYERMANAGER->setOtusState(otJUMP);
	PLAYERMANAGER->setX(1510);
	PLAYERMANAGER->setY(1915);
	_geddy->setX(330);
	_geddy->setY(880);

	CAMMANAGER->init();
	CAMMANAGER->setCamLimit(-640, 630, -600, 2345);
	
	_nextScene = RectMakeCenter(-530, 2550, 50, 50);
	return S_OK;
}

void village::release(void)
{
	stage::release();
}

void village::update(void)
{
	//������
	if (_rndTimeCount + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		_count++;
		//10
		//�ܵ� ������
		if (_count % 10 == 0)
		{
			_grassFrameX++;
		}
		if (_count % 2 == 0)
		{
			//����
			_treeFrameX++;
			//�ν�
			_bushFrameX++;
		}
		if (_imageGrass1->getMaxFrameX() < _grassFrameX)
		{
			_grassFrameX = 0;
			
		}
		if (_imageBush1->getMaxFrameX() < _bushFrameX)
		{
			_bushFrameX = 0;
		}
	}
	
	//����
	if (_isPlaySound)
	{
		SOUNDMANAGER->play("003.village", _backgroundVolume);
		_isPlaySound = false;
	}

	//����
	for (int i = 0; i < 9; i++)
	{
		if (_cloud[i].x < 2560)
		{
			_cloud[i].x += _cloud[i].speed;
		}
		else
		{
			_cloud[i].x = RND->getFloat(-WINSIZEX);
			_cloud[i].y = RND->getFloat(WINSIZEY);
		}
		_cloud[i].rc = RectMakeCenter(_cloud[i].x, _cloud[i].y, _cloud[i].image->getWidth(), _cloud[i].image->getHeight());
	}


	playMoveLimit("left", -560);
	playMoveLimit("right", 1830);
	playMoveLimit("up", -570);
	playMoveLimit("down", 3100);
	stage::update();
	nextScene();
}

void village::render(void)
{
	// �� �׸���
	_imageSky->render(getMemDC());

	//����
	for (int i = 0; i < 9; i++)
	{
		_cloud[i].image->render(getMemDC(), _cloud[i].rc.left - CAMMANAGER->getX(), _cloud[i].rc.top - CAMMANAGER->getY());
	}
	_bg->render(getMemDC(), -640 - CAMMANAGER->getX(), -600 - CAMMANAGER->getY());
	

	
	//���� ���� �� ������
	{
		_imageGrass1->frameRender(getMemDC(), -590 - CAMMANAGER->getX(), 667 - CAMMANAGER->getY(), _grassFrameX, 0);
		_imageGrass2->frameRender(getMemDC(), -498 - CAMMANAGER->getX(), 667 - CAMMANAGER->getY(), _grassFrameX, 0);
	}
	// ���� �߰� ������
	{
		_imageGrass1->frameRender(getMemDC(), -580 - CAMMANAGER->getX(), 1187 - CAMMANAGER->getY(), _grassFrameX, 0);
		_imageGrass2->frameRender(getMemDC(), -530 - CAMMANAGER->getX(), 1187 - CAMMANAGER->getY(), _grassFrameX, 0);
		_imageGrass3->frameRender(getMemDC(), -420 - CAMMANAGER->getX(), 1187 - CAMMANAGER->getY(), _grassFrameX, 0);
		_imageGrass2->frameRender(getMemDC(), -370 - CAMMANAGER->getX(), 1187 - CAMMANAGER->getY(), _grassFrameX, 0);
		_imageGrass1->frameRender(getMemDC(), -310 - CAMMANAGER->getX(), 1190 - CAMMANAGER->getY(), _grassFrameX, 0);
		_imageGrass3->frameRender(getMemDC(), -260 - CAMMANAGER->getX(), 1190 - CAMMANAGER->getY(), _grassFrameX, 0);
	}
	
	//���� �Ա� 
	{
		_imageGrass3->frameRender(getMemDC(), -530 - CAMMANAGER->getX(), 2620 - CAMMANAGER->getY(), _grassFrameX, 0);
		_imageGrass2->frameRender(getMemDC(), -480 - CAMMANAGER->getX(), 2619 - CAMMANAGER->getY(), _grassFrameX, 0);
		_imageGrass1->frameRender(getMemDC(), -430 - CAMMANAGER->getX(), 2620 - CAMMANAGER->getY(), _grassFrameX, 0);
		_imageGrass1->frameRender(getMemDC(), -380 - CAMMANAGER->getX(), 2621 - CAMMANAGER->getY(), _grassFrameX, 0);
		_imageGrass3->frameRender(getMemDC(), -330 - CAMMANAGER->getX(), 2620 - CAMMANAGER->getY(), _grassFrameX, 0);
		_imageGrass2->frameRender(getMemDC(), -280 - CAMMANAGER->getX(), 2620 - CAMMANAGER->getY(), _grassFrameX, 0);
		_imageGrass1->frameRender(getMemDC(), -230 - CAMMANAGER->getX(), 2620 - CAMMANAGER->getY(), _grassFrameX, 0);
		_imageGrass3->frameRender(getMemDC(), -180 - CAMMANAGER->getX(), 2620 - CAMMANAGER->getY(), _grassFrameX, 0);
		_imageGrass2->frameRender(getMemDC(), -130 - CAMMANAGER->getX(), 2620 - CAMMANAGER->getY(), _grassFrameX, 0);
		_imageGrass1->frameRender(getMemDC(), -80 - CAMMANAGER->getX(), 2620 - CAMMANAGER->getY(), _grassFrameX, 0);
		_imageGrass3->frameRender(getMemDC(), -40 - CAMMANAGER->getX(), 2620 - CAMMANAGER->getY(), _grassFrameX, 0);
	}
	
	//����
	{
		_imageBush2->frameRender(getMemDC(), 193 - CAMMANAGER->getX(), 887 - CAMMANAGER->getY(), _bushFrameX, 0);
	}

	//������
	{
		_imageBush2->frameRender(getMemDC(), 1644 - CAMMANAGER->getX(), 917 - CAMMANAGER->getY(), _bushFrameX, 0);
	}

	//��
	{
		_imageBush2->frameRender(getMemDC(), 1750 - CAMMANAGER->getX(), 1915 - CAMMANAGER->getY(), _bushFrameX, 0);
	}

	PLAYERMANAGER->render();
	
	stage::render();

}

// ���� �� (����)
void village::nextScene(void)
{
	RECT _rcTemp;
	if (IntersectRect(&_rcTemp, &_nextScene, &PLAYERMANAGER->getRect()))
	{
		if (_fadeScale >= 0.25f)
		{
			_fadeScale -= 0.25f;
		}
		else
		{
			_fadeScale = 11.0f;
			SCENEMANAGER->changeScene("����");
			SOUNDMANAGER->stop("003.village");
		}
	}
}

