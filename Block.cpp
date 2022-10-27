#include "Block.h"

Block::Block(float x, float y, int width, int height, Sprite* sprite, BlockType blocktype) :
	Hitbox(x, y, width, height, HitboxType::BLOCK), sprite(sprite), blocktype(blocktype) {}


BlockType Block::getBlockType()
{
	return this->blocktype;
}

Sprite* Block::getSprite() const
{
	return this->sprite;
}

void Block::setDestroyValue(bool value)
{
	this->destroy = value;
}

bool Block::getDestroyValue()
{
	return this->destroy;
}
