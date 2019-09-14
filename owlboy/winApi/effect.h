#pragma once
#include "singletonbase.h"

struct sEffect
{
	image* img;
	RECT rc;
	float x;
	float y;
	int count;
	int loopCount;	//이펙트를 여러번 출력하기 위한 변수
	bool isEnd;
};
struct rEffect
{
	Image* img;
	RECT rc;
	float x;
	float y;
	float angle;
	int count;
	int currentX;
};
class effect : public singletonBase <effect>
{
private:
	vector<sEffect> _vEffect;
	vector<sEffect>::iterator _viEffect;
	vector<rEffect> _vREffect;
	vector<rEffect>::iterator _viREffect;
	Graphics* _graphics;
	
public:
	HDC _hdc;

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setHDC(HDC hdc) { _hdc = hdc; }

	void createEffect(image* img, float x, float y);
	void createRotateEffect(float x, float y,float angle);
	void removeEffect(int arrNum);
	void removeRotateEffect(int arrNum);

	void repeatedRender(void);

	vector<sEffect> getEffect(void) { return _vEffect; }
	effect() {}
	~effect() {}
};

