#include "map.h"

int prop1_box[16]  = {0,50, 0,0, 50,50, 50,0,
	0,50, 0,0, 50,50, 50,0,};
float prop1_texture[16] =
	{
		// Run 0
		224.f / 288.f, 0.f,
		224.f / 288.f, 1.f,
		240.f / 288.f, 0.f,
		240.f / 288.f, 1.f,
		// Run 1
		240.f / 288.f, 0.f,
		240.f / 288.f, 1.f,
		256.f / 288.f, 0.f,
		256.f / 288.f, 1.f,
};

int prop2_box[16] = {0,100, 0,0, 50,100, 50,0,
					 0,100, 0,0, 50,100, 50,0};
float prop2_texture[16] =
	{
		// Run 0
		0.f, 0.f,
		0.f, 1.f,
		411.f / 822.f, 0.f,
		411.f / 822.f, 1.f,
		// Run 1
		411.f / 822.f, 0.f,
		411.f / 822.f, 1.f,
		1.f, 0.f,
		1.f, 1.f,
};

int bacground_box[8]  = {0,screenHeight, 0,0, screenWidth,screenHeight, screenWidth,0};
float standart_texture[8] =
	{
		0.f, 0.f,
		0.f, 1.f,
		1.f, 0.f,
		1.f, 1.f
};

int cloud_box1[8] = {0, 100, 0,0, 200,100, 200,0};
int cloud_box2[8] = {0, 100, 0,0, 300,100, 300,0};

void Map::Sprite_Logic()
{
	if(td.ClockUnit)
	{
		prop->sprite += 4;
		if(prop->sprite  >= 8) prop->sprite  = run0;
		td.sleep = 0.1;
	}
}

void Map::CheckProp()
{
	if(prop == nullptr)
	{
		prop = new Prop(ground);
	}
	if(cloud == nullptr)
	{
		cloud = new Cloud();
	}
}

Map::Map(int ground)
{
	this->ground = ground;
	mapScroll = 0;
}

bool Map::Collision(Coord coord)
{
	CheckProp();
	return ((prop->x <= coord.x + 50) && (prop->x + 50 >= coord.x)) && coord.y <= prop->y + prop->height;
}

void Map::Draw()
{
	CheckProp();

	if(!GameOver)
	{
		prop->x -= 5 * td.speed;
		mapScroll -= 5 * td.speed;
		cloud->x -= 2 * td.speed;
	}

	// Scroll map //

	glPushMatrix();
	glTranslatef(mapScroll, 0, 0);
	PaintTexture(white, GL_TRIANGLE_STRIP, 0, 4, bacground_box, standart_texture, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(screenWidth + mapScroll, 0, 0);
	PaintTexture(white, GL_TRIANGLE_STRIP, 0, 4, bacground_box, standart_texture, 1);
	glPopMatrix();

	// Draw Cloud //

	glPushMatrix();
	glTranslatef(cloud->x, cloud->y, 0);
	if(cloud->type)
	{
		PaintTexture(white, GL_TRIANGLE_STRIP, run0, 4, cloud_box2, standart_texture, 3);
	}
	else
	{
		PaintTexture(white, GL_TRIANGLE_STRIP, run0, 4, cloud_box1, standart_texture, 4);
	}
	glPopMatrix();

	// Draw Prop(Enemy) //

	glPushMatrix();
	glTranslatef(prop->x, prop->y, 0);

	Sprite_Logic();

	if(prop->height == 50)
	{
		PaintTexture(white, GL_TRIANGLE_STRIP, prop->sprite, 4, prop1_box, prop1_texture, 0);
	}
	else
	{
		PaintTexture(white, GL_TRIANGLE_STRIP, prop->sprite, 4, prop2_box, prop2_texture, 2);
	}
	glPopMatrix();

	// Check //

	if(mapScroll <= -screenWidth)
	{
		mapScroll = 0;
	}

	if(cloud->x < -300)
	{
		delete cloud;
		cloud = nullptr;
	}

	if(prop->x < -100)
	{
		delete prop;
		prop = nullptr;
	}
}

Map::~Map()
{
	delete prop;
	delete cloud;
}
