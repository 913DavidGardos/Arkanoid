#include "Ball.h"

Ball::Ball(float x, float y, float radius, Sprite* ballsprite) :
	Hitbox(x, y, radius, radius, HitboxType::BALL), radius(radius), ballsprite(ballsprite)
{
	setSpriteSize(this->ballsprite, 2.f * radius, 2.f * radius);
}

void Ball::DrawBall()
{
	drawSprite(this->ballsprite, x, y);
}

Vector2 Ball::getDirectionToCursor(Vector2& cursor)
{
	Vector2 ballvec(this->x, this->y);
	Vector2 direction = cursor.Substract(ballvec);
	Vector2 normal = direction.Normalize();

	return normal;
}

void Ball::update(float deltaT, Vector2 direction, float length)
{
	this->x = this->x + length * direction.getX() * deltaT;
	this->y = this->y + length * direction.getY() * deltaT;
}

Vector2 Ball::getBallVector()
{
	return Vector2(this->x, this->y);
}

void Ball::setDirection(Vector2 direction)
{
	this->direction = &direction;
}