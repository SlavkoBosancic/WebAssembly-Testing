#pragma once
#include "GameObject.h"

struct Speed
{
	float speed_x;
	float speed_y;
};

class MovableGameObject : public GameObject
{
	public:
		MovableGameObject(float x, float y, float width, float height);
		~MovableGameObject();

		void SetNewCoordinates(float x, float y);
		Speed speed;
};

