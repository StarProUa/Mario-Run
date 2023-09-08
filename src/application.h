#ifndef APP_H
#define APP_H

struct GLFWwindow;

enum Key
{
	Space = 32,
	Escape = 256,
};

enum KeyState
{
	Press = 1,
};

class Application
{
	GLFWwindow *window;
	int screenWidth, screenHeight;

	const double fpsLimit = 1.0 / 60.0;
	double lastUpdateTime = 0;
	double lastFrameTime = 0;

protected:
	Application(int width, int height, const char *title);

	virtual void keyboard(int &key, int &scode, int &action, int &smode) = 0;
	virtual void render() = 0;

	void exit();

	virtual ~Application();

public:
	void Run();


private:
	void initLog();
	static void keyboardCallback(GLFWwindow *window, int key, int scode, int action, int smode);
};

#endif // APP_H
