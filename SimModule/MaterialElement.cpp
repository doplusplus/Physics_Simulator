
#include "MaterialElement.h"
#include "Geo.h"
#include "Calculator.h"
#include<vector>
#include <iostream>

//Constructors & destructor-------------------------------

MaterialElement::MaterialElement(Point p, Vect velocity, double mass, double charge_)
{
	Charge = charge_; 					// in Coulomb
	Mass = mass;   						// in kg
	CenterOfMassVelocity = velocity;	// m/s
	CenterOfMassPosition = p;			// m 
}

MaterialElement::~MaterialElement()
{}

//Accessors---------------------------------------------
/*Point * MaterialElement::pointerToPosition()
{
	Point *pos = nullptr;
	pos = &CenterOfMassPosition;
	return pos;
}*/
/*
double MaterialElement::mass()
{
	return Mass;
}


double MaterialElement::charge()
{
	return Charge;
}
*/

//Display-----------------------------------------------
void MaterialElement::consoleShow()
{
	CenterOfMassPosition.show();
	std::cout << "mass: " << Mass << '\n';
	std::cout << "charge: " << Charge << '\n';
}

//Modifier----------------------------------------------

void MaterialElement::move(Vect dP)
{
	CenterOfMassPosition = Vect(CenterOfMassPosition, dP);
}
void MaterialElement::changeVelocity(Vect dS)
{
	CenterOfMassVelocity = CenterOfMassVelocity + dS;
}

bool MaterialElement::operator ==(const MaterialElement &B)
{
	return B.Charge == Charge && B.Mass == Mass
		&& CenterOfMassPosition == B.CenterOfMassPosition
		&& CenterOfMassVelocity == B.CenterOfMassVelocity;
}

// ================================== Material Point==================================================================== 
MaterialPoint::MaterialPoint() :MaterialElement()
{}
MaterialPoint::~MaterialPoint() {}
/*
void MaterialPoint::addExternalAction(Vect MechanicalAction)
{
	//	ExternalActions.push_back(MechanicalAction);
}

void MaterialPoint::addExternalAction(Vect F, Torsor T)
{
	addExternalAction(F);
}
*/


//Simulation tool-------------------------------------

/*
void MaterialPoint::updateSpeedandPosition(double dt,Calculator C)
{
	//Vect accel = C.centerOfMassAcceleration(ExternalActions, Mass);

//	CenterOfMassPosition = C.positionVariation(accel, CenterOfMassVelocity, dt) + CenterOfMassPosition;
//	CenterOfMassVelocity = C.velocityVariation(accel, dt) + CenterOfMassVelocity;
}
*/
void MaterialPoint::update(double dt)		//computes and updates the state of the element at t+dt
{
	//	updateSpeedandPosition(dt);
}

// ================================== Solids Point ==================================================================== 
Solid::Solid() :MaterialElement()
{}
Solid::~Solid() {}

void Solid::addExternalAction(Torsor MechanicalAction)
{
	//ExternalActions.push_back(MechanicalAction);
}

void Solid::addExternalAction(Vect F, Torsor T)
{
	addExternalAction(T);
}

//Simulation tool-------------------------------------
/*
void Solid::updateSpeedandPosition(double dt)
{
	Calculator C;
//	CenterOfMassPosition = C.position(C.centerOfMassAcceleration(ExternalActions, Mass), CenterOfMassVelocity, CenterOfMassPosition, dt);
//	CenterOfMassVelocity = C.velocity(C.centerOfMassAcceleration(ExternalActions, Mass), CenterOfMassVelocity, dt);
}

void Solid::update(double dt)		//computes and updates the state of the element at t+dt
{
	updateSpeedandPosition(dt);
}
*/