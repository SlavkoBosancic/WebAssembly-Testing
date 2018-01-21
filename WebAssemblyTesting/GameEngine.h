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

	public:
		GameEngine(int scene_width, int scene_height);
		~GameEngine();

		float GetSceneWidth();
		float GetSceneHeight();

		void AddObject(GameObject gameObject);
		void MoveObject(MovableGameObject *movingObject);

		void ClearScene();
		void DrawScene();
};

