#include <iostream>
#include <map>
#include <iterator>
#include <ctime>
#include "Framework.h"
#include "Board.h"
#include "Hitbox.h"
#include "Vector2.h"
#include "GameFrame.h"
#include "Ball.h"
#include "Block.h"
#include "EnemyTurret.h"
#include "AbilityKind.h"
#include <vector>
#include <memory>

/* Test Framework realization */
class MyFramework : public Framework 
{
private:
	std::vector<std::shared_ptr<Hitbox>> boardAndGameFrame;
	std::vector<std::shared_ptr<Block>> Blocks;

	std::shared_ptr<Board> board = nullptr;
	std::shared_ptr<GameFrame> gameframe = nullptr;
	std::shared_ptr<Ball> ball = nullptr;
	std::shared_ptr<EnemyTurret> enemyturret = nullptr;

	int screenheight = 600;
	int screenwidth = 800;
	int countNormalBlocks = 0;
	uint32_t startTime = 0;
	int stopWatch = 0;

	float mouse_x = 0.0;
	float mouse_y = 0.0;
	float flPrevioustime = 0;
	float flCurrenttime = float(getTickCount());

	bool mouseClick = false;
	bool RIGHTpressed = false;
	bool LEFTpressed = false;
	bool fired = false;
	bool timePassed = false;

