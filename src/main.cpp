#include "GLFW/glfw3.h"
#include <iostream>

#include "application.h"
#include "map.h"

using namespace std;

class Game : public Application
{
	Map *map;
public:
	Game() : Application(640, 480, "MarioRun")
	{
		map = new Map();
	}
	~Game()
	{
		delete map;
	}
private:
	void render() override
	{
		map->draw();
	}
	void keyboard(int &key, int &scode, int &action, int &smode) override
	{
		if(key == Key::Space && action == KeyState::Press)
		{
			if(key == GLFW_KEY_SPACE && action == GLFW_PRESS)
			{
				if(map->playerActive())
				{
					map->playerJump();
				}
				else
				{
					delete map;
					map = new Map();
				}
			}
		}
		if(key == Key::Escape && action == KeyState::Press)
		{
			this->exit();
		}
	}
};


int main()
{
	srand(time(NULL));

	Game MarioRun;
	MarioRun.Run();

	return 0;
}
