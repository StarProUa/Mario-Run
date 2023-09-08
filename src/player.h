#ifndef PLAYER_H
#define PLAYER_H

#include "func.h"

class Player
{
	int jumpHeight = 20;

	int sprite;

	void Jump_Logic();

	void Sprite_Logic();

protected:
	int x;
	float y, dy;
	int ground;

public:
	bool onGround();
	void Jump();
	int GetGround();
	Coord GetArg();
	Player(const int &x, const int &y);
	void Draw();
};

#endif // PLAYER_H
