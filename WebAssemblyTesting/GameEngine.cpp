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

void GameEngine::DrawScene()
{
	clearScene();

	for (int i = 0; i < sceneArrayIndex; i++) {

		GameObject obj = scene[i];
		float *position = obj.GetCoordinates();
		float *dimensions = obj.GetDimensions();
		
		if (obj.isCircle) {
			drawCircle(*position, *(position + 1), *dimensions, *(dimensions + 1));
		} else {
			drawRectangle(*position, *(position + 1), *dimensions, *(dimensions + 1));
		}

		delete position;
		delete dimensions;
	}
}

void GameEngine::MoveBall(MovableGameObject *ball)
{
	float *ballPosition =  ball->GetCoordinates();
	float *ballDimensions = ball->GetDimensions();

	float ballX = *ballPosition;
	float ballY = *(ballPosition + 1);

	float ballWidth = *ballDimensions;
	float ballHeight = *(ballDimensions + 1);

	for (int i = 0; i < sceneArrayIndex; i++) {
		GameObject *obj = &scene[i];

		// if obj is not the ball it self
		if(obj != ball){
			float *objPosition =  obj->GetCoordinates();
			float *objDimensions = obj->GetDimensions();

			float objX = *objPosition;
			float objY = *(objPosition + 1);

			float objWidth = *objDimensions;
			float objHeight = *(objDimensions + 1);

			bool xOverlap = IsOverlaping(objX, (objX + objWidth), ballX, (ballX + ballWidth));
			bool yOverlap = IsOverlaping(objY, (objY + objHeight), ballY, (ballY + ballHeight));
		}
	}
}

bool GameEngine::IsOverlaping(float o1_start, float o1_end, float o2_start, float o2_end)
{
	float totalLength = (o1_end - o1_start) + (o2_end - o2_start);
	float currentLenght = 0;

	if(o1_start <= o2_start){
		currentLenght = o2_end - o1_start;
	}else{
		currentLenght = o1_end - o1_start;
	}

	return (totalLength - currentLenght) >= 0;
}
