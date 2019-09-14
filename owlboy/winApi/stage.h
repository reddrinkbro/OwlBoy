#pragma once
#include "gameNode.h"
#include "enemyManager.h"
#include "titleScene.h"
#include "geddy.h"
#include "progressBar.h"
#include "shadow.h"

struct wall
{
	RECT _rect;
	bool _block; // true면 캐릭터가 날고 있어도 충돌함.

	wall(RECT _r, bool _b) { _rect = _r; _block = _b; }
};

class stage : public gameNode
{
protected:
	Graphics* _graphics;
	Image* _fade;
	float _fadeScale;

	bool _debugMode;
	bool _animStart;

	image* _cursor;
	int _cursorIdx;
	image* _portrait;

	image* _bg;
	enemyManager* _enemyManager;
	geddy* _geddy;
	titleScene* _titleScene;
	progressBar* _progressBar;

	shadow* _shadow;

	float _backgroundVolume;

public:
	vector<wall> vWall;
	vector<wall>::iterator viWall;

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void checkCollision(void);
	void playMoveLimit(string direction, int limit);

	float getFadeScale() { return _fadeScale; }
	void setFadeScale(float f) { _fadeScale = f; }

	void bulletColllsionArea(void);
	void dieSceneChange(void);
	stage() {}
	~stage() {}
};

