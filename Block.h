#pragma once
#include "Hitbox.h"
#include "HitboxType.h"
#include "BlockType.h"
#include "Framework.h"
#include <vector>
#include <memory>

class Block : public Hitbox
{
public:
	Block(float x, float y, int width, int height, Sprite* sprite, BlockType blocktype);
	Sprite* getSprite() const;

	void setDestroyValue(bool value);
	bool getDestroyValue();
	BlockType getBlockType();

private:
	Sprite* sprite = nullptr;
	bool destroy = false;
	BlockType blocktype;
};

