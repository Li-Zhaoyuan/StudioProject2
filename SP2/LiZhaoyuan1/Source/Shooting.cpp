#include "Shooting.h"

Shooting::Shooting(const int &AmmoInMag)
{
	AmmoInClip = AmmoInMag;
	Capacity = new Missile[AmmoInMag];
}

Shooting::~Shooting()
{
	delete[] Capacity;
}

void Shooting::init(Camera3 *target)
{
	this->camera = target;
}

void Shooting::Firing()
{
	if (bulletCount < AmmoInClip)
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

void Shooting::update(double dt)
{
	for (int i = 0; i < AmmoInClip; ++i)
	{
		if (Capacity[i].getPositionOfMissile() != Vector3(0, -10, 0))
		{
			Capacity[i].Animation(dt);
		}
	}
}
