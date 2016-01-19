#pragma once

#include <iostream>
#include <vector>

#include "Scene.h"
#include "Geo.h"

class Calculator
{
public:
	Calculator();
	~Calculator();

	Vect Resultant(std::vector<Vect> extActions);

	
	Vect acceleration(Vect Resultant, double mass);
	
	Vect acceleration(std::vector<Vect> extActions, double mass);

	Vect  Velocity(Vect Acceleration, Vect currentVelocity, double dt);
	Point Position(Vect Acceleration, Vect currentVelocity, Point currentPosition, double dt);
	

private:
	Scene * SimScene;

};
