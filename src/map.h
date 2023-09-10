#ifndef MAP_H
#define MAP_H

class Map
{
public:
	Map();
	bool playerActive();
	void playerJump(); // interface function to call the jump method in the player.
	void click(const int &x, const int &y);
	bool &Pause();
	void draw();
	~Map();
};

#endif // MAP_H
