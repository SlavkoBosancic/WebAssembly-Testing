#include <stdio.h>
#include <stdlib.h>
#include "GameEngine.h"
#include "MovableGameObject.h"


static GameEngine *global_engine;
static MovableGameObject *global_ball;

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
	engine->AddObject(leftWall);

	// Right Wall
	GameObject *rightWall = new GameObject(width - wallThickness, 0 + wallThickness, wallThickness, height - wallThickness);
	engine->AddObject(rightWall);
}

MovableGameObject *AddBallToScene(GameEngine *engine, int ballSize)
{
	float width = engine->GetSceneWidth();
	float height = engine->GetSceneHeight();

	float ballX = (width - ballSize) / 2;
	float ballY = (height - ballSize) / 2;

	MovableGameObject *ball = new MovableGameObject(ballX, ballY, ballSize, ballSize);
	ball->isCircle = true;

	Speed ballSpeed;
	ballSpeed.speed_x = 3.0f;	//Hard-coded for now, also can be controled from JS...
	ballSpeed.speed_y = 1.5f;	//Hard-coded for now
	ball->speed = ballSpeed;

	engine->AddObject(ball);
	return ball;
}

int main()
{
	int scene_width = 1024;
	int scene_height = 500;
	int wallThickness = 30, ball_size = 30;

	GameEngine *engine = new GameEngine(scene_width, scene_height);

	// Adding walls to scene
	AddWallsToScene(engine, wallThickness);

	// Adding the ball
	MovableGameObject *ball = AddBallToScene(engine, ball_size);

	// Initial drawing of the scene
	engine->DrawScene();

	global_engine = engine;
	global_ball = ball;
	return 0;
}

extern "C" {

	void MoveBall()
	{
		global_engine->MoveBall(global_ball);
	}
	
}
