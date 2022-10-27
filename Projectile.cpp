#include "Projectile.h"

Projectile::Projectile(float x, float y, int width, int height, Sprite* sprite):
	Hitbox(x, y, width, height, HitboxType::PROJECTILE), sprite(sprite)
{
	setSpriteSize(sprite, width, height);
}

void Projectile::DrawProjectile()
{
	drawSprite(this->sprite, this->x, this->y);
}

void Projectile::update(float deltaT, float length)
{
	if (this->direction)
	{
		this->x = this->x + length * direction->getX() * deltaT;
		this->y = this->y + length * direction->getY() * deltaT;
	}
}

void Projectile::setDirection(Vector2 direction)
{
	this->direction = std::make_unique<Vector2>(direction);
}

