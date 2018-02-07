#include <stdio.h>
#include <stdlib.h>
#include "GameEngine.h"
#include "MovableGameObject.h"
#include <emscripten.h>


static GameEngine *global_engine;
static MovableGameObject *global_ball;
static MovableGameObject *global_left_paddle;
static MovableGameObject *global_right_paddle;

void increaseScore(bool leftPlayer)
{
	EM_ASM_({
		jsFunctions.increaseScore($0);
	}, leftPlayer);
}

void sideWallCollision(GameObject *wall, GameObject *ball)
{
	float *wallPosition =  wall->GetCoordinates();
	float wallX = *wallPosition;

	if(wallX == 0){
		increaseScore(false);
	}else{
		increaseScore(true);
	}
}

void AddWallsToScene(GameEngine *engine, int wallThickness)
{
	float width = engine->GetSceneWidth();
	float height = engine->GetSceneHeight();

	// Top Wall
	GameObject *topWall = new GameObject(0, 0, width, wallThickness);
	engine->AddObject(topWall);

	// Bottom Wall
	GameObject *bottomWall = new GameObject(0, height - wallThickness, width, wallThickness);
	engine->AddObject(bottomWall);

	// Left Wall
	GameObject *leftWall = new GameObject(0, 0 + wallThickness, wallThickness, height - wallThickness);
	leftWall->onCollide = sideWallCollision;
	engine->AddObject(leftWall);

	// Right Wall
	GameObject *rightWall = new GameObject(width - wallThickness, 0 + wallThickness, wallThickness, height - wallThickness);
	rightWall->onCollide = sideWallCollision;
	engine->AddObject(rightWall);
}

MovableGameObject *AddBallToScene(GameEngine *engine, int ballSize)
{
	float width = engine->GetSceneWidth();
	float height = engine->GetSceneHeight();

	float ballX = (width - ballSize) / 2;
	float ballY = (height - ballSize) / 2;

	MovableGameObject *ball = new MovableGameObject(ballX, ballY, ballSize, ballSize);
	ball->isBall = true;

	Speed ballSpeed;
	ballSpeed.speed_x = 6.0f;	//Hard-coded for now, also can be controled from JS...
	ballSpeed.speed_y = 2.9f;	//Hard-coded for now
	ball->speed = ballSpeed;

	engine->AddObject(ball);
	return ball;
}

MovableGameObject *AddPaddleToScene(GameEngine *engine, int paddleThickness, bool leftPosition)
{
	int paddleHeight = 80;
	int spacingFromWall = 80;
	int wallThickness = paddleThickness;

	float width = engine->GetSceneWidth();
	float height = engine->GetSceneHeight();

	float paddleX = leftPosition ? wallThickness + spacingFromWall :
								   width - wallThickness - spacingFromWall - paddleThickness;
	float paddleY = (height - paddleHeight) / 2;

	MovableGameObject *paddle = new MovableGameObject(paddleX, paddleY, paddleThickness, paddleHeight);

	Speed paddleSpeed;
	paddleSpeed.speed_x = 0;
	paddleSpeed.speed_y = 10.0f;
	paddle->speed = paddleSpeed;

	engine->AddObject(paddle);
	return paddle;
}

int main()
{
	int scene_width = 1024;
	int scene_height = 500;
	int elementSize = 30;

	GameEngine *engine = new GameEngine(scene_width, scene_height);

	// Adding walls to scene
	AddWallsToScene(engine, elementSize);

	// Adding the ball
	MovableGameObject *ball = AddBallToScene(engine, elementSize);

	//Adding paddles to scene
	MovableGameObject *leftPaddle = AddPaddleToScene(engine, elementSize, true);
	MovableGameObject *rightPaddle = AddPaddleToScene(engine, elementSize, false);

	// Initial drawing of the scene
	engine->DrawScene();

	// Adding element to global variables
	global_engine = engine;
	global_ball = ball;
	global_left_paddle = leftPaddle;
	global_right_paddle = rightPaddle;

	return 0;
}

extern "C" {

	void MoveBall()
	{
		global_engine->MoveBall(global_ball);
	}

	void MovePaddle(bool leftPaddle, bool moveDOWN)
	{
		MovableGameObject *paddle = leftPaddle ? global_left_paddle : global_right_paddle;
		global_engine->MovePaddle(paddle, moveDOWN);
	}
	
}
