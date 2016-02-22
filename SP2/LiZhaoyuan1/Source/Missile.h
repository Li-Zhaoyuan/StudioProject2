#ifndef MISSILE_H
#define MISSILE_H

#include "Vector3.h"

class Missile
{
public:
	Missile();
	~Missile();
	Vector3 getPositionOfMissile();
	void updatePosition(const Vector3 &pos);
	void setView(const Vector3 &view);
	Vector3 missilePosition;
	void Animation(double dt);
	
private:

	Vector3 position;
	Vector3 view;
};

#endif