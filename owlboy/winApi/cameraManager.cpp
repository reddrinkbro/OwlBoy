#include "stdafx.h"
#include "cameraManager.h"

HRESULT cameraManager::init(void)
{
	// 최초 시작시 카메라가 플레이어를 바라보게 함.
	_camPosX = PLAYERMANAGER->getX() - WINSIZEX / 2;
	_camPosY = PLAYERMANAGER->getY() - WINSIZEY / 2;

	return S_OK;
}

void cameraManager::release(void)
{
}

void cameraManager::update(void)
{
	// 카메라가 플레이어의 위치를 부드럽게 따라감
	_camPosX += ((PLAYERMANAGER->getX() - _camPosX) - (WINSIZEX/2)) * CAMLERPSPEED;
	_camPosY += ((PLAYERMANAGER->getY() - _camPosY) - (WINSIZEY/2)) * CAMLERPSPEED;

	// 카메라 이동 제한 범위 안에서만 움직임
	if (_camPosY > _maxY) _camPosY = _maxY;
	if (_camPosY < _minY) _camPosY = _minY;
	if (_camPosX > _maxX) _camPosX = _maxX;
	if (_camPosX < _minX) _camPosX = _minX;
}
