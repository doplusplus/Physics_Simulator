#include "Calculator.h"

Calculator::Calculator()
{}


Calculator::~Calculator()
{}


Vect Calculator::resultant(std::vector<Vect> extActions)
{
	Vect resultant;

	for (auto it = extActions.begin(); it != extActions.end(); it++)
	{
		resultant = resultant + *it;
	}

	return resultant;
}

Vect Calculator::resultant(std::vector<Torsor> extActions)
{
	Vect res;
	for (auto it = extActions.begin(); it != extActions.end(); it++)
	{
		res = res + it->resultant();
	}
	return res;
}


Vect Calculator::centerOfMassAcceleration(Vect resultant, double mass)
{
	Vect acc = Vect(0, 0, 0);
	if (mass > 0)
	{
		acc = resultant / mass;
	}
	else
	{
		throw std::invalid_argument("MassLess_Particle");
	}
	return acc;
}

Vect Calculator::centerOfMassAcceleration(Torsor resultantTorsor, double mass)
{
	return centerOfMassAcceleration(resultantTorsor.resultant(), mass);
}

Vect Calculator::centerOfMassAcceleration(std::vector<Vect> extActions, double mass)
{
	return centerOfMassAcceleration(resultant(extActions), mass);
}

Vect Calculator::centerOfMassAcceleration(std::vector<Torsor> extActions, double mass)
{
	return centerOfMassAcceleration(resultant(extActions), mass);
}



Vect  Calculator::velocity(Vect Acceleration, Vect currentVelocity, double dt)
{
	//integration of the acceleration gives final speeds
	Vect Velocity = currentVelocity + (CartesianElement)Acceleration*dt;
	return Velocity;
}

Point Calculator::position(Vect Acceleration, Vect currentVelocity, Point currentPosition, double dt)
{
	//double integration of the acceleration gives final position
	Point position = (CartesianElement)Acceleration*0.5*dt*dt + (CartesianElement)currentVelocity*dt + currentPosition;
	return position;
}

Vect  Calculator::velocityVariation(Vect Acceleration, double dt)
{
	Vect DVel = (CartesianElement)Acceleration*dt;
	return DVel;
}

Point Calculator::positionVariation(Vect Acceleration, Vect currentVelocity, double dt)
{
	Point DPos = (CartesianElement)Acceleration*0.5*dt*dt + (CartesianElement)currentVelocity*dt;
	return DPos;
}

