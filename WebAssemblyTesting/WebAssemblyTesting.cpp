#include "stdafx.h"
#include "GameEngine.h"
#include "MovableGameObject.h"
#include <emscripten.h>

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
	EM_ASM_({
		externalFunctions.jsDrawCircle($0, $1, $2, $3);
	}, x, y, width, height);
}

// ---------------------------------------

void AddWallsToScene(GameEngine *engine, int wallThickness)
{
	float width = engine->GetSceneWidth();
	float height = engine->GetSceneHeight();

	// Top Wall
	GameObject topWall (0, 0, width, wallThickness);
	engine->AddObject(topWall);

	// Bottom Wall
	GameObject bottomWall (0, height - wallThickness, width, wallThickness);
	engine->AddObject(bottomWall);

	// Left Wall
	GameObject leftWall (0, 0 + wallThickness, wallThickness, height - wallThickness);
	engine->AddObject(leftWall);

	// Right Wall
	GameObject rightWall (width - wallThickness, 0 + wallThickness, wallThickness, height - wallThickness);
	engine->AddObject(rightWall);
}

int main()
{
	int scene_width = 1024;
	int scene_height = 500;
	int wallThickness = 30, ball_size = wallThickness;

	GameEngine engine (scene_width, scene_height);
	engine.SetClearSceneCallback(&jsClearCanvas);
	engine.SetDrawRectangleCallback(&jsDrawRectangle);
	engine.SetDrawCircleCallback(&jsDrawCircle);

	// Adding walls to scene
	AddWallsToScene(&engine, wallThickness);

	// Adding the ball
	float ballX = (scene_width - ball_size) / 2;
	float ballY = (scene_height - ball_size) / 2;
	MovableGameObject ball (ballX, ballY, ball_size, ball_size);
	ball.isCircle = true;
	Speed ballSpeed;
	ballSpeed.speed_x = 3.0f;
	ballSpeed.speed_y = 1.5f;
	ball.speed = ballSpeed;

	engine.AddObject(ball);

	// Initial drawing of the scene
	engine.DrawScene();

	//Start moving the ball
	// while (int i = 1)
	// {
	// 	engine.MoveObject(&ball);
	// 	i--;
	// }

	return 0;
}
