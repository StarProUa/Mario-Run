#include "player.h"

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
		// GameOver
		96.f / 288.f, 0.f,
		96.f / 288.f, 1.f,
		112.f / 288.f, 0.f,
		112.f / 288.f, 1.f
};

void Player::Jump_Logic()
{
	if(dy != 0 )
	{
		y += dy * td.speed / 10;

		dy -= (y < ground + jumpHeight) ? 0.1 : 0.2;

		if(y <= ground)
		{
			dy = 0;
			y = ground;
		}
	}
}

void Player::Sprite_Logic()
{
	if(!GameOver)
	{
		if(td.ClockUnit && onGround())
		{
			sprite += 4;
			if(sprite > 8) sprite = run0;
			td.sleep = 0.1;
		}
		else if(!onGround())
		{
			sprite = jump;
		}
	}
	else
	{
		sprite = fall;
	}

}

bool Player::onGround() { return y == ground || y <= ground + 10; }

Coord Player::GetArg()
{
	Coord coord {static_cast<float>(x), y};
	return coord;
}

Player::Player(int &&x, int &&y)
{
	sprite = run0;
	this->x = x;
	this->y = this->ground = y;
	dy = 0;
}

void Player::Draw()
{
	Jump_Logic();

	glPushMatrix();
	glTranslatef(x, y, 0);
	PaintTexture(white, GL_TRIANGLE_STRIP, sprite, 4, box, texture_coords, 0);
	glPopMatrix();

	Sprite_Logic();
}
