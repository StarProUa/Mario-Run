#include "GLFW/glfw3.h"
#include <iostream>

#include "application.h"
#include "player.h"
#include "map.h"

using namespace std;

GLFWwindow *window;

void Time()
{
	td.new_time = glfwGetTime();
	td.delta = td.new_time - td.old_time;
	td.old_time = td.new_time;
	td.sleep -= td.delta;

	if(td.sleep <= 0)
	{
		td.sleep = 0.1;
		td.ClockUnit = true;
	}
}


class Game : public Application
{
	Player *player;
	Map *map;
public:
	Game() : Application(640, 480, "MarioRun")
	{
		newGame();

		InitTexture();
	}
	~Game()
	{
		delete player;
		delete map;
	}
private:
	void render() override
	{
		Time();

		map->Draw();

		if(map->Collision(player->GetArg()))
		{
			GameOver = true;
		}

		player->Draw();

		glfwPollEvents();

		td.ClockUnit = false;
		td.speed = td.delta * 100;
	}
	void keyboard(int &key, int &scode, int &action, int &smode) override
	{
		if(key == Key::Space && action == KeyState::Press)
		{
			if(key == GLFW_KEY_SPACE && action == GLFW_PRESS)
			{
				if(player->onGround() && !GameOver)
				{
					player->Jump();
				}
				else if(GameOver)
				{
					delete player;
					delete map;

					newGame();
				}
			}
		}
		if(key == Key::Escape && action == KeyState::Press)
		{
			this->exit();
		}
	}
	void newGame()
	{
		map = new Map(75);
		player = new Player(100, 75);
		GameOver = false;
	}
};


int main()
{
	srand(time(NULL));

	Game MarioRun;
	MarioRun.Run();

	return 0;
}
