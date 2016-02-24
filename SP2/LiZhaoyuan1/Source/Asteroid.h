#ifndef ASTEROID_H
#define ASTEROID_H

#include "Vector3.h"
#include "Camera3.h"

class Asteroid
{
public:
	Asteroid();
	~Asteroid();
	void Animation(double dt);
	void setView(const Vector3 &view);
	Vector3 getPositionOfMissile();
	void updatePosition(const Vector3 &pos);
	void FlytowardPlayer();
	void update(double dt);

private:
	Vector3 AsteroidCoord = Vector3(-40, 600, -100);
	Vector3 position;
	Vector3 view;
	Vector3 target;
	Camera3 camera;

	float rotateAsteroid = 0;

	float AsteroidCoordx = 0;
	float AsteroidCoordz = 0;
};

#endif