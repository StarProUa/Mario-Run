#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
	friend bool collision(const Entity *a, const Entity *b);

protected:
	int sprite;
	float x, y, dx, dy;

	virtual void spriteLogic() = 0;

	void spawn();

public:
	virtual void draw() = 0;
	virtual ~Entity(){};
};

class Player : public Entity
{
	int jumpHeight = 120;

public:
	void jump();
	Player(const int &x, const int &y);
	void draw() override;
	~Player() override{};
private:
	void spriteLogic() override;
	//void spawn();
	void jumpLogic();
	bool onGround();
};

class Prop : public Entity
{
public:
	Prop();

	int height;
	~Prop() override{};
private:
	void spawn();
	void draw() override;
	void spriteLogic() override;
};

class Cloud : public Entity
{
	bool type;
public:
	Cloud();
	~Cloud() override{};
private:
	void spawn();
	void draw() override;
	void spriteLogic() override{};
};

#endif // ENTITY_H
