#include "stdafx.h"
#include "stage.h"
#include "geddy.h"

HRESULT stage::init(void)
{
	_graphics = new Graphics(getMemDC());
	_fade = IMAGEMANAGER->addPngImage("image/circleFade.png");
	_fadeScale = 11.0f;

	_cursor = IMAGEMANAGER->addFrameImage("cursor", "image/arrow.bmp", 432, 216, 6, 3, true, RGB(255, 0, 255));
	_cursorIdx = 0;

	_portrait = IMAGEMANAGER->addImage("portrait", "image/geddyPortrait.bmp", 38, 38, true, RGB(255, 0, 255));

	ShowCursor(false);

	_debugMode = false;

	_geddy = new geddy;
	_geddy->init();

	_titleScene = new titleScene;
	_titleScene->init();

	_backgroundVolume =OPTIONMANAGER->getMusicVolume();
	PLAYERMANAGER->setVolume(OPTIONMANAGER->getSoundVolume());
	_geddy->setVolume(OPTIONMANAGER->getSoundVolume());
	CAMMANAGER->setZoom(1.5f);

	_progressBar = new progressBar;
	_progressBar->init("image/playerHpTop", "image/playerHpBottom", 0, 0, 74, 24);
	SOUNDMANAGER->addSound("002.tutorial", "sound/Flying Lessons.mp3", true, true);
	SOUNDMANAGER->addSound("003.village", "sound/Vellie.mp3", true, true);
	SOUNDMANAGER->addSound("004.Vellie Cave", "sound/Vellie Cave.mp3", true, true);
	SOUNDMANAGER->addSound("005.Turtle Guardian", "sound/Turtle Guardian.mp3", true, true);
	SOUNDMANAGER->addSound("1.run", "sound/run.mp3", false, true);
	SOUNDMANAGER->addSound("2.jump", "sound/jump.mp3", false, false);
	SOUNDMANAGER->addSound("3.landing", "sound/landing.mp3", false, false);
	SOUNDMANAGER->addSound("4.attack", "sound/attack.mp3", false, false);
	SOUNDMANAGER->addSound("5.fly", "sound/fly.mp3", false, true);
	SOUNDMANAGER->addSound("6.shooting", "sound/shooting.mp3", false, false);
	SOUNDMANAGER->addSound("7.monsterHit", "sound/monsterHit.mp3", false, false);

	_shadow = new shadow;
	_shadow->vShadow.push_back(new shadowStruct(PLAYERMANAGER->getXpointer(), PLAYERMANAGER->getYpointer(), 0, 100));
	_shadow->vShadow.push_back(new shadowStruct(_geddy->getXpointer(), _geddy->getYpointer(), 50, 100));

	return S_OK;
}

void stage::release(void)
{
	_geddy->release();
	SAFE_DELETE(_geddy);

	_titleScene->release();
	SAFE_DELETE(_titleScene);

	_progressBar->release();
	SAFE_DELETE(_progressBar);

	_shadow->release();
	SAFE_DELETE(_shadow);
}

void stage::update(void)
{
	_geddy->update();
	PLAYERMANAGER->update();
	CAMMANAGER->update();
	EFFECTMANAGER->update();
	_shadow->update();
	
	// ����� ��� ���
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_debugMode = !_debugMode;
	}

	// ���� �ܾƿ� �׽�Ʈ
	if (KEYMANAGER->isStayKeyDown(VK_F5))
	{
		if (CAMMANAGER->getZoom() > 1.01f) CAMMANAGER->setZoom(CAMMANAGER->getZoom() - 0.01);
	}
	if (KEYMANAGER->isStayKeyDown(VK_F6))
	{
		if (CAMMANAGER->getZoom() < 1.50f) CAMMANAGER->setZoom(CAMMANAGER->getZoom() + 0.01);
	}

	checkCollision();
	_progressBar->setGauge(PLAYERMANAGER->getHp(), 10);
	_progressBar->setX(100);
	_progressBar->setY(100);
	_progressBar->update();
	bulletColllsionArea();
	dieSceneChange();
}

