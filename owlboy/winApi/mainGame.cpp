#include "stdafx.h"
#include "mainGame.h"
#include "tutorial.h"
#include "village.h"
#include "bossScene.h"
#include "titleScene.h"
#include "dungeon.h"
#include "playerDieScene.h"
#include "endingScene.h"
//=========================
//	## init(void) ## �ʱ�ȭ
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//�̰����� �ʱ�ȭ

	SCENEMANAGER->addScene("����ȭ��", new titleScene);
	SCENEMANAGER->addScene("Ʃ�丮��", new tutorial);
	SCENEMANAGER->addScene("����", new village);
	SCENEMANAGER->addScene("����", new dungeon);
	SCENEMANAGER->addScene("������������", new bossScene);
	SCENEMANAGER->addScene("�÷��̾���", new playerDieScene);
	SCENEMANAGER->addScene("������", new endingScene);
	SCENEMANAGER->changeScene("����ȭ��");

	return S_OK;
}

//=====================
//	## release(void) ##
//=====================
void mainGame::release(void)
{
	gameNode::release();
	//�����Ҵ��� �ߴٸ� ���⿡�� SAFE_DELETE() ���		
}

//=============================s
//	## update(void) ## ������Ʈ
//=============================
void mainGame::update(void)
{
	gameNode::update();
	//�̰����� ����, Ű����, ���콺��� ������Ʈ

	SCENEMANAGER->update();
}

//============================
//	## render(HDC hdc) ## ����
//============================

void mainGame::render(void)
{

	//������ �� ��Ʈ�� (�̰͵� ������ �״�� �Ѱ�)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//=============================================================

	SCENEMANAGER->render();

	TIMEMANAGER->render(getMemDC());

	//=============================================================
	//������� ������ HDC�� �׸���
	this->getBackBuffer()->render(getHDC());

}
