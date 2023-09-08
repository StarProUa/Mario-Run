#include "application.h"
#include "GLFW/glfw3.h"
#include "plog/Log.h"
#include "plog/Initializers/RollingFileInitializer.h"

Application::Application(int width, int height, const char *title) : screenWidth(width), screenHeight(height)
{
	initLog();

	if(!glfwInit()) { PLOG_FATAL << "FAILED TO INIT GLFW LIBRARY"; }

	window = glfwCreateWindow(width, height, title, nullptr, nullptr);

	if(!window) { PLOG_ERROR << "ERROR TO CREATE WINDOW"; }

	glfwMakeContextCurrent(window);

	glClearColor(1, 1, 1, 0);
	glOrtho(0, screenWidth, 0, screenHeight, 0, 1);

	glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height)
							  {
								  glViewport(0, 0, width, height);
							  });

	glfwSetWindowUserPointer(window, this);

	glfwSetKeyCallback(window, keyboardCallback);
}

void Application::exit()
{
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Application::Run()
{
	PLOG_DEBUG << "APPLICATION IS RUN";

	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		double now = glfwGetTime();
		double delta = now - lastUpdateTime;

		glfwPollEvents();

		if((now - lastFrameTime) >= fpsLimit)
		{
			render();
			glfwSwapBuffers(window);

			lastFrameTime = now;
		}

		lastUpdateTime = now;
	}

}

void Application::initLog()
{
	std::time_t rawtime;
	std::tm* timeinfo;

	std::time(&rawtime);
	timeinfo = std::localtime(&rawtime);

	std::string logName = "log_" + std::to_string(1900 + timeinfo->tm_year)
						  + "-" +
						  ((timeinfo->tm_mon + 1 > 9) ? std::to_string(timeinfo->tm_mon + 1) : "0" + std::to_string(timeinfo->tm_mon + 1))
						  + "-" +
						  ((timeinfo->tm_mday > 9) ? std::to_string(timeinfo->tm_mday) : "0" + std::to_string(timeinfo->tm_mday))
						  + "-" +
						  ((timeinfo->tm_hour > 9) ? std::to_string(timeinfo->tm_hour) : "0" + std::to_string(timeinfo->tm_hour))
						  + "-" +
						  ((timeinfo->tm_min > 9) ? std::to_string(timeinfo->tm_min) : "0" + std::to_string(timeinfo->tm_min)) + ".txt";

	plog::init(plog::debug, ("../log/" + logName).c_str());

	PLOG_DEBUG << "PLOG IS INIT";
}

Application::~Application()
{
	PLOG_DEBUG << "APPLICATION IS DESTROYED";

	glfwDestroyWindow(window);
	glfwTerminate();

}

void Application::keyboardCallback(GLFWwindow *window, int key, int scode, int action, int smode)
{
	Application *app = static_cast<Application *>(glfwGetWindowUserPointer(window));
	app->keyboard(key, scode, action, smode);
}
