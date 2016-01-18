#include "MaterialElement.h"
#include "Geo.h"
#include <iostream>

//Constructors & destructor-------------------------------
MaterialElement::MaterialElement()
{}

MaterialElement::MaterialElement(Point p, Vect resultantForce, Vect velocity,
	double masse, double charge_ )
{
	Charge = charge_; 	// in Coulomb
	Mass = masse;   	// in kg
	Velocity = velocity;	// m/s
	NetForce = resultantForce;		// Newton
	Position = p;		// m 
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
void MaterialElement::setPosition(Point &P)
{
	Position = P;
}

void MaterialElement::setPosition(double x, double y, double z)
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

void MaterialElement::setResultant(Vect force)
{
	NetForce = force;
}

//Simulation tool-------------------------------------
void MaterialElement::update(double dt) //computes and updates the state of the element at t+dt
{
	Vect a;
	a = getAcceleration();
	updateSpeedandPosition(a, dt);

}

Vect MaterialElement::getAcceleration()
{
	Vect a;
	a.nullify();

	Vect V = NetForce;

	if (Mass != 0)
	{
		a = V / Mass;
	}
	else
	{
		std::cout << "** No mass no accs :-( **" << '\n';
	}

	return a;
}

void MaterialElement::updateSpeedandPosition(Vect a, double dt)
{
	CartesianElement Acceleration = a;
	CartesianElement InitialVelocity = Velocity;

	//double integration of the acceleration gives final position
	Position = Acceleration*0.5*dt*dt + InitialVelocity*dt + Position;

	//integration of the acceleration gives final speeds
	Velocity = InitialVelocity + Acceleration;
}



// ------------------- Material Point ----------------

MaterialPoint::MaterialPoint() {}
MaterialPoint::~MaterialPoint() {}
