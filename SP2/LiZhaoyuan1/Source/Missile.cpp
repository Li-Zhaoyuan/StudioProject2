#include "Missile.h"

Missile::Missile()
{
	position = Vector3(20, -10, 20);
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
	position.z = -20;
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
	float speed = 50;
	position += view * speed * dt;
	if (position.x > 1000 || position.y > 1000 ||  position.x < -1000 || position.y < -1000 || position.z < -1000)
	{
		view = Vector3(0, 0, 0);
	}
}
void Missile::init(Camera3 *target)
{
	this->camera = target;
}
void Missile::Firing()
{
	if (bulletCount < Missiles)
	{
		Capacity[bulletCount].updatePosition(camera->target);
		Capacity[bulletCount].setView(camera->view);
		bulletCount++;
	}
	else
	{
		bulletCount = 0;
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

