#include "application.h"
#include "func.h"

#include "GLFW/glfw3.h"

#include "plog/Log.h"
#include "plog/Initializers/RollingFileInitializer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned texture[6];

void Paint(Color color, unsigned int &&Mode, int &&array_first, int &&array_size, int *array)
{
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glVertexPointer(2, GL_INT, 0, array);
	glEnableClientState(GL_VERTEX_ARRAY);

	glColor3f(color.r, color.g, color.b);
	glDrawArrays(Mode, array_first, array_size);

	glDisableClientState(GL_VERTEX_ARRAY);
}

void PaintTexture(Color color, unsigned int &&Mode, int array_first, int array_size, int *array, float *texture_array, unsigned int id)
{
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(2, GL_INT, 0, array);
	glTexCoordPointer(2, GL_FLOAT, 0, texture_array);

	glColor4f(color.r, color.g, color.b, 1);
	glBindTexture(GL_TEXTURE_2D, texture[id]);
	glDrawArrays(Mode, array_first, array_size);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

Application::Application(int width, int height, const char *title)
{
	initLog();

	PLOG_FATAL_IF(!glfwInit()) << "FAILED TO INIT GLFW LIBRARY";

	window = glfwCreateWindow(width, height, title, nullptr, nullptr);

	PLOG_ERROR_IF(!window) << "ERROR TO CREATE WINDOW";

	glfwMakeContextCurrent(window);

	glClearColor(1, 1, 1, 0);
	glOrtho(0, screenWidth, 0, screenHeight, 0, 1);

	glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height)
							  {
								  glViewport(0, 0, width, height);
							  });

	glfwSetKeyCallback(window, keyboardCallback);

	glfwSetMouseButtonCallback(window, mouseCallback);

	glfwSetWindowUserPointer(window, this);

	initTexture();

	sleepTime = WAIT;
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
		delta = now - lastUpdateTime;

		glfwPollEvents();

		if((sleepTime -= delta) <= 0)
		{
			clockUnit = true;
			sleepTime = WAIT;
		}

		render();
		glfwSwapBuffers(window);

		clockUnit = false;

		lastUpdateTime = now;

	}
}

void Application::initTexture()
{
	unsigned amount = 6;

	struct Texture
	{
		int h_image, w_image, cnt;
		unsigned char *data;
	} arg[amount];

	arg[0].data = stbi_load("../assets/small_mario.png", &arg[0].w_image, &arg[0].h_image, &arg[0].cnt, 0);
	arg[1].data = stbi_load("../assets/background_ground.jpg", &arg[1].w_image, &arg[1].h_image, &arg[1].cnt, 0);
	arg[2].data = stbi_load("../assets/flower_atlass.png", &arg[2].w_image, &arg[2].h_image, &arg[2].cnt, 0);
	arg[3].data = stbi_load("../assets/one_clound.png", &arg[3].w_image, &arg[3].h_image, &arg[3].cnt, 0);
	arg[4].data = stbi_load("../assets/two_clound.png", &arg[4].w_image, &arg[4].h_image, &arg[4].cnt, 0);
	arg[5].data = stbi_load("../assets/menu.png", &arg[5].w_image, &arg[5].h_image, &arg[5].cnt, 0);

	for(unsigned i = 0; i < amount; i++)
	{
		if(arg[i].data == NULL)
		{
			PLOG_FATAL << "FAILED TO INIT TEXTURE - " << std::to_string(i);
		}
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);

	glGenTextures(amount, texture);

	for(unsigned i = 0; i < amount; i++)
	{
		glBindTexture(GL_TEXTURE_2D, texture[i]);
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexImage2D(GL_TEXTURE_2D, 0, (arg[i].cnt == 4) ? GL_RGBA : GL_RGB,
						 arg[i].w_image, arg[i].h_image, 0, (arg[i].cnt == 4) ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, arg[i].data);
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glDisable(GL_TEXTURE_2D);

	for(unsigned i = 0; i < amount; i++)
	{
		stbi_image_free(arg[i].data);
	}

	PLOG_DEBUG << "TEXTURES CREATED AND UPLOADED";
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
	app->keyboard(key, action);
}

void Application::mouseCallback(GLFWwindow *window, int button, int action, int smode)
{
	double x, y;

	glfwGetCursorPos(window, &x, &y);

	Application *app = static_cast<Application *>(glfwGetWindowUserPointer(window));
	app->mouse(button, action, x, screenHeight - y);
}
