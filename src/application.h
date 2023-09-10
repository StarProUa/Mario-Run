#ifndef APP_H
#define APP_H

struct GLFWwindow;

enum Key
{
	Space = 32,
	Escape = 256,
};

enum State
{
	Press = 1,
};

enum mouseButton
{
	Left = 0,
	Right,
	Middle,
};

class Application
{
	GLFWwindow *window;

	const double fpsLimit = 1.0 / 60.0;
	double lastUpdateTime = 0, lastFrameTime = 0;
	double sleepTime;

protected:
	Application(int width, int height, const char *title);

	virtual void keyboard(int &key, int &action) = 0;
	virtual void mouse(int &button, int &action, int x, int y) = 0;

	virtual void render() = 0;

	void exit();

	virtual ~Application();

public:
	void Run();

private:
	void initTexture();
	void initLog();

	static void keyboardCallback(GLFWwindow *window, int key, int scode, int action, int smode);
	static void mouseCallback(GLFWwindow *window, int button, int action, int smode);
};

#endif // APP_H
