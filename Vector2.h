#pragma once

class Vector2
{
public:
	Vector2(float x, float y);
	float getX();
	float getY();
	void setX(float);
	void setY(float);

	Vector2 Substract(const Vector2& v) const;
	Vector2 addVector(const Vector2& v) const;
	Vector2 Rotate(float angle) const;
	float length() const;
	Vector2 Scale(float scalar) const;
	Vector2 Normalize() const;

private:
	float x = 0.f;
	float y = 0.f;
};

