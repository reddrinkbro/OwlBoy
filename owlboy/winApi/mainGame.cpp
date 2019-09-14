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
//	## init(void) ## 초기화
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//이곳에서 초기화

	SCENEMANAGER->addScene("시작화면", new titleScene);
	SCENEMANAGER->addScene("튜토리얼", new tutorial);
	SCENEMANAGER->addScene("마을", new village);
	SCENEMANAGER->addScene("던전", new dungeon);
	SCENEMANAGER->addScene("보스스테이지", new bossScene);
	SCENEMANAGER->addScene("플레이어사망", new playerDieScene);
	SCENEMANAGER->addScene("엔딩씬", new endingScene);
	SCENEMANAGER->changeScene("시작화면");

	return S_OK;
}

//=====================
//	## release(void) ##
//=====================
void mainGame::release(void)
{
	gameNode::release();
	//동적할당을 했다면 여기에서 SAFE_DELETE() 사용		
}

//=============================s
//	## update(void) ## 업데이트
//=============================
void mainGame::update(void)
{
	gameNode::update();
	//이곳에서 계산식, 키보드, 마우스등등 업데이트

	SCENEMANAGER->update();
}

//============================
//	## render(HDC hdc) ## 렌더
//============================

void mainGame::render(void)
{

	//검은색 빈 비트맵 (이것도 렌더에 그대로 둘것)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//=============================================================

	SCENEMANAGER->render();

	TIMEMANAGER->render(getMemDC());

	//=============================================================
	//백버퍼의 내용을 HDC에 그린다
	this->getBackBuffer()->render(getHDC());

}
