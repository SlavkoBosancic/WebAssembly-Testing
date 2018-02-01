#pragma once
#include "MovableGameObject.h"

class GameEngine
{
	float _scene_width;
	float _scene_height;

	GameObject *scene[7];
	int sceneArrayIndex = 0;

	void ClearSceneJS();
	void DrawRectangleJS(int x, int y, int width, int height);
	void DrawCircleJS(int x, int y, int width, int height);

	bool IsOverlaping(float o1_start, float o1_end, float o2_start, float o2_end);

	public:
		GameEngine(int scene_width, int scene_height);
		~GameEngine();

		float GetSceneWidth();
		float GetSceneHeight();

		void AddObject(GameObject *gameObject);
		void ClearScene();
		void DrawScene();

		void MoveBall(MovableGameObject *ball);
		void MovePaddle(MovableGameObject *paddle, bool moveDOWN);
};

