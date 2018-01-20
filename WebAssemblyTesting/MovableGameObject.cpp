#include "stdafx.h"
#include "MovableGameObject.h"


MovableGameObject::MovableGameObject(float x, float y, float width, float height) : GameObject(x, y, width, height)
{
}

MovableGameObject::~MovableGameObject()
{
}

void MovableGameObject::SetNewCoordinates(float x, float y)
{
	position_x = x;
	position_y = y;
}
