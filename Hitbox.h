#pragma once
#include "Vector2.h"
#include "HitboxType.h"

class Hitbox
{
public:
	Hitbox(float x, float y, int width, int height, HitboxType frametype);

	float getX();
	float getY();
	int getWidth();
	int getHeight();
	void setX(float);
	void setY(float);
	void setCollision(bool value);
	bool getCollision();
	Vector2 virtual getNormal() const;
	HitboxType getFrameType();

protected:
	float x;
	float y;
	int width;
	int height;
	bool collision = false;
	HitboxType frametype;
};

