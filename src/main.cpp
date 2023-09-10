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
	void keyboard(int &key, int &action) override
	{
		if(key == Key::Space && action == State::Press)
		{
			if(map->playerActive() && !map->Pause())
			{
				map->playerJump();
			}			
		}
		if(key == Key::Escape && action == State::Press)
		{
			if(!map->Pause()) map->Pause() = true;
			else map->Pause() = false;
		}
	}
	void mouse(int &button, int &action, int x, int y) override
	{
		if(button == mouseButton::Left && action == State::Press)
		{
			if(map->Pause())
			{
				if((x >= 218 && x <= 218 + 203) && (y >= 228 && y <= 228 + 65)) // start
				{
					map->Pause() = false;

					if(!map->playerActive())
					{
						delete map;
						map = new Map();
					}
				}
				else if((x >= 187 && x <= 187 + 264) && (y >= 138 && y <= 138 + 65)) // options
				{
					// not released
				}
				else if((x >= 248 && x <= 248 + 142) && (y >= 48 && y <= 48 + 65)) // start
				{
					this->exit();
				}
			}
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
