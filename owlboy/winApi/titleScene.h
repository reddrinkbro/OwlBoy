#pragma once
#include "gameNode.h"
#include "optionWindow.h"
#define FRAMECOUNT 1.0f

struct tagFrameImage
{
	Image* _image;
	float _count;
	int _currentX;
};
class titleScene : public gameNode
{
private:
	Graphics* _graphics;
	tagFrameImage _titleOtus;
	tagFrameImage _grass;
	optionWindow* _optionWindow;
	Image* _logo;
	image* _image;
	image* _centerCloud;
	image* _continueButton;
	image* _optionButton;
	image* _exitButton;
	RECT _logoRc;
	RECT _continueRc;
	RECT _optionRc;
	RECT _exitRc;
	float _x, _y;
	bool _isPlaySound;
	bool _isShowOption;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void playGame(void);
	void openOption(void);
	void closeOption(void);
	void exitGame(void);
	void volumeApplying(void);
	optionWindow* getOtion(void) { return _optionWindow; }

	titleScene(){}
	~titleScene(){}
};

