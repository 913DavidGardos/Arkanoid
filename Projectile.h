#include "Framework.h"
#include "Hitbox.h"
#include "Vector2.h"
#include <iostream>

class Projectile : public Hitbox
{
public:
	Projectile(float x, float y, int width, int height, Sprite* sprite);

	void DrawProjectile();
	void update(float deltaT, float length);
	void setDirection(Vector2 direction);

private:
	Sprite* sprite = nullptr;
	std::unique_ptr<Vector2> direction = nullptr;
};
