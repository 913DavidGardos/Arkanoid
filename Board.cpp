#include "Board.h"
#include <iostream>
#include <cstdlib>

Board::Board(float x, float y, int width, int height, Sprite* sprite) : 
	Hitbox(x, y, width, height, HitboxType::BOARD), sprite(sprite), maxsize(3*width), minsize(width*0.5)
{
	setSpriteSize(this->sprite, width, height);
}

void Board::DrawBoard()
{
	drawSprite(this->sprite, this->x, this->y);
}

void Board::MoveRight()
{
	if (this->collision)
	{
		// 800 must be changed with screen width...
		if (this->x > float(this->getWidth() / 2))
			this->x = float(800-21-this->getWidth());
	}
	setCollision(false);
	this->x += 5;
}

void Board::MoveLeft()
{
	if (this->collision)
	{
		if (this->x < this->getWidth() / 2)
			this->x = 21;
	}
	setCollision(false);
	this->x -= 5;
}

void Board::IncreaseSize()
{
	if(this->width < maxsize)
	{
		this->width = this->width + this->width * 0.4;
		setSpriteSize(this->sprite, this->width, this->height);
	}
}

void Board::DecreaseSize()
{
	if (this->width > minsize)
	{
		this->width = this->width - this->width * 0.4;
		setSpriteSize(this->sprite, this->width, this->height);
	}

}

void Board::DefaultSize()
{
	this->width = 100;
	this->height = 20;
	setSpriteSize(this->sprite, this->width, this->height);
}