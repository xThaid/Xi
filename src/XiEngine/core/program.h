#pragma once

class Entity;

class Program
{
public:
	void init();
	void update();

private:
	bool mouseLocked = true;

	Entity* myEntity;
	Entity* myEntity2;
};
