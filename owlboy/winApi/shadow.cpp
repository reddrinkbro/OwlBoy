#include "stdafx.h"
#include "shadow.h"

HRESULT shadow::init(void)
{
	return S_OK;
}

void shadow::release(void)
{
}

void shadow::update(void)
{
	for each (auto v in vShadow)
	{
		v->finalX = *v->originX + v->offsetX;
		v->finalY = *v->originY + v->offsetY;
		v->detectRect = RectMakeCenter(v->finalX, v->finalY, 40, 100);
		v->shadowRect = RectMakeCenter(v->finalX, v->interRect.top, (v->interRect.bottom - v->interRect.top) * 0.6f, 4);
	}
}

void shadow::render(void)
{
	HBRUSH b = CreateSolidBrush(RGB(60, 60, 60));

	for each (auto v in vShadow)
	{
		FillRect(getMemDC(), &MoveRect(v->shadowRect, -CAMMANAGER->getX(), -CAMMANAGER->getY()), b);
	}

	DeleteObject(b);
}
