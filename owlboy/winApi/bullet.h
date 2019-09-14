#pragma once
#include "gameNode.h"
struct tagBullet
{
	image* image;
	RECT rc;
	float x, y;
	float angle;
	float speed;
	float fireX, fireY;
};
class bossBullet : public gameNode
{
private:
	typedef vector<tagBullet> Bullet;
	typedef vector<tagBullet>::iterator BulletIter;
private:
	Bullet _vBullet;
	BulletIter _viBullet;
	float _range;
	int _bulletMax;
public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float angle);
	void draw(void);
	void move(void);

	vector<tagBullet> getBulletVector(void) { return _vBullet; }

	void removeBullet(int arrNum);

	bossBullet(){}
	~bossBullet(){}
};

class geddyBullet : public gameNode
{
private:
	typedef vector<tagBullet> Bullet;
	typedef vector<tagBullet>::iterator BulletIter;
private:
	Bullet _vBullet;
	BulletIter _viBullet;
	float _range;
	int _bulletMax;

	int _frameX, _frameY, _countBullet;
public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(int x, int y, float angle);
	void draw(void);
	void move(void);

	vector<tagBullet> getBulletVector(void) { return _vBullet; }

	void removeBullet(int arrNum);

	geddyBullet() {}
	~geddyBullet() {}
};
class torqueBullet : public gameNode
{
private:
	typedef vector<tagBullet> Bullet;
	typedef vector<tagBullet>::iterator BulletIter;
private:
	Bullet _vBullet;
	BulletIter _viBullet;
	float _range;
	int _bulletMax;
public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float angle);
	void draw(void);
	void move(void);

	vector<tagBullet> getBulletVector(void) { return _vBullet; }

	void removeBullet(int arrNum);

	torqueBullet() {}
	~torqueBullet() {}
};


