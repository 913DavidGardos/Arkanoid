#include "Vector2.h"	
#include <math.h>

Vector2::Vector2(float x, float y) : x(x), y(y) {}

float Vector2::getX()
{
	return x;
}

float Vector2::getY()
{
	return y;
}

void Vector2::setX(float x)
{
	x = x;
}
void Vector2::setY(float y)
{
	y = y;
}

Vector2 Vector2::Substract(const Vector2& vec) const
{
	Vector2 result_vec(x - vec.x, y - vec.y);
	return result_vec;
}

Vector2 Vector2::addVector(const Vector2& vec) const
{
	Vector2 result_vec(x + vec.x, y + vec.y);
	return result_vec;
}

float Vector2::length() const
{
	return sqrt(x * x + y * y);
}

Vector2 Vector2::Scale(float scalar) const
{
	Vector2 result_(x * scalar, y * scalar);
	return result_;
}

Vector2 Vector2::Normalize() const
{
	float normx = this->x / this->length();
	float normy = this->y / this->length();

	Vector2 normalized(normx, normy);
	return normalized;
}

Vector2 Vector2::Rotate(float angle) const
{
	float xangled = this->x * cos(angle) - this->y * sin(angle);
	float yangled = this->x * sin(angle) - this->y * cos(angle);

	return Vector2(xangled, yangled);
}