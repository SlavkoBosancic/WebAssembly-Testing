#include "GameEngine.h"
#include <emscripten.h>


GameEngine::GameEngine(int scene_width, int scene_height)
{
	_scene_width = scene_width;
	_scene_height = scene_height;
}

GameEngine::~GameEngine()
{
	printf("Game engine finalizer called.");
	for (int i = 0; i < sceneArrayIndex; i++) {
		GameObject *obj = scene[i];
		delete obj;
	}
}

void GameEngine::ClearSceneJS()
{
	EM_ASM(
		jsFunctions.jsClearCanvas();
	);
}

void GameEngine::DrawRectangleJS(int x, int y, int width, int height)
{
	EM_ASM_({
		jsFunctions.jsDrawRectangle($0, $1, $2, $3);
	}, x, y, width, height);
}

void GameEngine::DrawCircleJS(int x, int y, int width, int height)
{
	int radius = width / 2;

	EM_ASM_({
		jsFunctions.jsDrawCircle($0, $1, $2);
	}, x, y, radius);
}

float GameEngine::GetSceneWidth()
{
	return _scene_width;
}

float GameEngine::GetSceneHeight()
{
	return _scene_height;
}

void GameEngine::AddObject(GameObject *gameObject)
{
	scene[sceneArrayIndex] = gameObject;
	sceneArrayIndex++;
}

void GameEngine::DrawScene()
{
	ClearSceneJS();

	for (int i = 0; i < sceneArrayIndex; i++) {

		GameObject *obj = scene[i];
		float *position = obj->GetCoordinates();
		float *dimensions = obj->GetDimensions();
		
		if (obj->isCircle) {
			DrawCircleJS(*position, *(position + 1), *dimensions, *(dimensions + 1));
		} else {
			DrawRectangleJS(*position, *(position + 1), *dimensions, *(dimensions + 1));
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
	float nextBallX = ballX + ball->speed.speed_x;
	float nextBallY = ballY + ball->speed.speed_y;

	float ballWidth = *ballDimensions;
	float ballHeight = *(ballDimensions + 1);

	for (int i = 0; i < sceneArrayIndex; i++) {
		GameObject *obj = scene[i];

		// if obj is not the ball itself
		if(obj != ball){
			float *objPosition =  obj->GetCoordinates();
			float *objDimensions = obj->GetDimensions();

			float objX = *objPosition;
			float objY = *(objPosition + 1);

			float objWidth = *objDimensions;
			float objHeight = *(objDimensions + 1);

			bool overlapX = IsOverlaping(objX, (objX + objWidth), ballX, (ballX + ballWidth));
			bool overlapY = IsOverlaping(objY, (objY + objHeight), ballY, (ballY + ballHeight));

			// if overlaping already, just set new coordinates... change of direction already done
			if(!(overlapX && overlapY)){
				// check if next movement will colide the ball with object
				bool nextOverlapX = IsOverlaping(objX, (objX + objWidth), nextBallX, (nextBallX + ballWidth));
				bool nextOverlapY = IsOverlaping(objY, (objY + objHeight), nextBallY, (nextBallY + ballHeight));

				if(nextOverlapX && nextOverlapY){
					// colision on next move, chage direction of ball movement
					// check which axis was not in colision previously, that direction needs to change
					if(!overlapX) { ball->speed.speed_x *= -1; }
					if(!overlapY) { ball->speed.speed_y *= -1; }
				}
			}

			delete objPosition;
			delete objDimensions;
		}
	}
	
	delete ballPosition;
	delete ballDimensions;

	ball->SetNewCoordinates(nextBallX, nextBallY);
	DrawScene();
}

bool GameEngine::IsOverlaping(float o1_start, float o1_end, float o2_start, float o2_end)
{
	float totalLength = (o1_end - o1_start) + (o2_end - o2_start);
	float currentLenght = 0;

	if(o1_start <= o2_start){
		currentLenght = o2_end - o1_start;
	}else{
		currentLenght = o1_end - o2_start;
	}

	return (totalLength - currentLenght) >= 0;
}