void stage::render(void)
{
	if (_debugMode)
	{
		// �÷��̾� ��Ʈ �׸��� (����׿�)
		RectangleMake(getMemDC(), MoveRect(PLAYERMANAGER->getRect(), -CAMMANAGER->getX(), -CAMMANAGER->getY()));

		// ���� ��Ʈ �׸��� (����׿�)
		if (_debugMode)
		{
			for each (auto v in vWall)
			{
				RectangleMake(getMemDC(), MoveRect(v._rect, -CAMMANAGER->getX(), -CAMMANAGER->getY()));
			}
		}
	}

	_geddy->render();

	// ����Ʈ �׸���
	EFFECTMANAGER->render();

	// �׸��� �׸���
	_shadow->render();

	// ���� �ܾƿ�. �̰ź��� �Ʒ����� �����ϴ� �͵��� Ȯ����ҿ� ������ �ȹ���.
	float pPosXInView = (PLAYERMANAGER->getX() - CAMMANAGER->getX()) / WINSIZEX;
	float pPosYInView = (PLAYERMANAGER->getY() - CAMMANAGER->getY()) / WINSIZEY;

	StretchBlt(getMemDC(), 0 - (CAMMANAGER->getZoom() - 1) * pPosXInView * WINSIZEX, 0 - (CAMMANAGER->getZoom() - 1) * pPosYInView * WINSIZEY, WINSIZEX * CAMMANAGER->getZoom(), WINSIZEY * CAMMANAGER->getZoom(),
		getMemDC(), 0, 0, WINSIZEX, WINSIZEY, SRCCOPY);


	// Ŀ���� ���� �ܾƿ� ������ �׸���.

	_cursorIdx++;
	if (_cursorIdx > 48)_cursorIdx = 0;

	if (PLAYERMANAGER->getGeddyOn())
	{
		_cursor->frameRender(getMemDC(), _ptMouse.x - 30, _ptMouse.y - 20, _cursorIdx / 8, 1);
	}
	else
	{
		_cursor->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y - 20, 0, 0);
	}
	_portrait->render(getMemDC(), 62, 107);
	_progressBar->render();

	if (_fadeScale < 11.0f)
	{
		float size = 200 * _fadeScale;
		float top = PLAYERMANAGER->getY() - CAMMANAGER->getY() - size / 2;
		float bottom = top + size - 5;
		float left = PLAYERMANAGER->getX() - CAMMANAGER->getX() - size / 2;
		float right = left + size - 5;

		IMAGEMANAGER->DrawPng(_graphics, _fade, left, top, size, size);

		HBRUSH b = CreateSolidBrush(RGB(0, 0, 0));
		FillRect(getMemDC(), &RectMake(0, 0, WINSIZEX, top), b); //��
		FillRect(getMemDC(), &RectMake(0, bottom, WINSIZEX, WINSIZEY), b); //�Ʒ�
		FillRect(getMemDC(), &RectMake(0, 0, left, WINSIZEY), b); // 
		FillRect(getMemDC(), &RectMake(right, 0, WINSIZEX, WINSIZEY), b);
		DeleteObject(b);
	}

#pragma region ����׿� �ؽ�Ʈ ���
	/*if (_debugMode)
	{
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
		FillRect(getMemDC(), &RectMake(0,0,180,500), brush);
		DeleteObject(brush);

		// ȭ�� �߽� ǥ�� (����׿�)
		EllipseMakeCenter(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, 6, 6);
	}

	char str[256];
	sprintf_s(str, "pWorldPos : %d, %d", PLAYERMANAGER->getX(), PLAYERMANAGER->getY());
	TextOut(getMemDC(), 0, 200, str, strlen(str));
	sprintf_s(str, "pViewPos : %.1f, %.1f", pPosXInView, pPosYInView);
	TextOut(getMemDC(), 0, 220, str, strlen(str));

	sprintf_s(str, "CamPos : %.1f, %.1f", CAMMANAGER->getX(), CAMMANAGER->getY());
	TextOut(getMemDC(), 0, 240, str, strlen(str));
	sprintf_s(str, "Zoom : %.2f", CAMMANAGER->getZoom());
	TextOut(getMemDC(), 0, 280, str, strlen(str));
	sprintf_s(str, "�浹��? : %s", PLAYERMANAGER->getIsCollision() ? "True" : "False");
	TextOut(getMemDC(), 0, 300, str, strlen(str));
	sprintf_s(str, "�Ե��浹��? : %s", _geddy->getIsCollision() ? "True" : "False");
	TextOut(getMemDC(), 0, 320, str, strlen(str));

	sprintf_s(str, "Ŀ���� : %.1f", PLAYERMANAGER->getCursorAngle());
	TextOut(getMemDC(), 0, 360, str, strlen(str));
	
	Rectangle(getMemDC(), PLAYERMANAGER->getX() - 2 - CAMMANAGER->getX(), PLAYERMANAGER->getY() - 2 - CAMMANAGER->getY(), PLAYERMANAGER->getX() + 2 - CAMMANAGER->getX(), PLAYERMANAGER->getY() + 2 - CAMMANAGER->getY());*/
#pragma endregion
}

