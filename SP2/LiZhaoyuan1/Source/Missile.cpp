#include "Missile.h"

Missile::Missile()
{
}

Missile::Missile(const int &AmmoInMag)
{	
	Missiles = AmmoInMag;
	Capacity = new Missile[AmmoInMag];
}

Missile::~Missile()
{
}
void Missile::updatePosition(const Vector3 &pos)
{
	position.x = 0;
	position.y = 490;
	position.z = 0;
}

Vector3 Missile::getPositionOfMissile()
{
	return position;
}
void Missile::setView(const Vector3 &view)
{
	this->view = view;
}
void Missile::Animation(double dt)
{
	float speed = 250.f;
	position += view * speed * dt;
	if (position.x > 750 || position.y > 750 || position.z > 750|| position.x < -750 || position.y < -750 || position.z < -750)
	{
		view = Vector3(0, 0, 0);
	}
}
void Missile::init(Camera3 *target)
{
	camera = target;
}
void Missile::Firing()
{
	if (MissileUsed < Missiles)
	{
		Capacity[MissileUsed].updatePosition(camera->target);
		Capacity[MissileUsed].setView(camera->view);
		MissileUsed++;

	}
	else
	{
		MissileUsed = 0;
	}
}
void Missile::update(double dt)
{
	for (int i = 0; i < Missiles; ++i)
	{
		if (Capacity[i].getPositionOfMissile() != Vector3(0, -10, 0))
		{
			Capacity[i].Animation(dt);
		}
	}
}



