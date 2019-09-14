 #pragma once
#include "gameNode.h"
#include "spikeBall.h"
#include "gawk.h"
#include "torque.h"
#include "boss.h"
#include "minion.h"

class enemyManager : public gameNode
{
private:
	typedef vector<spikeBall*> vSpikeBall;				//Spikeball ����
	typedef vector<spikeBall*>::iterator viSpikeBall;	//Spikeball ���� ���ͷ�����
	typedef vector<gawk*> vGawk;						//Gawk ����
	typedef vector<gawk*>::iterator viGawk;				//Gawk ���� ���ͷ�����
	typedef vector<torque*> vTorque;				//torque ����
	typedef vector<torque*>::iterator viTorque;	//torque ���� ���ͷ�����
private:
	//����
	vSpikeBall _vSpikeBall;
	viSpikeBall _viSpikeBall;
	vGawk _vGawk;
	viGawk _viGawk;
	vTorque _vTorque;
	viTorque _viTorque;
private:
	gawk* _gawk;
	spikeBall* _spikeBall;
	torque* _torque;
	boss* _boss;
	bool _isMinion;
	bool _otusDamage;
public:
	HRESULT init(bool isMinion);
	void release(void);
	void update(bool isMove);
	void render(void);
	void setMinion(void);
	void setBoss(void);
	void removeGawk(int arrNum);
	void removeSpikeBall(int arrNum);
	void removeTorque(int arrNum);
	
	//spikeball ��������
	vector<spikeBall*> getspikeBall(void) { return _vSpikeBall; }
	vector<gawk*> getGawk(void) { return _vGawk; }
	vector<torque*> getTorque(void) { return _vTorque; }
	boss* getBoss(void) { return _boss; }
	void playHit(void);
	enemyManager() {}
	~enemyManager() {}
};

