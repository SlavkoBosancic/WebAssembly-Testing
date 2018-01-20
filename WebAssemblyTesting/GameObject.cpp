#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
{
	position_x = 0;
	position_y = 0;

	object_width = 0;
	object_height = 0;
}

GameObject::GameObject(float x, float y, float width, float height)
{
	position_x = x;
	position_y = y;

	object_width = width;
	object_height = height;
}

GameObject::~GameObject()
{
}

float* GameObject::GetCoordinates()
{
	float result[2] = { position_x, position_y };
	return result;
}

float* GameObject::GetDimensions()
{
	float result[2] = { object_width, object_height };
	return result;
}
