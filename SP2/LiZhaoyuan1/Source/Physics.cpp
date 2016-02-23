#include "Physics.h"
#include <cmath>

Physics::Physics()
{
}

Physics::~Physics()
{
}

float Physics::VelocityUAT(float u, float a, float t)
{
	return u + a * t;
}

float Physics::DisplacementUVT(float u, float v, float t)
{
	return 0.5 * (u + v) * t;
}
float Physics::DisplacemnetUTAT(float u, float t, float a)
{
	return u * t + 0.5 * a * t * t;
}
float Physics::VelocityU2AS(float u, float a, float s)
{
	return sqrt(u * u + 2 * a * s);
}

float Physics::AccelerationFM(float M, float F)
{
	return F / M;
}