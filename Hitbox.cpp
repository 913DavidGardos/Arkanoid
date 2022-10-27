#include "Hitbox.h"

Hitbox::Hitbox(float x, float y, int width, int height, HitboxType frametype) :
	x(x), y(y), width(width), height(height), frametype(frametype) {}

int Hitbox::getWidth()
{
	return this->width;
}
int Hitbox::getHeight()
{
	return this->height;
}

Vector2 Hitbox::getNormal() const
{
	if (frametype == HitboxType::CEILLING)
		return Vector2(0, 1);
	if (frametype == HitboxType::LEFTWALL)
		return Vector2(1, 0);
	if (frametype == HitboxType::RIGHTWALL)
		return Vector2(-1, 0);
	if (frametype == HitboxType::BOARD)
		return Vector2(0, -1);
}

HitboxType Hitbox::getFrameType()
{
	return this->frametype;
}

void Hitbox::setCollision(bool value)
{
	this->collision = value;
}

bool Hitbox::getCollision()
{
	return this->collision;
}

void Hitbox::setX(float val)
{
	this->x = val;
}

void Hitbox::setY(float val)
{
	this->y = val;
}

float Hitbox::getX()
{
	return this->x;
}
float Hitbox::getY()
{
	return this->y;
}

