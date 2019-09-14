#include "stdafx.h"
#include "effect.h"

HRESULT effect::init(void)
{
	IMAGEMANAGER->addFrameImage("explosion_big", "image/explosion_big.bmp", 0.0f, 0.0f, 6460, 170, 38, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("explosion", "image/explosion.bmp", 0.0f, 0.0f, 4840, 250, 22, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("flameExplode","image/flameExplode.bmp", 0.0f, 0.0f, 1170, 154, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("flair", "image/flairGreen_35x37_strip12.bmp", 0.0f, 0.0f, 840, 74, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossBulletEffect", "image/bossBulletEffect.bmp", 0.0f, 0.0f, 423, 47, 9, 1, true, RGB(255, 0, 255));
	return S_OK;
}

void effect::release(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		SAFE_DELETE(_viEffect->img);
	}
	_vEffect.clear();
	for (_viREffect = _vREffect.begin(); _viREffect != _vREffect.end(); ++_viREffect)
	{
		SAFE_DELETE(_viREffect->img);
	}
	_vREffect.clear();
}

void effect::update(void)
{
}

void effect::render(void)
{
	_graphics = new Graphics(_hdc);
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		_viEffect->img->frameRender(_hdc, _viEffect->rc.left - CAMMANAGER->getX(), _viEffect->rc.top - CAMMANAGER->getY());

		_viEffect->count++;
		if (_viEffect->count % 4 == 0)
		{
			_viEffect->img->setFrameX(_viEffect->img->getFrameX() + 1);
			if (_viEffect->img->getFrameX() >= _viEffect->img->getMaxFrameX())
			{
				removeEffect(0);
				break;
			}
		}
	}
	//png 이펙트
	for (_viREffect = _vREffect.begin(); _viREffect != _vREffect.end(); ++_viREffect)
	{
		Matrix mat;
		mat.RotateAt(-_viREffect->angle- 90, PointF(float(_viREffect->x  - CAMMANAGER->getX()), float(_viREffect->y - CAMMANAGER->getY())));
		_graphics->SetTransform(&mat);
		if (PLAYERMANAGER->getY() > _viREffect->y)
		{
			IMAGEMANAGER->DrawPng(_graphics, _viREffect->img, _viREffect->rc.left - CAMMANAGER->getX(), _viREffect->y - CAMMANAGER->getY() -70, _viREffect->currentX, 0, 1476, 74, 18, 1);
		}
		else
		{
			IMAGEMANAGER->DrawPng(_graphics, _viREffect->img, _viREffect->rc.left - CAMMANAGER->getX(), _viREffect->y - CAMMANAGER->getY() - 10, _viREffect->currentX, 0, 1476, 74, 18, 1);
		}
		_viREffect->count++;
		if (_viREffect->count % 4 == 0)
		{
			_viREffect->currentX++;
			if (_viREffect->currentX >= 17)
			{
				removeRotateEffect(0);
				break;
			}
		}
	}
}

// 이펙트 생성
void effect::createEffect(image* img, float x, float y)
{
	sEffect effect;
	ZeroMemory(&effect, sizeof(sEffect));

	effect.img = new image();
	// 복사생성자 만들려다가 실패해서 이렇게 함..
	effect.img->init(img->getName(), img->getWidth(), img->getHeight(), img->getMaxFrameX()+1, img->getMaxFrameY()+1, true, RGB(255, 0, 255));
	effect.x = x;
	effect.y = y;
	effect.loopCount = 4;
	effect.isEnd = false;
	effect.rc = RectMakeCenter(effect.x, effect.y, effect.img->getFrameWidth(), effect.img->getFrameHeight());
	effect.count = 0;

	_vEffect.push_back(effect);
}
//회전하는 이펙트
void effect::createRotateEffect(float x, float y, float angle)
{
	rEffect effect;
	ZeroMemory(&effect, sizeof(rEffect));
	effect.currentX = 0;
	effect.img = IMAGEMANAGER->addPngImage("image/bulletExplosion.png");
	effect.x = x;
	effect.y = y;
	effect.angle = angle;
	effect.rc = RectMakeCenter(effect.x, effect.y, 82, 74);
	_vREffect.push_back(effect);
}

// 이펙트 삭제 (렌더에서 알아서 호출 됨)
void effect::removeEffect(int arrNum)
{
	SAFE_DELETE(_vEffect[arrNum].img);

	_vEffect.erase(_vEffect.begin());
}

void effect::removeRotateEffect(int arrNum)
{
	SAFE_DELETE(_vREffect[arrNum].img);

	_vREffect.erase(_vREffect.begin());
}

void effect::repeatedRender(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		_viEffect->img->frameRender(_hdc, _viEffect->rc.left - CAMMANAGER->getX(), _viEffect->rc.top - CAMMANAGER->getY());

		_viEffect->count++;
		if (_viEffect->count % 4 == 0)
		{
			_viEffect->img->setFrameX(_viEffect->img->getFrameX() + 1);
			if (_viEffect->img->getFrameX() >= _viEffect->img->getMaxFrameX())
			{
				_viEffect->loopCount--;
				_viEffect->img->setFrameX(0);
				if (_viEffect->loopCount <= 0)
				{
					removeEffect(0);
					break;
				}
			}
		}
	}
}