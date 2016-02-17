#include "Calculator.h"

Calculator::Calculator()
{}

Calculator::Calculator(double accuracy, double amplitude) 
{
	Accuracy = accuracy;
	Range = amplitude;
};

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

Vect  Calculator::centerOfMassAcceleration(std::vector<MechanicalAction* > extActions, double mass)
{
	MechanicalAction* res = extActions.back()->copy();
	resultant(extActions, res);
	Vect v = res->force();
	delete res;
	return centerOfMassAcceleration(v, mass);
};

Vect  Calculator::velocityVariationCenterM(Vect Acceleration, double dt)
{
	Vect DVel = (CartesianElement)Acceleration*dt;
	return DVel;
}

Vect Calculator::positionVariationCenterM(Vect Acceleration, Vect currentVelocity, double dt)
{
	Vect DPos = (CartesianElement)Acceleration*0.5*dt*dt + (CartesianElement)currentVelocity*dt;
	return DPos;
}