#ifndef MAP_H
#define MAP_H

#include "func.h"

class Map
{
	friend void Keyboard(GLFWwindow *window, int key, int scode, int action, int smode);

	int ground;
	float mapScroll;

	struct Prop
	{
		int sprite;
		float x; int y;
		int height;
		Prop(int &ground)
		{
			x = rand() % screenWidth + screenWidth;
			y = ground;

			height = (rand() % 2) ? 50 : 100;
			sprite = run0;
		}
	};

	struct Cloud
	{
		bool type;
		float x;
		int y;
		Cloud()
		{
			y = screenHeight / 2 + 100;

			x = screenWidth;
			type = rand() % 2;
		}
	};

	Cloud *cloud = nullptr;
	Prop *prop = nullptr;
	void Sprite_Logic();
	void CheckProp();

public:
	Map(int ground);
	bool Collision(Coord coord);
	void Draw();
	~Map();
};

#endif // MAP_H
