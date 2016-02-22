#ifndef PHYSICS_H
#define PHYSICS_H

class Physics
{
	float finalvelocity;
	float initvelocity = 0;
	float gravity = -9.8f;
	float acceleration;
	float displacement;

protected:
	float groundLevel;

public:
	Physics();
	~Physics();

	int Gravity();
};

#endif