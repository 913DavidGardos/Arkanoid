#pragma once
#include "Hitbox.h"
#include "Framework.h"
#include "Vector2.h"
#include <memory>
#include <vector>
#include "Projectile.h"

class EnemyTurret : public Hitbox
{
public:
	EnemyTurret(float x, float y, int width, int height, Sprite* sprite);
	void DrawEnemyTurret();
	void DrawBullet();
	void MoveRandomly();
	void update(float deltaT, float length);
	void ShootPlayerRandomly(float playerx, float playery);
	void updateBullet(float deltaT, float length);
	std::vector<std::shared_ptr<Projectile>>& getBullets();
	void DestroyBullet(std::vector<std::shared_ptr<Projectile>>::const_iterator bullet);

private:
	Sprite* sprite = nullptr;
	std::unique_ptr<Vector2> direction = nullptr;
	std::vector<std::shared_ptr<Projectile>> bullets;
	int random_x;
	int random_y;
};

