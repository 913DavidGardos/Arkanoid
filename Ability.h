#pragma once
#include"Hitbox.h"
#include<memory>

class Ability
{
public:
	virtual void IncreaseSize(std::shared_ptr<Hitbox> hitbox) = 0;
	virtual void DecreaseSize(std::shared_ptr<Hitbox> hitbox) = 0;
};