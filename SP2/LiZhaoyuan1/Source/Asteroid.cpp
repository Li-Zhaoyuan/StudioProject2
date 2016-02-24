#include "Asteroid.h"

Asteroid::Asteroid()
{
	position.Set(10, 500, 20);
}
Asteroid::~Asteroid()
{

}
Vector3 Asteroid::getPositionOfMissile()
{
	return position;
}
void Asteroid::updatePosition(const Vector3 &pos)
{
	position = pos;
	camera.position.x = target.x;
	camera.position.y = target.y;
	camera.position.z = target.z;
}
void Asteroid::Animation(double dt)
{
	float speed = 25.f;
	position += view * speed * dt;
	if (position.x > 750 || position.y > 750 || position.z > 750 || position.x < -750 || position.y < -750 || position.z < -750)
	{
		view = Vector3(0, 500, -30);
	}
}
void Asteroid::setView(const Vector3 &view)
{
	this->view = view;
}
void Asteroid::update(double dt)
{

}