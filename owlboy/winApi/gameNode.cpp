#include "stdafx.h"
#include "gameNode.h"

//=========================
//	## �ʱ�ȭ ## init(void)
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
		//Ÿ�̸� �ʱ�ȭ
		SetTimer(_hWnd, 1, 10, NULL);
		//Ű�Ŵ��� �ʱ�ȭ
		KEYMANAGER->init();
		//������� �ʱ�ȭ
		RND->init();
		//�̹��� �Ŵ��� �ʱ�ȭ
		IMAGEMANAGER->init();
		//Ÿ�� �Ŵ��� �ʱ�ȭ
		TIMEMANAGER->init();
		//�ؽ�Ʈ������ �Ŵ��� �ʱ�ȭ
		TXTMANAGER->init();
		//INI������ �ʱ�ȭ
		INIDATA->init();
		//�� �Ŵ��� �ʱ�ȭ
		SCENEMANAGER->init();
		//���� �Ŵ��� �ʱ�ȭ
		SOUNDMANAGER->init();
		//ī�޶� �Ŵ��� �ʱ�ȭ
		CAMMANAGER->init();
		//�÷��̾� �Ŵ��� �ʱ�ȭ
		PLAYERMANAGER->init();
		PLAYERMANAGER->setHDC(getMemDC());
		//����Ʈ
		EFFECTMANAGER->init();
		EFFECTMANAGER->setHDC(getMemDC());
		//�ɼ� �Ŵ���
		OPTIONMANAGER->init();
	}

	return S_OK;
}

//==============================
//	## ���� ## release(void)
//==============================
void gameNode::release(void)
{
	if (_managerInit)
	{
		//Ÿ�̸� ����
		KillTimer(_hWnd, 1);
		//Ű�Ŵ��� �̱��� ����
		KEYMANAGER->releaseSingleton();

		//������� �̱��� ����
		RND->releaseSingleton();

		//�̹��� �Ŵ��� ����, �̱��� ����
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		//Ÿ�� �Ŵ��� ����, �̱��� ����
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		//�ؽ�Ʈ������ �Ŵ��� ����, �̱��� ����
		TXTMANAGER->release();
		TXTMANAGER->releaseSingleton();

		//INI������ ����, �̱��� ����
		INIDATA->release();
		INIDATA->releaseSingleton();

		//�� �Ŵ��� ����, �̱��� ����
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		//���� �Ŵ��� ����, �̱��� ����
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();

		PLAYERMANAGER->release();
		PLAYERMANAGER->releaseSingleton();

		//ī�޶� �Ŵ��� ����, �̱��� ����
		CAMMANAGER->release();
		CAMMANAGER->releaseSingleton();

		//����Ʈ
		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();

		//�ɼ� �Ŵ��� ����
		OPTIONMANAGER->release();
		OPTIONMANAGER->releaseSingleton();

	}
	//DC ����
	ReleaseDC(_hWnd, _hdc);
}

//=============================
//	## ������Ʈ ## update(void)
//=============================
void gameNode::update(void)
{
	//���ΰ�ħ (���� Ÿ�̸Ӹ� ���� �Ŀ��� ������� �ʴ´�)
	//������۸� ���� ������� �ʴ´� (true => false)
	//InvalidateRect(_hWnd, NULL, FALSE);
}

//============================
//	## ���� ## render(HDC hdc)
//============================
void gameNode::render(void)
{
}

//============================
//	## �������ν��� ## MainProc
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