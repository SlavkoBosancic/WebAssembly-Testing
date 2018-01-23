#pragma once
#include "MovableGameObject.h"

class GameEngine
{
	float _scene_width;
	float _scene_height;

	GameObject scene[7];
	int sceneArrayIndex = 0;

	void (*clearScene)();
	void (*drawRectangle)(int x, int y, int width, int height);
	void (*drawCircle)(int x, int y, int width, int height);

	bool IsOverlaping(float o1_start, float o1_end, float o2_start, float o2_end);

	public:
		GameEngine(int scene_width, int scene_height);
		~GameEngine();

		void SetClearSceneCallback(void (*callback)());
		void SetDrawRectangleCallback(void (*callback)(int, int, int, int));
		void SetDrawCircleCallback(void (*callback)(int, int, int, int));

		float GetSceneWidth();
		float GetSceneHeight();

		void AddObject(GameObject gameObject);
		void ClearScene();
		void DrawScene();

		void MoveBall(MovableGameObject *ball);
		void MovePaddle(MovableGameObject *paddle);
};

