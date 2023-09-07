#ifndef FUNCTION_H
#define FUNCTION_H

#define screenWidth 640
#define screenHeight 480

#include "GLFW/glfw3.h"
#include <iostream>

struct Coord
{
	float x, y;
};

struct Color
{
	GLuint r, g, b;
};

inline Color yellow {1, 1, 0};
inline Color white {1, 1, 1};

inline bool GameOver;

enum spriteIndex
{
	run0 = 0,
	run1 = 4,
	run2 = 8,
	jump = 12,
	fall = 16,
};

struct TimeData
{
	float new_time, old_time, delta;
	float sleep = 0.1;
	bool ClockUnit = false;
	float speed;
};

inline TimeData td;

void Paint(Color &color, GLenum &&Mode, int &&array_first, int &&array_size, int *array);

void PaintTexture(Color &color, GLenum &&Mode, int array_first, int array_size, int *array, float *texture_array, unsigned id);

void InitTexture();

#endif // FUNCTION_H
