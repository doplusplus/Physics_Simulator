
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
void MaterialElement::consoleShow() const
{
	CenterOfMassPosition.show();
	std::cout << "mass: " << Mass << '\n';
	std::cout << "charge: " << Charge << '\n';
}

//Modifier----------------------------------------------

void MaterialElement::move(Vect dP)
{
	CenterOfMassPosition = CenterOfMassPosition + dP;
}
void MaterialElement::changeVelocity(Vect dS)
{
	CenterOfMassVelocity = CenterOfMassVelocity + dS;
}

// ================================== Material Point==================================================================== 
MaterialPoint::MaterialPoint(Point G, Vect velocity, double mass, double charge):MaterialElement(G,velocity,mass,charge)
{}
MaterialPoint::~MaterialPoint() {}


// ================================== Solids Point ==================================================================== 
Solid::Solid(Point G, Vect velocity, double mass, double charge):MaterialElement(G,velocity,mass,charge)
{
}
Solid::~Solid() {}
