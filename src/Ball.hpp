#pragma once

using namespace std;

class Ball
{
public:
	Ball(double x, double y, double f, int mass);
	void push(double speed, double direction);
	pair<double, double> updatePosition();
private:
	pair<double, double> pos;
	pair<double, double> velocity;
	double startTime;
	double friction;
	int mass;
};