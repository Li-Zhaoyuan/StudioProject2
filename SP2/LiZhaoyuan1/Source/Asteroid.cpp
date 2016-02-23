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
}
void Asteroid::Animation(double dt)
{
	float speed = 25.f;
	camera.position.x = target.x;
	camera.position.y = target.y;
	camera.position.z = target.z;
	position += view * speed * dt;
	target += view * speed * dt;
}
void Asteroid::setView(const Vector3 &view)
{
	this->view = view;
}
