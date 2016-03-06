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
	std::shared_ptr<MechanicalAction> resultant(std::vector<std::shared_ptr<MechanicalAction>> setOfActions);


	Vect centerOfMassAcceleration(Vect resultant, double mass);
	Vect centerOfMassAcceleration(std::vector<MechanicalAction* > extActions, double mass);

	Vect velocityVariationCenterM(Vect acceleration, double dt);
	Vect positionVariationCenterM(Vect acceleration, Vect currentVelocity, double dt);

private:
	double Accuracy;
	double Range;
};