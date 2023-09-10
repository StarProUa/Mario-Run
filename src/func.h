#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>

#define screenWidth 640
#define screenHeight 480

#define WAIT 0.1

#define ground 75

#define speed 200

struct Coord
{
	float x, y;
};

struct Color
{
	unsigned int r, g, b;
};

inline bool loser, pause = true;
inline bool clockUnit;
inline double delta = 0;

inline float standart_texture[8] = {
	0.f, 0.f,
	0.f, 1.f,
	1.f, 0.f,
	1.f, 1.f };

enum spriteIndex
{
	run0 = 0,
	run1 = 4,
	run2 = 8,
	jump = 12,
	fall = 16,
};

void Paint(Color color, unsigned int &&Mode, int &&array_first, int &&array_size, int *array);

void PaintTexture(Color color, unsigned int &&Mode, int array_first, int array_size, int *array, float *texture_array, unsigned id);

#endif // FUNCTION_H
