#pragma once
#include "stage.h"


struct cloud
{
	image* image;
	RECT rc;
	float x, y;
	float speed;
};

class village :	public stage
{
private:
	image * _imageSky;
	image* _imageGrass1;
	image* _imageGrass2;
	image* _imageGrass3;
	image* _imageGrass4;
	image* _imageBush1;
	image* _imageBush2;
	image* _imageTree1;
	
	RECT _nextScene;
	cloud _cloud[9];
	bool _isPlaySound;

	int _count;

	float _rndTimeCount;   
	float _worldTimeCount; 
	int _bushFrameX;
	int _grassFrameX;	
	int _treeFrameX;
	
	
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void nextScene(void);
	village() {}
	~village() {}
};

