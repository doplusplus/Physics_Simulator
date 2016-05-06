#include "Calculator.h"
#include <memory>

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

Vect Calculator::centerOfMassAcceleration(Vect resultant, double mass)const
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

Vect Calculator::velocityVariationCoM(Vect acceleration, double dt) const
{ return acceleration*dt; }

Vect Calculator::positionVariationCoM(Vect acceleration, Vect currentVelocity, double dt)const
{
	Vect DPos = (CartesianElement)acceleration*0.5*dt*dt + (CartesianElement)currentVelocity*dt;
	return DPos;
}