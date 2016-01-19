#include "Calculator.h"

Calculator::Calculator()
{
}


Calculator::~Calculator()
{
}


Vect Calculator::Resultant(std::vector<Vect> extActions)
{
	Vect resultant;

	for (auto it = extActions.begin(); it != extActions.end(); it++)
	{
		resultant = resultant + *it;
	}

	return resultant;
}


Vect Calculator::acceleration(Vect Resultant, double mass)
{
	Vect acc=Vect(0,0,0);
	if (mass > 0)
	{
		acc= Resultant / mass;
	}
	else
	{
		throw std::invalid_argument("MassLess_Particle");
	}
	return acc;
}

Vect Calculator::acceleration(std::vector<Vect> extActions, double mass)
{
	return acceleration(Resultant(extActions), mass);
}

Vect  Calculator::Velocity(Vect Acceleration, Vect currentVelocity, double dt)
{
	//integration of the acceleration gives final speeds
	Vect Velocity = currentVelocity + (CartesianElement)Acceleration*dt;
	return Velocity;
}

Point Calculator::Position(Vect Acceleration, Vect currentVelocity, Point currentPosition, double dt)
{
	//double integration of the acceleration gives final position
	Point position = (CartesianElement)Acceleration*0.5*dt*dt + (CartesianElement)currentVelocity*dt + currentPosition;
	return position;
}
