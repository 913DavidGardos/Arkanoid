#pragma once
#include "Framework.h"
#include "Hitbox.h"
#include "Vector2.h"
#include<iostream>

class Ball : public Hitbox
{
public:
	Ball(float x, float y, float radius, Sprite* ballsprite);

	void DrawBall();
	Vector2 getDirectionToCursor(Vector2& v);
	Vector2 getBallVector();

	void update(float deltaT, Vector2 direction, float length);
	void setDirection(Vector2 direction);

private:
	float radius;
	Sprite* ballsprite = nullptr;
	Vector2* direction = nullptr;
};

