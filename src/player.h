#ifndef PLAYER_H
#define PLAYER_H

#include "func.h"

class Player
{
	friend void Keyboard(GLFWwindow *window, int key, int scode, int action, int smode);

	int jumpHeight = 55;

	int sprite;

	void Jump_Logic();

	void Sprite_Logic();

protected:
	int x;
	float y, dy;
	int ground;

	void Jump() { dy += jumpHeight; }

	bool onGround();

public:
	int GetGround();
	Coord GetArg();
	Player(int &&x, int &&y);
	void Draw();
};

#endif // PLAYER_H
