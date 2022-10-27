#pragma once
#include "Framework.h"
#include "Hitbox.h"
#include "Vector2.h"

class Board : public Hitbox
{
public:
	Board(float x, float y, int width, int height, Sprite* sprite);
	void DrawBoard();
	void MoveRight();
	void MoveLeft();
	void IncreaseSize();
	void DecreaseSize();
	void DefaultSize();

private:
	Sprite* sprite = nullptr;

	int maxsize;
	int minsize;
};