void stage::checkCollision()
{
	PLAYERMANAGER->setIsCollision(false);

	float oldX = PLAYERMANAGER->getX();
	float oldY = PLAYERMANAGER->getY();

	_geddy->setIsCollision(false);

	RECT temp;

	for each (auto v in vWall)
	{
		// ���� ����̰� �������� ���� ��
		if (v._block == false && PLAYERMANAGER->getOtusState() == otFLY)
		{
			// ���� ���ϴ� ���̰ų� ��Ʈ ���鿡 ��¦ ��ħ
			if(PLAYERMANAGER->getMoveAmountY() <= 0 || PLAYERMANAGER->getRect().bottom > v._rect.top + 2) continue; // �浹 ����
		}

		if (IntersectRect(&temp, &v._rect, &PLAYERMANAGER->getRect()))
		{
			if ((temp.right - temp.left) > (temp.bottom - temp.top)) // �浹������ �¿�� �� ���� = ���� �Ʒ��ʿ��� �浹�Ѱ���
			{
				if (PLAYERMANAGER->getY() < (v._rect.top - v._rect.bottom) / 2 + v._rect.top)
				{
					// �Ʒ��� �浹
					PLAYERMANAGER->setY(PLAYERMANAGER->getY() + (temp.top - temp.bottom));
					PLAYERMANAGER->setIsCollision(true);
				}
				else
				{
					// �������� �ƴϰų� ���� ����̸� ���� �浹
					if (PLAYERMANAGER->getOtusState() != otFLY || v._block == true)
					{
						PLAYERMANAGER->setY(PLAYERMANAGER->getY() - (temp.top - temp.bottom));
						PLAYERMANAGER->setIsCollision(true);
					}
				}
			}
			else // �� ������ �浹�Ѱ���
			{
				if (PLAYERMANAGER->getX() < (v._rect.right - v._rect.left)/2 + v._rect.left) // �����ʰ� �浹 ( = ����Ʈ�� ����)
				{
					PLAYERMANAGER->setX(PLAYERMANAGER->getX() - (temp.right - temp.left));
					PLAYERMANAGER->setIsCollision(true);
				}
				else
				{
					PLAYERMANAGER->setX(PLAYERMANAGER->getX() + (temp.right - temp.left));
					PLAYERMANAGER->setIsCollision(true);
				}
			}
		}
	}

	//�Ե�
	for each (auto v in vWall)
	{
		if (IntersectRect(&temp, &v._rect, &_geddy->getRect()))
		{
			_geddy->setY(_geddy->getY() + (temp.top - temp.bottom));
			_geddy->setIsCollision(true);
		}
	}

	for each (auto vS in _shadow->vShadow)
	{
		RECT temp;
		bool tBool = false;

		for each (auto v in vWall)
		{
			if (IntersectRect(&temp, &v._rect, &vS->detectRect))
			{
				vS->interRect = temp;
				tBool = true;
				break;
			}
		}

		if (!tBool) vS->interRect = { 0,0,0,0 };
	}
}

void stage::playMoveLimit(string direction, int limit)
{
	if (direction == "right")
	{
		if (PLAYERMANAGER->getX() >= limit)
		{
			PLAYERMANAGER->setX(limit);
		}
	}
	else if (direction == "left")
	{
		if (PLAYERMANAGER->getX() <= limit)
		{
			PLAYERMANAGER->setX(limit);
		}
	}
	else if (direction == "up")
	{
		if (PLAYERMANAGER->getY() <= limit)
		{
			PLAYERMANAGER->setY(limit);
		}
	}
	else if (direction == "down")
	{
		if (PLAYERMANAGER->getY() >= limit)
		{
			PLAYERMANAGER->setY(limit);
		}
	}
}

void stage::bulletColllsionArea(void)
{
	RECT _rcTemp;
	for (int i = 0; i < _geddy->getBullet()->getBulletVector().size(); i++)
	{
		for (int j = 0; j < vWall.size(); j++)
		{
			if (IntersectRect(&_rcTemp, &_geddy->getBullet()->getBulletVector()[i].rc, &vWall[j]._rect))
			{
				EFFECTMANAGER->createRotateEffect(_geddy->getBullet()->getBulletVector()[i].x, _geddy->getBullet()->getBulletVector()[i].y, PLAYERMANAGER->getCursorAngle());
				_geddy->getBullet()->removeBullet(i);
				break;
			}
		}
	}
}

void stage::dieSceneChange(void)
{
	if (PLAYERMANAGER->getOtusState() == otDIE)
	{
		SCENEMANAGER->changeScene("�÷��̾���");
	}
}
