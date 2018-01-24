#include "stdafx.h"
#include "GameEngine.h"
#include "MovableGameObject.h"
#include <emscripten.h>
#include <unistd.h>

// ----- External JS fuctions -------------------

void jsClearCanvas()
{
	EM_ASM(
		externalFunctions.jsClearCanvas();
	);
}

void jsDrawRectangle(int x, int y, int width, int height)
{
	EM_ASM_({
		externalFunctions.jsDrawRectangle($0, $1, $2, $3);
	}, x, y, width, height);
}

void jsDrawCircle(int x, int y, int width, int height)
{
	int radius = width / 2;

	EM_ASM_({
		externalFunctions.jsDrawCircle($0, $1, $2);
	}, x, y, radius);
}

// ---------------------------------------

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
	engine->SetClearSceneCallback(&jsClearCanvas);
	engine->SetDrawRectangleCallback(&jsDrawRectangle);
	engine->SetDrawCircleCallback(&jsDrawCircle);

	// Adding walls to scene
	AddWallsToScene(engine, wallThickness);

	// Adding the ball
	MovableGameObject *ball = AddBallToScene(engine, ball_size);

	// Initial drawing of the scene
	engine->DrawScene();

	//Start moving the ball
	for(int i = 0; i < 200; i++)
	{
		engine->MoveBall(ball);
		usleep(200);
	}

	delete engine;
	return 0;
}
