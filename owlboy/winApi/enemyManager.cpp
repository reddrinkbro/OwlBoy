#include "stdafx.h"
#include "enemyManager.h"
HRESULT enemyManager::init(bool isMinion)
{
	IMAGEMANAGER->addFrameImage("torque", "image/torque.bmp", 1724, 1036, 9, 8, true, RGB(255, 0, 255));
	_isMinion = isMinion;
	if (_isMinion)
	{
		setMinion(); // 현재 init을 안해서 몬스터가 안나옴
	}
	else
	{
		setBoss();
	}

	_otusDamage = false;
	return S_OK;
}

void enemyManager::release(void)
{
	for (_viSpikeBall = _vSpikeBall.begin(); _viSpikeBall != _vSpikeBall.end(); ++_viSpikeBall)
	{
		(*_viSpikeBall)->release();
		SAFE_DELETE(*_viSpikeBall);
	}
	for (_viGawk = _vGawk.begin(); _viGawk != _vGawk.end(); ++_viGawk)
	{
		(*_viGawk)->release();
		SAFE_DELETE(*_viGawk);
	}
	for (_viTorque = _vTorque.begin(); _viTorque != _vTorque.end(); ++_viTorque)
	{
		(*_viTorque)->release();
		SAFE_DELETE(*_viTorque);
	}
	if (!_isMinion)
	{
		_boss->release();
		SAFE_DELETE(_boss);
	}
}

void enemyManager::update(bool isMove)
{
	for (_viSpikeBall = _vSpikeBall.begin(); _viSpikeBall != _vSpikeBall.end(); ++_viSpikeBall)
	{
		(*_viSpikeBall)->update();
	}
	if (isMove)
	{
		for (_viGawk = _vGawk.begin(); _viGawk != _vGawk.end(); ++_viGawk)
		{
			(*_viGawk)->update();
		}
	}
	for (_viTorque = _vTorque.begin(); _viTorque != _vTorque.end(); ++_viTorque)
	{
		(*_viTorque)->update();
	}
	if (!_isMinion)
	{
		_boss->update();
	}
	playHit();
}

void enemyManager::render(void)
{
	int count = 0;
	for (_viSpikeBall = _vSpikeBall.begin(); _viSpikeBall != _vSpikeBall.end(); ++_viSpikeBall)
	{
		(*_viSpikeBall)->render();
	}
	for (_viGawk = _vGawk.begin(); _viGawk != _vGawk.end(); ++_viGawk)
	{
		(*_viGawk)->render();
	}
	for (_viTorque = _vTorque.begin(); _viTorque != _vTorque.end(); ++_viTorque, count++)
	{
		(*_viTorque)->render();
	}
	if(!_isMinion)
	{
		_boss->render();
	}
}

void enemyManager::setMinion(void)
{
	for (int i = 0; i < 10; i++)
	{
		_gawk = new minionGawk;
		_gawk->init(3000 - RND->getFromIntTo(100,200) * i, RND->getFromIntTo(-300, WINSIZEY/2));
		_vGawk.push_back(_gawk);
	}
	for (int i = 0; i < 6; i++)
	{
		_spikeBall = new minionSpikeBall;
		_spikeBall->init(5500 - 250 * i, WINSIZEY / 2);
		_vSpikeBall.push_back(_spikeBall);
	}
	for (int i = 0; i < 3; i++)
	{
		_torque = new minionTorque;
		_torque->init("torque", 1200 - 400 * i, WINSIZEY / 2 + 180);
		_vTorque.push_back(_torque);
	}
}

void enemyManager::setBoss(void)
{
	_boss = new boss;
	_boss->init(200, WINSIZEY - 220);
}

void enemyManager::removeGawk(int arrNum)
{
	SAFE_DELETE(_vGawk[arrNum]);
	_vGawk.erase(_vGawk.begin() + arrNum);
}

void enemyManager::removeSpikeBall(int arrNum)
{
	SAFE_DELETE(_vSpikeBall[arrNum]);
	_vSpikeBall.erase(_vSpikeBall.begin() + arrNum);
}

void enemyManager::removeTorque(int arrNum)
{
	SAFE_DELETE(_vTorque[arrNum]);
	_vTorque.erase(_vTorque.begin() + arrNum);
}

void enemyManager::playHit(void)
{
	RECT _rcTemp;
	//gawk 충돌
	for (_viGawk = _vGawk.begin(); _viGawk != _vGawk.end(); ++_viGawk)
	{
		if (IntersectRect(&_rcTemp, &PLAYERMANAGER->playerHitRect(), &CollisionAreaResizing((*_viGawk)->getRect(),10,70,20,10)) && !PLAYERMANAGER->getOtusDamageOn())
		{
			//플레이어 체력 감소
			PLAYERMANAGER->setHp(PLAYERMANAGER->getHp() - 1.0f);
			PLAYERMANAGER->setOtusDamageOn(true);
		}
	}
	//spikeBall 충돌
	for (_viSpikeBall = _vSpikeBall.begin(); _viSpikeBall != _vSpikeBall.end(); ++_viSpikeBall)
	{
		if (IntersectRect(&_rcTemp, &PLAYERMANAGER->playerHitRect(), &CollisionAreaResizing((*_viSpikeBall)->getRect(), 20, 30, 20, 30)) && !PLAYERMANAGER->getOtusDamageOn())
		{
			//플레이어 체력 감소
			PLAYERMANAGER->setHp(PLAYERMANAGER->getHp() - 1.0f);
			PLAYERMANAGER->setOtusDamageOn(true);
		}
	}
	//torque 충돌
	for (_viTorque = _vTorque.begin(); _viTorque != _vTorque.end(); ++_viTorque)
	{
		if (IntersectRect(&_rcTemp, &PLAYERMANAGER->playerHitRect(), &CollisionAreaResizing((*_viTorque)->getRect(), 80, 30, 70, 0))&& !PLAYERMANAGER->getOtusDamageOn())
		{
			//플레이어 체력 감소
			PLAYERMANAGER->setHp(PLAYERMANAGER->getHp() - 1.0f);
			PLAYERMANAGER->setOtusDamageOn(true);
			
		}
	}
}
