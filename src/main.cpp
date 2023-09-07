#include "GLFW/glfw3.h"
#include <iostream>

#include "player.h"
#include "map.h"

using namespace std;

GLFWwindow *window;

Player *player;
Map *map;

void NewGame()
{
	map = new Map(75);
	player = new Player(100, 75);
	GameOver = false;
}

void Keyboard(GLFWwindow *window, int key, int scode, int action, int smode)
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

			NewGame();
		}
	}
}

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

int main()
{
	srand(time(NULL));

	if(!glfwInit())
	{
		cout << "Error library";
		return -1;
	}

	window = glfwCreateWindow(screenWidth, screenHeight, "MarioRun", nullptr, nullptr);

	if(!window)
	{
		cout << "Error create window";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glClearColor(0, 0, 0, 0);

	glOrtho(0, screenWidth, 0, screenHeight, 0, 1);

	glfwSetKeyCallback(window,Keyboard);
	glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height)
							  {
								  glViewport(0, 0, width, height);
							  });

	InitTexture();

	NewGame();

	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		Time();

		map->Draw();

		if(map->Collision(player->GetArg()))
		{
			GameOver = true;
		}

		player->Draw();

		glfwPollEvents();

		glfwSwapBuffers(window);

		td.ClockUnit = false;
		td.speed = td.delta * 100;
	}

	delete player;
	delete map;

	glfwTerminate();
	return 0;
}
