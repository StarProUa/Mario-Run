#ifndef MAP_H
#define MAP_H

class Map
{
	float mapScroll;
public:
	Map();
	bool playerActive();
	void playerJump(); // interface function to call the jump method in the player.
	void draw();
	~Map();
};

#endif // MAP_H
