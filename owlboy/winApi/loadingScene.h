#pragma once
#include "gameNode.h"
#include "loading.h"

class loadingScene : public gameNode
{
private:
	loading* _loading;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//로딩이미지 함수
	void loadingImage(void);
	//로딩사운드 함수
	void loadingSound(void);

	loadingScene() {}
	~loadingScene() {}
};

