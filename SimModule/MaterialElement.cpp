#include "MaterialElement.h"
#include "Geo.h"
#include "Calculator.h"
#include<vector>
#include <iostream>

//Constructors & destructor-------------------------------
MaterialElement::MaterialElement()
{}

MaterialElement::MaterialElement(Point p, std::vector<Vect> actions, Vect velocity,
	double masse, double charge_)
{
	Charge = charge_; 			// in Coulomb
	Mass = masse;   			// in kg
	Velocity = velocity;		// m/s
	ExternalActions = actions;  //Newton
	Position = p;				// m 
}

MaterialElement::~MaterialElement()
{}

//Accessors---------------------------------------------
Point * MaterialElement::pointerToPosition()
{
	Point *pos = NULL;
	pos = &Position;
	return pos;
}


double MaterialElement::getMass()
{
	return Mass;
}

double MaterialElement::getCharge()
{
	return Charge;
}

//Display-----------------------------------------------
void MaterialElement::consoleShow()
{
	Position.show();
	std::cout << "mass: " << Mass << '\n';
	std::cout << "charge: " << Charge << '\n';
}

//Modifier----------------------------------------------
void MaterialElement::place(Point &P)
{
	Position = P;
}

void MaterialElement::place(double x, double y, double z)
{
	Position.place(x, y, z);
}

void MaterialElement::setMass(double m)
{
	Mass = m;
}

void MaterialElement::setCharge(double c)
{
	Charge = c;
}

void MaterialElement::addExternalAction(Vect MechanicalAction)
{
	ExternalActions.push_back(MechanicalAction);
}

//Simulation tool-------------------------------------
void MaterialElement::update(double dt)		//computes and updates the state of the element at t+dt
{
	updateSpeedandPosition(dt);
}

Vect MaterialElement::Acceleration()
{
	Calculator C;
	return C.acceleration(ExternalActions,Mass);
}

void MaterialElement::updateSpeedandPosition(double dt)
{
	Calculator C;
	Position = C.Position(C.acceleration(ExternalActions, Mass), Velocity, Position, dt);
	Velocity = C.Velocity(C.acceleration(ExternalActions, Mass), Velocity, dt);
}

// ------------------- Material Point ----------------

MaterialPoint::MaterialPoint() {}
MaterialPoint::~MaterialPoint() {}
