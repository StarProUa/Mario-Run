#ifndef MAP_H
#define MAP_H

class Map
{
public:
	Map();
	bool playerActive();
	void playerJump(); // interface function to call the jump method in the player.
	bool &Pause(); // interface function for accessing 'pause'
	void draw();
	~Map();
};

#endif // MAP_H
