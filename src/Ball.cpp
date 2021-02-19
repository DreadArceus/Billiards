#include "Ball.hpp"
#include <ctime>

Ball::Ball(double x, double y, double f, int mass)
{
	this->pos = {x, y};
	this->friction = f;
	this->mass = mass;
	this->startTime = 0;
	this->velocity = {0, 0};
}

void Ball::push(double speed, double direction)
{
	this->velocity = {speed, direction};
	this->startTime = time(0);
}

pair<double, double> Ball::updatePosition()
{

}