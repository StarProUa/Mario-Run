#include "map.h"
#include "func.h"
#include "entity.h"

#include <vector>

#include "GLFW/glfw3.h"
#include "plog/Log.h"

int bacground_box[8]  = {0,screenHeight, 0,0, screenWidth,screenHeight, screenWidth,0};

std::vector<Entity *> entities;

bool collision(const Entity *a, const Entity *b)
{
	const Player *player = static_cast<const Player *>(a);
	const Prop *prop = static_cast<const Prop *>(b);
	return ((player->x <= prop->x + 50) && (player->x + 50 >= b->x)) && player->y <= prop->y + prop->height;
}

Map::Map()
{
	PLOG_DEBUG << "MAP CREATED";

	mapScroll = 0;
	gameOver = false;

	entities.push_back(new Player(100, ground)); // Reservation of the first slot for the player for further collision processing
	entities.push_back(new Prop());
	entities.push_back(new Cloud());
}

bool Map::playerActive()
{
	return !gameOver;
}

void Map::playerJump()
{
	Player *player = static_cast<Player *>(entities[0]);
	player->jump();
}

void Map::draw()
{
	if(!gameOver) mapScroll -= delta * speed;

	glPushMatrix();
	glTranslatef(mapScroll, 0, 0);
	PaintTexture({1, 1, 1}, GL_TRIANGLE_STRIP, 0, 4, bacground_box, standart_texture, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(screenWidth + mapScroll, 0, 0);
	PaintTexture({1, 1, 1}, GL_TRIANGLE_STRIP, 0, 4, bacground_box, standart_texture, 1);
	glPopMatrix();

	if(mapScroll <= -screenWidth) mapScroll = 0;

	for(int i = 0; i < entities.size(); i++)
	{
		entities[i]->draw();
	}

	if(collision(entities[0], entities[1]))
	{
		gameOver = true;
		PLOG_DEBUG << "COLLISION DETECTED";
	}

}

Map::~Map()
{
	for(int i = 0; i < entities.size(); i++)
	{
		delete entities[i];
	}

	entities.clear();

	PLOG_DEBUG << "ENTITIES REMOVED";
	PLOG_DEBUG << "MAP DELETED";
}
