#include "stdafx.h"
#include "tutorial.h"

#include <atlconv.h>

HRESULT tutorial::init(void)
{
	USES_CONVERSION;
	WCHAR* wstr;
	char str[128];

	sprintf(str, "image//testPlayer.png");
	wstr = A2W(str);

	graphics = new Graphics(getMemDC());

	stage::init();

	_bg = IMAGEMANAGER->addImage("Ʃ�丮��", "image/Ʃ�丮��.bmp", 1280, 1200);

	RECT temp = RectMakeCenter(-10, 490, 580, 50);
	vWall.push_back(wall(temp,false));

	RECT temp1 = RectMakeCenter(0, -155, 380, 50);
	vWall.push_back(wall(temp1, false));

	_image = IMAGEMANAGER->addImage("Mist", "image/Mist.bmp", 530, 86, true, RGB(255, 0, 255));
	for (int i = 0; i < 8; i++)
	{
		_mist[i]._x = RND->getFloat(WINSIZEX);
		_mist[i]._y = RND->getFloat(WINSIZEY);
		_mist[i]._rc = RectMakeCenter(_mist[i]._x, _mist[i]._y, _image->getWidth(), _image->getHeight());
		_mist[i]._speed = RND->getFromFloatTo(0.1f, 1.0f);
	}
	RECT _nextScene = RectMakeCenter(0, -550, 50, 50);

	
	vWall.push_back(wall(_nextScene, false));
	
	PLAYERMANAGER->setX(0);
	PLAYERMANAGER->setY(392);
	_geddy->setX(2000);
	_geddy->setY(200);

	CAMMANAGER->init(); // ī�޶� �÷��̾� ���� ��ġ�� �ٷ� ��ġ��Ű�� ����.
	CAMMANAGER->setCamLimit(-640, -640, -600, -200);

	_isPlaySound = true;
	return S_OK;
}

void tutorial::release(void)
{
	stage::release();
	SAFE_DELETE(graphics);
}

void tutorial::update(void)
{
	if (_isPlaySound)
	{
		SOUNDMANAGER->play("002.tutorial", _backgroundVolume);
		_isPlaySound = false;
	}

	playMoveLimit("right", 560);
	playMoveLimit("left", -560);
	playMoveLimit("up", -560);
	playMoveLimit("down", 550);
	stage::update();
	moveMist();
	nextScene();
}

void tutorial::render(void)
{
	// �� �׸���
	_bg->render(getMemDC(), -640 - CAMMANAGER->getX(), -600 - CAMMANAGER->getY());

	for (int i = 0; i < 8; i++)
	{
		_image->alphaRender(getMemDC(), _mist[i]._rc.left - CAMMANAGER->getX(), _mist[i]._rc.top - CAMMANAGER->getY(), 50);
	}

	

	PLAYERMANAGER->render();
	stage::render();
}

void tutorial::DrawPng(Image* tempimage, int x, int y)
{
	Image* img = tempimage;
	graphics->DrawImage(img, x, y);
	img = NULL;
	delete img;
}

//����ȯ
void tutorial::nextScene(void)
{
	RECT _rcTemp;
	if (IntersectRect(&_rcTemp, &vWall[2]._rect, &PLAYERMANAGER->getRect()))
	{
		if (_fadeScale >= 0.25f)
		{
			_fadeScale -= 0.25f;
		}
		else
		{
			_fadeScale = 11.0f;
			SCENEMANAGER->changeScene("����");
			SOUNDMANAGER->stop("002.tutorial");
		}
	}
}
//�Ȱ� �����̱�
void tutorial::moveMist(void)
{
	for (int i = 0; i < 8; i++)
	{
		_mist[i]._x -= _mist[i]._speed;
		_mist[i]._rc = RectMakeCenter(_mist[i]._x, _mist[i]._y, _image->getWidth(), _image->getHeight());
		if (_mist[i]._rc.right < -WINSIZEX)
		{
			_mist[i]._x = RND->getFromFloatTo(WINSIZEX + WINSIZEX / 2, WINSIZEX * 2);
			_mist[i]._speed = RND->getFromFloatTo(1.0f, 3.0f);
		}
	}
}