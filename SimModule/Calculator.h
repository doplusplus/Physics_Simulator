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
	~Calculator();

	void resultant(std::vector<MechanicalAction*> setOfT, MechanicalAction* result);
	
	Vect centerOfMassAcceleration(Vect Resultant, double mass);
	Vect centerOfMassAcceleration(std::vector<MechanicalAction* > extActions, double mass) {};

	Vect velocityVariation(Vect Acceleration, double dt);
	Vect positionVariation(Vect Acceleration, Vect currentVelocity, double dt);
};