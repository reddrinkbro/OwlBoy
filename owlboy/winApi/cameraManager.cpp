#include "stdafx.h"
#include "cameraManager.h"

HRESULT cameraManager::init(void)
{
	// ���� ���۽� ī�޶� �÷��̾ �ٶ󺸰� ��.
	_camPosX = PLAYERMANAGER->getX() - WINSIZEX / 2;
	_camPosY = PLAYERMANAGER->getY() - WINSIZEY / 2;

	return S_OK;
}

void cameraManager::release(void)
{
}

void cameraManager::update(void)
{
	// ī�޶� �÷��̾��� ��ġ�� �ε巴�� ����
	_camPosX += ((PLAYERMANAGER->getX() - _camPosX) - (WINSIZEX/2)) * CAMLERPSPEED;
	_camPosY += ((PLAYERMANAGER->getY() - _camPosY) - (WINSIZEY/2)) * CAMLERPSPEED;

	// ī�޶� �̵� ���� ���� �ȿ����� ������
	if (_camPosY > _maxY) _camPosY = _maxY;
	if (_camPosY < _minY) _camPosY = _minY;
	if (_camPosX > _maxX) _camPosX = _maxX;
	if (_camPosX < _minX) _camPosX = _minX;
}
