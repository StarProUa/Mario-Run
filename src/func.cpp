#include "func.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

unsigned texture[5];

void Paint(Color &color, GLenum &&Mode, int &&array_first, int &&array_size, int *array)
{
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glVertexPointer(2, GL_INT, 0, array);
	glEnableClientState(GL_VERTEX_ARRAY);

	glColor3f(color.r, color.g, color.b);
	glDrawArrays(Mode, array_first, array_size);

	glDisableClientState(GL_VERTEX_ARRAY);
}

void PaintTexture(Color &color, GLenum &&Mode, int array_first, int array_size, int *array, float *texture_array, unsigned int id)
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

void InitTexture()
{
	unsigned amount = 5;

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

	for(unsigned i = 0; i < amount; i++)
	{
		if(arg[i].data == NULL)
		{
			cout << "Failed load image!" << i << endl;
			glfwTerminate();
			exit(-1);
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
}
