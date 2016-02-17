
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


// ================================== Solids Point ==================================================================== 
Solid::Solid() :MaterialElement()
{}
Solid::~Solid() {}
