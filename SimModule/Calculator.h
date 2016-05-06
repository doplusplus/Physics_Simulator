#pragma once

#include <iostream>
#include <vector>
#include "Scene.h"
#include "Geo.h"
#include "Torsor.h"
#include "MechanicalAction.h"

class Calculator
{
public:
	Calculator();
	Calculator(double accuracy, double range);
	~Calculator();

	void resultant(std::vector<MechanicalAction*> setOfT, MechanicalAction* result);
	
	Vect centerOfMassAcceleration(Vect resultant, double mass) const;
	Vect centerOfMassAcceleration(std::vector<MechanicalAction* > extActions, double mass);
	
	Vect positionVariationCoM(Vect acceleration, Vect currentVelocity, double dt)const;
	Vect velocityVariationCoM(Vect acceleration, double dt)const;

private:
	double Accuracy;
	double Range;

};