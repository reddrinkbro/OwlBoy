#pragma once
#include "singletonbase.h"

#define CAMLERPSPEED 0.04f // 카메라 보간 속도. 숫자가 낮을수록 캐릭터를 천천히 따라감

class cameraManager : public singletonBase <cameraManager>
{
private:
	// 카메라 위치
	float _camPosX;
	float _camPosY;

	// 카메라가 이동할 수 있는 최대 범위
	float _minX, _maxX, _minY, _maxY;

	// 카메라 줌
	float _zoom;

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	float getZoom() { return _zoom; }
	void setZoom(float f) { _zoom = f; }

	float getX() { return _camPosX; }
	float getY() { return _camPosY; }

	void setCamLimit(float minX, float maxX, float minY, float maxY) { _minX = minX; _maxX = maxX; _minY = minY; _maxY = maxY; };

	cameraManager() {}
	~cameraManager() {}
};

