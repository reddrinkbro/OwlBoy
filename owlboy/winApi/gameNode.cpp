#include "stdafx.h"
#include "gameNode.h"

//=========================
//	## 초기화 ## init(void)
//=========================
HRESULT gameNode::init(void)
{	
	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		//타이머 초기화
		SetTimer(_hWnd, 1, 10, NULL);
		//키매니져 초기화
		KEYMANAGER->init();
		//랜덤펑션 초기화
		RND->init();
		//이미지 매니져 초기화
		IMAGEMANAGER->init();
		//타임 매니져 초기화
		TIMEMANAGER->init();
		//텍스트데이터 매니져 초기화
		TXTMANAGER->init();
		//INI데이터 초기화
		INIDATA->init();
		//씬 매니져 초기화
		SCENEMANAGER->init();
		//사운드 매니져 초기화
		SOUNDMANAGER->init();
		//카메라 매니져 초기화
		CAMMANAGER->init();
		//플레이어 매니저 초기화
		PLAYERMANAGER->init();
		PLAYERMANAGER->setHDC(getMemDC());
		//이펙트
		EFFECTMANAGER->init();
		EFFECTMANAGER->setHDC(getMemDC());
		//옵션 매니저
		OPTIONMANAGER->init();
	}

	return S_OK;
}

//==============================
//	## 해제 ## release(void)
//==============================
void gameNode::release(void)
{
	if (_managerInit)
	{
		//타이머 해제
		KillTimer(_hWnd, 1);
		//키매니져 싱글톤 해제
		KEYMANAGER->releaseSingleton();

		//랜덤펑션 싱글톤 해제
		RND->releaseSingleton();

		//이미지 매니져 해제, 싱글톤 해제
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		//타임 매니져 해제, 싱글톤 해제
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		//텍스트데이터 매니져 해제, 싱글톤 해제
		TXTMANAGER->release();
		TXTMANAGER->releaseSingleton();

		//INI데이터 해제, 싱글톤 해제
		INIDATA->release();
		INIDATA->releaseSingleton();

		//씬 매니져 해제, 싱글톤 해제
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		//사운드 매니져 해제, 싱글톤 해제
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();

		PLAYERMANAGER->release();
		PLAYERMANAGER->releaseSingleton();

		//카메라 매니져 해제, 싱글톤 해제
		CAMMANAGER->release();
		CAMMANAGER->releaseSingleton();

		//이펙트
		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();

		//옵션 매니저 해제
		OPTIONMANAGER->release();
		OPTIONMANAGER->releaseSingleton();

	}
	//DC 해제
	ReleaseDC(_hWnd, _hdc);
}

//=============================
//	## 업데이트 ## update(void)
//=============================
void gameNode::update(void)
{
	//새로고침 (고성능 타이머를 만든 후에는 사용하지 않는다)
	//더블버퍼링 이후 사용하지 않는다 (true => false)
	//InvalidateRect(_hWnd, NULL, FALSE);
}

//============================
//	## 렌더 ## render(HDC hdc)
//============================
void gameNode::render(void)
{
}

//============================
//	## 메인프로시져 ## MainProc
//============================
LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (iMessage)
	{
	case WM_TIMER:
		this->update();
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		this->render();
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}