#pragma once

#include <iostream>
#include <vector>

#include "Scene.h"
#include "Geo.h"
#include "Torsor.h"


class Calculator
{
public:
	Calculator();
	~Calculator();

	Vect resultant(std::vector<Vect> extActions);
	Vect resultant(std::vector<Torsor> extActions);

	Vect centerOfMassAcceleration(Vect Resultant, double mass);
	Vect centerOfMassAcceleration(Torsor Resultant, double mass);
	Vect centerOfMassAcceleration(std::vector<Vect> extActions, double mass);
	Vect centerOfMassAcceleration(std::vector<Torsor> extActions, double mass);

	Vect  velocity(Vect Acceleration, Vect currentVelocity, double dt);
	Point position(Vect Acceleration, Vect currentVelocity, Point currentPosition, double dt);

	Vect  velocityVariation(Vect Acceleration, double dt);

	Point positionVariation(Vect Acceleration, Vect currentVelocity, double dt);


private:
	Scene * SimScene;

};
