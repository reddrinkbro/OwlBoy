// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//
#pragma once

#include <SDKDDKver.h>

// ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#define WIN32_LEAN_AND_MEAN
// Windows ��� ����:
#include <Windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>

// C++ ��Ÿ�� ��� �����Դϴ�.
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <ole2.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")
using namespace Gdiplus;

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

using namespace std;

//======================================
//	## ���� ���� ��������� �̰��� �߰� ##
//======================================
#include "commonMacroFiunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "utils.h"
#include "timeManager.h"
#include "txtDataManager.h"
#include "iniData.h"
#include "sceneManager.h"
#include "soundManager.h"
#include "player.h"
#include "effect.h"
#include "cameraManager.h"
#include "optionManager.h"

using namespace MY_UTIL;

//================================
//	## �̱����� �̰��� �߰��Ѵ� ##
//================================
#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define TXTMANAGER txtDataManager::getSingleton()
#define INIDATA iniData::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define PLAYERMANAGER player::getSingleton()
#define EFFECTMANAGER effect::getSingleton()
#define CAMMANAGER cameraManager::getSingleton()
#define OPTIONMANAGER optionManager::getSingleton()

//================================
//	## ��ũ�� ## (������â �ʱ�ȭ)
//================================
#define WINNAME			(LPTSTR)(TEXT("WindowAPI"))
#define WINSTARTX		400
#define WINSTARTY		100
#define WINSIZEX		1280
#define WINSIZEY		800
#define WINSTYLE		WS_CAPTION | WS_SYSMENU

//=================================================
//	## ��ũ�� �Լ� ## (Ŭ�������� �����Ҵ�� �κ� ����)
//=================================================
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}

//================
//	## �������� ##
//================
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;
extern ULONG_PTR	gdiplusToken;

#define GRAVITY 1.0f

