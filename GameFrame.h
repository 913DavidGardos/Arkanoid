#pragma once
#include "Hitbox.h"
#include<map>
#include<string>
#include<memory>

class GameFrame
{
public:
	GameFrame(int width, int height);
	void InitGameFrame();
	std::shared_ptr<Hitbox> getLeftWall();
	std::shared_ptr<Hitbox> getRightWall();
	std::shared_ptr<Hitbox> getCeilling();
	std::shared_ptr<Hitbox> getFloor();

	std::map <std::string, std::shared_ptr<Hitbox>> gameFrames;

private:
	int width;
	int height;
};