	Vector2 balldirection = Vector2(0 ,0);

public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = 800;
		height = 600;
		fullscreen = false;
	}

	virtual bool Init() {
		std::cout << "Init was called "<< std::endl;
		
		srand(time(0));

		InitBoard();
		InitGameFrame();
		InitBall();
		InitBlocks();
		InitBoardAndGameFrame();
		InitEnemyTurret();

		return true;
	}

	virtual void Close() {
		std::cout << "Close was called " << std::endl;
	}

	virtual bool Tick() {

		drawTestBackground();
		HandleBoardMovement();
		HandleBallCollisions();

		float dt = computeDeltaTime();
		if(this->mouseClick)
			this->ball->update(dt, balldirection, 20.0f);

		if (getTickCount() % 100 == 0)
			this->enemyturret->MoveRandomly();

		if (getTickCount() % (rand() % 10000 + 1) == 0)
		{
			this->enemyturret->ShootPlayerRandomly(this->board->getX(), this->board->getY());
			this->fired = true;
		}

		if (this->startTime + 20000 < getTickCount())
		{
			this->board->DefaultSize();
			this->startTime = 0;
		}

		if (this->fired)
		{
			this->enemyturret->DrawBullet();
			this->enemyturret->updateBullet(dt ,7.0f);
			HandleBulletOutOfGameFrame();

			if (!BoardCollisionWithBullets())
				GameOver();
		}

		this->enemyturret->update(dt, 2.0f);
		this->enemyturret->DrawEnemyTurret();
		this->ball->DrawBall();
		this->board->DrawBoard();
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
		if (!this->mouseClick)
		{
			this->mouse_x = float(x);
			this->mouse_y = float(y);
		}
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		this->mouseClick = true;
		std::cout << "mouse x = " << mouse_x << ", y = " << mouse_y << std::endl;
	}

	virtual void onKeyPressed(FRKey k) 
	{
		if (k == FRKey::RIGHT)
		{
			this->board->MoveRight();
			this->RIGHTpressed = true;
			this->LEFTpressed = false;
		}
		if (k == FRKey::LEFT)
		{
			this->board->MoveLeft();
			this->LEFTpressed = true;
			this->RIGHTpressed = false;
		}
		if (k == FRKey::UP)
		{
			this->startTime = getTickCount();
			this->board->IncreaseSize();
		}
		if (k == FRKey::DOWN)
		{
			this->startTime = getTickCount();
			this->board->DecreaseSize();
		}
	}

	virtual void onKeyReleased(FRKey k)
	{
		if (k == FRKey::RIGHT)
		{
			this->RIGHTpressed = false;
		}
		if (k == FRKey::LEFT)
		{
			this->LEFTpressed = false;
		}
	}

	virtual const char* GetTitle() override
	{
		return "Arcanoid";
	}


	bool BoardCollisionWithGameFrame()
	{
		for (auto const& element : this->gameframe->gameFrames)
		{
			//AABB
			if (this->board->getX() < element.second->getX() + element.second->getWidth() &&
				this->board->getX() + this->board->getWidth() > element.second->getX() &&
				this->board->getY() < element.second->getY() + element.second->getHeight() &&
				this->board->getY() + this->board->getHeight() > element.second->getY())
			{
				return false;
			}
		}
		return true;
	}

	bool BallCollisionWithGameAndBoard()
	{
		for (auto const& element : boardAndGameFrame)
		{
			if (this->ball->getX() < element->getX() + element->getWidth() &&
				this->ball->getX() + this->ball->getWidth() > element->getX() &&
				this->ball->getY() < element->getY() + element->getHeight() &&
				this->ball->getY() + this->ball->getHeight() > element->getY())
			{
				if (element->getFrameType() == HitboxType::FLOOR)
					GameOver();

				BallCollisionResolution(element);
				return false;
			}

		}
		return true;
	}

	bool BallCollisionBlock()
	{
		for (auto & element : Blocks)
		{
			if (element)
				if (this->ball->getX() < element->getX() + element->getWidth() &&
					this->ball->getX() + this->ball->getWidth() > element->getX() &&
					this->ball->getY() < element->getY() + element->getHeight() &&
					this->ball->getY() + this->ball->getHeight() > element->getY())
				{
					BallCollisionResolution2(element);

					if(element->getBlockType() == BlockType::NORMALBLOCK)
					{
						element->setDestroyValue(true);
						this->countNormalBlocks--;
					}

					if(element->getBlockType() == BlockType::REDBLOCK && this->countNormalBlocks <= 0)
						element->setDestroyValue(true);

					return false;
				}
		}
		return true;
	}

	bool BoardCollisionWithBullets()
	{
		for (auto const& bullet : this->enemyturret->getBullets())
		{
			if (this->board->getX() < bullet->getX() + bullet->getWidth() &&
				this->board->getX() + this->board->getWidth() > bullet->getX() &&
				this->board->getY() < bullet->getY() + bullet->getHeight() &&
				this->board->getY() + this->board->getHeight() > bullet->getY())
			{
				return false;
			}
		}
		return true;
	}

	void BallCollisionResolution(const std::shared_ptr<Hitbox> element)
	{
		Vector2 planeNormal = element->getNormal();
		balldirection = balldirection.addVector(planeNormal);
		balldirection = balldirection.Normalize();
	}

	void BallCollisionResolution2(const std::shared_ptr<Hitbox> element)
	{
		float ballX = this->ball.get()->getX();
		float ballY = this->ball.get()->getY();
		float ballW = this->ball.get()->getWidth();
		float ballH = this->ball.get()->getHeight();

		float blockX = element.get()->getX();
		float blockY = element.get()->getY();
		float blockW = element.get()->getWidth();
		float blockH = element.get()->getWidth();

		if (balldirection.getX() > 0 && balldirection.getY() > 0) // x increasing y increasing
		{
			float overlapX = ballX + ballW - blockX;
			float overlapY = ballY + ballH - blockY;

			if (overlapX > overlapY) // top
				balldirection = balldirection.addVector(Vector2(0, -1)).Normalize();
			if (overlapX < overlapY) // left
				balldirection = balldirection.addVector(Vector2(-1, 0)).Normalize();
		}
		if (balldirection.getX() > 0 && balldirection.getY() < 0) // x increasing y decreasing
		{
			float overlapX = ballX + ballW - blockX;
			float overlapY = blockY - ballY;

			if (overlapX > overlapY) // bottom
				balldirection = balldirection.addVector(Vector2(0, 1)).Normalize();
			if (overlapX < overlapY) // left
				balldirection = balldirection.addVector(Vector2(-1, 0)).Normalize();
		}
		if (balldirection.getX() < 0 && balldirection.getY() > 0) // x decreasing  y increasing
		{
			float overlapX = blockX - ballX;
			float overlapY = blockY - ballY - ballH;
			if (overlapX > overlapY) // top
				balldirection = balldirection.addVector(Vector2(0, -1)).Normalize();
			if (overlapX < overlapY) // right
				balldirection = balldirection.addVector(Vector2(1, 0)).Normalize();
		}
		if (balldirection.getX() < 0 && balldirection.getY() < 0) // x decreasing  y decreasing
		{
			float overlapX = blockX - ballX;
			float overlapY = blockY - ballY;
			if (overlapX > overlapY) // bottomm
				balldirection = balldirection.addVector(Vector2(0, 1)).Normalize();
			if (overlapX < overlapY) // right
				balldirection = balldirection.addVector(Vector2(1, 0)).Normalize();
		}
	}

	void computeBallDirection()
	{
		if (!this->mouseClick) // when first click occours set the direction
		{
			Vector2 cursor(this->mouse_x, this->mouse_y);
			Vector2 ballvec = this->ball->getBallVector();
			Vector2 direction = this->ball->getDirectionToCursor(cursor);
			balldirection = direction;
		}
	}

	float computeDeltaTime()
	{
		this->flPrevioustime = this->flCurrenttime;
		this->flCurrenttime = float(getTickCount());
		float deltaT = this->flCurrenttime - this->flPrevioustime;
		if (deltaT > 0.15f)
			deltaT = 0.15f;

		return deltaT;
	}

	void HandleBoardMovement()
	{
		if (this->RIGHTpressed)
			this->board->MoveRight();
		if (this->LEFTpressed)
			this->board->MoveLeft();

		if (!BoardCollisionWithGameFrame())
			this->board->setCollision(true);
	}

	void HandleBallCollisions()
	{
		BallCollisionWithGameAndBoard();
		computeBallDirection();
		BallCollisionBlock();

		for (auto it = Blocks.begin(); it != Blocks.end(); )
		{
			if (*it)
				if (!it->get()->getDestroyValue())
				{
					drawSprite(it->get()->getSprite(), it->get()->getX(), it->get()->getY());
					it++;
				}
				else
				{
					it = this->Blocks.erase(it);
				}
		}
	}

	void InitBoard()
	{
		Sprite* boardsprite = createSprite("../data/50-Breakout-Tiles.png");
		int board_width = 100;
		int board_height = 20;

		float board_x = screenwidth / 2 - board_width / 2;
		float board_y = screenheight - 2 * board_height;

		this->board = std::shared_ptr<Board>(new Board(board_x, board_y, board_width, board_height, boardsprite));
	}

	void InitBall()
	{
		Sprite* ballsprite = createSprite("../data/63-Breakout-Tiles.png");
		int radius = 10;

		float ball_x = screenwidth / 2 - radius;
		float ball_y = screenheight - 6 * radius;

		this->ball = std::shared_ptr<Ball>(new Ball(ball_x, ball_y, radius, ballsprite));
	}

	void InitGameFrame()
	{
		this->gameframe = std::shared_ptr<GameFrame>(new GameFrame(screenwidth, screenheight));
		this->gameframe->InitGameFrame();
	}

	void InitBlocks()
	{
		float matrix_x = 100.f;
		float matrix_y = 25.f;

		int columns = 9;
		int rows = 1;

		int block_width = 60;
		int block_height = 20;

		int padding = 10;

		int vectorlength = rows * columns;

		

		for (int i = 0; i < vectorlength; i++)
		{
			Sprite* blc2 = createSprite("../data/01-Breakout-Tiles.png");
			BlockType bt = BlockType::NORMALBLOCK;
			this->countNormalBlocks++;

			int choice = rand() % 4 - 1;
			
			if (choice == 0)
			{
				blc2 = createSprite("../data/07-Breakout-Tiles.png");
				bt = BlockType::REDBLOCK;
				this->countNormalBlocks--;
			}

			setSpriteSize(blc2, block_width, block_height);
			float x = matrix_x + i * (padding + block_width);
			float y = matrix_y;
			std::shared_ptr<Block> ptr = std::make_shared<Block>(x, y, block_width, block_height, blc2, bt);
			this->Blocks.push_back(ptr);

			if ((i + 1) % columns == 0 && i > 0)
			{
				matrix_y += block_height + padding;
				matrix_x = matrix_x - (i % columns + 1) * (padding + block_width);
			}
		}
	}

	void InitBoardAndGameFrame()
	{
		boardAndGameFrame.push_back(this->board);
		for (auto elem : this->gameframe->gameFrames)
		{
			boardAndGameFrame.push_back(elem.second);
		}
	}

	void InitEnemyTurret()
	{
		Sprite* sprite = createSprite("../data/turret.png");
		this->enemyturret = std::make_shared<EnemyTurret>(100, 100, 50, 50, sprite);
	}

	void HandleBulletOutOfGameFrame()
	{
		for (auto it = this->enemyturret->getBullets().begin(); it != this->enemyturret->getBullets().end(); )
			if (it->get()->getX() > screenwidth || it->get()->getY() > screenheight)
				it = this->enemyturret->getBullets().erase(it);
			else
				it++;
	}

	void GameOver()
	{
		boardAndGameFrame.clear();
		Blocks.clear();

		board = nullptr;
		gameframe = nullptr;
		ball = nullptr;
		enemyturret = nullptr;

		screenheight = 600;
		screenwidth = 800;

		mouse_x = 0.0;
		mouse_y = 0.0;
		flPrevioustime = 0;
		flCurrenttime = float(getTickCount());
		startTime = 0;

		mouseClick = false;
		RIGHTpressed = false;
		LEFTpressed = false;
		fired = false;

		balldirection = Vector2(0, 0);
		this->Init();
	}
};

int main(int argc, char* argv[])
{
	return run(new MyFramework);
}

