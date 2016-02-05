#include "Calculator.h"

Calculator::Calculator()
{}
Calculator::~Calculator()
{}

void Calculator::resultant(std::vector<MechanicalAction*> setOfActions, MechanicalAction* result)
{
	result->null();
	for (auto element : setOfActions) { result->add(element, result); }
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

Vect  Calculator::velocityVariation(Vect Acceleration, double dt)
{
	Vect DVel = (CartesianElement)Acceleration*dt;
	return DVel;
}

Vect Calculator::positionVariation(Vect Acceleration, Vect currentVelocity, double dt)
{
	Vect DPos = (CartesianElement)Acceleration*0.5*dt*dt + (CartesianElement)currentVelocity*dt;
	return DPos;
}