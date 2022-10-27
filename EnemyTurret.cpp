#include "EnemyTurret.h"
#include <ctime>
#include<iostream>


EnemyTurret::EnemyTurret(float x, float y, int width, int height, Sprite* sprite):
	Hitbox(x, y, width, height, HitboxType::TURRET), sprite(sprite)
{
	setSpriteSize(this->sprite, width, height);
	srand(time(0));
}

void EnemyTurret::DrawEnemyTurret()
{
	drawSprite(this->sprite, this->x, this->y);
}

void EnemyTurret::MoveRandomly()
{
	this->random_x = rand() % 800;
	this->random_y = rand() % 300;

	std::cout << "rand pos (" << this->random_x <<", " << this->random_y << ")" << std::endl;

	Vector2 destination(this->random_x, this->random_y);
	Vector2 enemyturret(this->x, this->y);
	this->direction = std::make_unique<Vector2>(destination.Substract(enemyturret).Normalize());
}

void EnemyTurret::update(float deltaT, float length)
{
	if (this->direction)
	{
		this->x += length * this->direction->getX() * deltaT;
		this->y += length * this->direction->getY() * deltaT;
	}
}

void EnemyTurret::ShootPlayerRandomly(float playerx, float playery)
{
	float bulletx = this->x + this->width / 2;
	float bullety = this->y + this->height;
	int bulletwidth = 10;
	int bulletheight = 20;
	auto createdbullet = std::make_shared<Projectile>(bulletx, bullety, bulletwidth, bulletheight, createSprite("../data/61-Breakout-Tiles.png"));

	// set direction to player
	Vector2 player(playerx, playery);
	Vector2 enemy(this->x, this->y);
	createdbullet->setDirection(player.Substract(enemy).Normalize());

	this->bullets.push_back(createdbullet);
}

void EnemyTurret::DrawBullet()
{
	for(auto bullet : this->bullets)
		bullet->DrawProjectile();
}

void EnemyTurret::updateBullet(float deltaT, float length)
{
	for (auto bullet : this->bullets)
		bullet->update(deltaT, length);
}

std::vector<std::shared_ptr<Projectile>>& EnemyTurret::getBullets()
{
	return this->bullets;
}

void EnemyTurret::DestroyBullet(std::vector<std::shared_ptr<Projectile>>::const_iterator bullet)
{
	this->bullets.erase(bullet);
}