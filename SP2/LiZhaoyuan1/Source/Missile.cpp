#include "Missile.h"

Missile::Missile()
{
	position = Vector3(20, -10, 20);
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
	float speed = 100;
	position += view * speed * dt;
	if (position.x > 1000 || position.y > 1000 || position.z > 1000|| position.x < -1000 || position.y < -1000 || position.z < -1000)
	{
		view = Vector3(0, 0, 0);
	}
}


