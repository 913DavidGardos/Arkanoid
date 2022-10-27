#include "GameFrame.h"

GameFrame::GameFrame(int width, int height) : width(width), height(height) {}

void GameFrame::InitGameFrame()
{
	this->gameFrames["leftwall"] = std::shared_ptr<Hitbox>(new Hitbox(0, 0, 20, height, HitboxType::LEFTWALL));
	this->gameFrames["ceilling"] = std::shared_ptr<Hitbox>(new Hitbox(20, 0, width - 40, 20, HitboxType::CEILLING));
	this->gameFrames["rightwall"] = std::shared_ptr<Hitbox>(new Hitbox(width - 20, 0, 20, height, HitboxType::RIGHTWALL));
	this->gameFrames["floor"] = std::shared_ptr<Hitbox>(new Hitbox(20, height - 20, width - 40, 20, HitboxType::FLOOR));
}

std::shared_ptr<Hitbox> GameFrame::getLeftWall()
{
	return this->gameFrames["leftwall"];
}
std::shared_ptr<Hitbox> GameFrame::getRightWall()
{
	return this->gameFrames["rightwall"];
}
std::shared_ptr<Hitbox> GameFrame::getCeilling()
{
	return this->gameFrames["ceilling"];
}
std::shared_ptr<Hitbox> GameFrame::getFloor()
{
	return this->gameFrames["floor"];
}
