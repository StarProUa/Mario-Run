#include "entity.h"
#include "func.h"

#include "GLFW/glfw3.h"
#include "plog/Log.h"

int box[50]  = {0,50, 0,0, 50,50, 50,0,
			   0,50, 0,0, 50,50, 50,0,
			   0,50, 0,0, 50,50, 50,0,
			   0,50, 0,0, 50,50, 50,0,
			   0,50, 0,0, 50,50, 50,0,
			   0,50, 0,0, 50,50, 50,0};

float texture_coords[48] =
	{
		// Run 0
		16.f / 288.f, 0.f,
		16.f / 288.f, 1.f,
		32.f / 288.f, 0.f,
		32.f / 288.f, 1.f,
		// Run 1
		32.f / 288.f, 0.f,
		32.f / 288.f, 1.f,
		48.f / 288.f, 0.f,
		48.f / 288.f, 1.f,
		// Run 2
		48.f / 288.f, 0.f,
		48.f / 288.f, 1.f,
		64.f / 288.f, 0.f,
		64.f / 288.f, 1.f,
		// Jump
		80.f / 288.f, 0.f,
		80.f / 288.f, 1.f,
		96.f / 288.f, 0.f,
		96.f / 288.f, 1.f,
		// loser
		96.f / 288.f, 0.f,
		96.f / 288.f, 1.f,
		112.f / 288.f, 0.f,
		112.f / 288.f, 1.f
};

int cloud_box1[8] = {0, 100, 0,0, 200,100, 200,0};
int cloud_box2[8] = {0, 100, 0,0, 300,100, 300,0};

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

void Entity::spawn()
{
	PLOG_INFO << "ENTITY CREATED";
}

void Player::jumpLogic()
{
	if(dy != 0 && !pause)
	{
		y += dy * delta + 0.25;

		dy -= (y < ground + jumpHeight) ? 0.2 : 1;

		if(y <= ground)
		{
			dy = 0;
			y = ground;
		}
	}
}

void Player::spriteLogic()
{
	if(!pause)
	{
		if(!loser)
		{
			if(clockUnit && onGround())
			{
				sprite += 4;
				if(sprite > 8) sprite = run0;
			}
			else if(!onGround())
			{
				sprite = spriteIndex::jump;
			}
		}
		else
		{
			sprite = fall;
		}
	}
}

bool Player::onGround() { return y == ground || y <= ground + 10; }

void Player::jump()
{
	if(onGround()) dy += jumpHeight; // тут апасна вийде таке шо зможу пригати в меню
}

Player::Player(const int &x, const int &y)
{
	PLOG_DEBUG<< "PLAYER CREATED";

	this->x = x;
	sprite = run0;
	this->y = y;
	dy = 0;
}

void Player::draw()
{
	jumpLogic();

	glPushMatrix();
	glTranslatef(x, y, 0);
	PaintTexture({1, 1, 1}, GL_TRIANGLE_STRIP, sprite, 4, box, texture_coords, 0);
	glPopMatrix();

	spriteLogic();
}

Prop::Prop()
{
	PLOG_DEBUG << "PROP CREATED";

	spawn();
}

void Prop::spawn()
{
	x = rand() % screenWidth + screenWidth;
	y = ground;

	height = (rand() % 2) ? 50 : 100;
	sprite = run0;
}

void Prop::draw()
{
	if(!pause)
	{
		if(!loser) x -= delta * speed;

		spriteLogic();

		if(x < -100) spawn();
	}

	glPushMatrix();
	glTranslatef(x, y, 0);
	PaintTexture({1, 1, 1}, GL_TRIANGLE_STRIP, sprite, 4,
				 (height == 50) ? prop1_box : prop2_box,
				 (height == 50) ? prop1_texture : prop2_texture,
				 (height == 50) ? 0 : 2);
	glPopMatrix();
}

void Prop::spriteLogic()
{
	if(clockUnit)
	{
		sprite += 4;
		if(sprite >= 8) sprite  = run0;
	}
}

Cloud::Cloud()
{
	PLOG_DEBUG<< "CLOUND CREATED";

	spawn();
}

void Cloud::spawn()
{
	y = screenHeight / 2 + 100;

	x = screenWidth;
	type = rand() % 2;
}

void Cloud::draw()
{

	x -= delta * speed;

	if(x < -300) spawn();


	glPushMatrix();
	glTranslatef(x, y, 0);
	PaintTexture({1,1,1}, GL_TRIANGLE_STRIP, run0, 4,
				 (type) ? cloud_box2 : cloud_box1, standart_texture, (type) ? 3 : 4);
	glPopMatrix();
}
