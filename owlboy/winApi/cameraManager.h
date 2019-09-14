#pragma once
#include "singletonbase.h"

#define CAMLERPSPEED 0.04f // ī�޶� ���� �ӵ�. ���ڰ� �������� ĳ���͸� õõ�� ����

class cameraManager : public singletonBase <cameraManager>
{
private:
	// ī�޶� ��ġ
	float _camPosX;
	float _camPosY;

	// ī�޶� �̵��� �� �ִ� �ִ� ����
	float _minX, _maxX, _minY, _maxY;

	// ī�޶� ��
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

