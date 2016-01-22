
#include "MaterialElement.h"
#include "Geo.h"
#include "Calculator.h"
#include<vector>
#include <iostream>

//Constructors & destructor-------------------------------
MaterialElement::MaterialElement()
{}

MaterialElement::MaterialElement(Point p, Vect velocity, double mass, double charge_)
{
	Charge = charge_; 		// in Coulomb
	Mass = mass;   			// in kg
	CenterOfMassVelocity = velocity;// m/s
	CenterOfMassPosition = p;	// m 
}

MaterialElement::~MaterialElement()
{}

//Accessors---------------------------------------------
Point * MaterialElement::pointerToPosition()
{
	Point *pos = nullptr;
	pos = &CenterOfMassPosition;
	return pos;
}


double MaterialElement::mass()
{
	return Mass;
}

double MaterialElement::charge()
{
	return Charge;
}

//Display-----------------------------------------------
void MaterialElement::consoleShow()
{
	CenterOfMassPosition.show();
	std::cout << "mass: " << Mass << '\n';
	std::cout << "charge: " << Charge << '\n';
}

//Modifiers----------------------------------------------

void MaterialElement::move(double dx, double dy, double dz)
{
	CenterOfMassPosition.move(dx, dy, dz);
}

void MaterialElement::setMass(double m)
{
	Mass = m;
}

void MaterialElement::setCharge(double c)
{
	Charge = c;
}


// ============================== Material Point ============================================================ 

MaterialPoint::MaterialPoint() {}
MaterialPoint::MaterialPoint(Point G, Vect velocity, double mass, double charge):MaterialElement(G,velocity,mass,charge)
{}
MaterialPoint::~MaterialPoint() {}

void MaterialPoint::addExternalAction(Vect MechanicalAction)
{
	ExternalActions.push_back(MechanicalAction);
}

void MaterialPoint::addExternalAction(Vect F, Torsor T)
{
	addExternalAction(F);
}


//Simulation tool-------------------------------------
Vect MaterialPoint::Acceleration()
{
	Calculator C;
	return C.centerOfMassAcceleration(ExternalActions, mass());
}

void MaterialPoint::updateSpeedandPosition(double dt)
{
	Calculator C;
	CenterOfMassPosition = C.Position(C.centerOfMassAcceleration(ExternalActions, Mass), CenterOfMassVelocity, CenterOfMassPosition, dt);
	CenterOfMassVelocity = C.Velocity(C.centerOfMassAcceleration(ExternalActions, Mass), CenterOfMassVelocity, dt);
}

void MaterialPoint::update(double dt)		//computes and updates the state of the element at t+dt
{
	updateSpeedandPosition(dt);
}


// ============================== Solids Point ============================================================================
Solid::Solid(){}
Solid::Solid(Point G, Vect velocity, double mass, double charge) 
	: MaterialElement(G, velocity, mass, charge)
{}
Solid::~Solid(){}

void Solid::addExternalAction(Torsor MechanicalAction)
{
	ExternalActions.push_back(MechanicalAction);
}

void Solid::addExternalAction(Vect F, Torsor T)
{
	addExternalAction(T);
}

//Simulation tool-------------------------------------

Vect Solid::Acceleration()
{
	Calculator C;
	return C.centerOfMassAcceleration(ExternalActions, mass());
}

void Solid::updateSpeedandPosition(double dt)
{
	Calculator C;
	CenterOfMassPosition = C.Position(C.centerOfMassAcceleration(ExternalActions, Mass), CenterOfMassVelocity, CenterOfMassPosition, dt);
	CenterOfMassVelocity = C.Velocity(C.centerOfMassAcceleration(ExternalActions, Mass), CenterOfMassVelocity, dt);
}

void Solid::update(double dt)		//computes and updates the state of the element at t+dt
{
	updateSpeedandPosition(dt);
}
