#include "stdafx.h"
#include "GameEngine.h"


GameEngine::GameEngine(int scene_width, int scene_height)
{
	_scene_width = scene_width;
	_scene_height = scene_height;
}

GameEngine::~GameEngine()
{
}

void GameEngine::SetClearSceneCallback(void (*callback)())
{
	clearScene = callback;
}

void GameEngine::SetDrawRectangleCallback(void (*callback)(int, int, int, int))
{
	drawRectangle = callback;
}

void GameEngine::SetDrawCircleCallback(void (*callback)(int, int, int, int))
{
	drawCircle = callback;
}

float GameEngine::GetSceneWidth()
{
	return _scene_width;
}

float GameEngine::GetSceneHeight()
{
	return _scene_height;
}

void GameEngine::AddObject(GameObject gameObject)
{
	scene[sceneArrayIndex] = gameObject;
	sceneArrayIndex++;
}

void GameEngine::MoveObject(MovableGameObject *movingObject)
{
}

void GameEngine::DrawScene()
{
	clearScene();

	for (int i = 0; i < sceneArrayIndex; i++) {
		GameObject obj = scene[i];
		float *position = obj.GetCoordinates();
		float *dimensions = obj.GetDimensions();

		if (obj.isCircle) {
			drawCircle(*position, *(position++), *dimensions, *(dimensions++));
		} else {
			drawRectangle(*position, *(position++), *dimensions, *(dimensions++));
		}
	}
}
