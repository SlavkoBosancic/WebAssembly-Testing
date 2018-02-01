#pragma once

class GameObject
{
	protected:
		// Coordinates
		float position_x;
		float position_y;

		// Dimensions
		float object_width;
		float object_height;

		// Other
		//char color[] = "orange";

	public:
		GameObject();
		GameObject(float x, float y, float width, float height);
		~GameObject();

		float *GetCoordinates();
		float *GetDimensions();
		bool isBall = false;
};

