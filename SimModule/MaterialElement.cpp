#include "MaterialElement.h"
#include "PhysicalElement.h"
#include <iostream>

//Constructors & destructor-------------------------------
MaterialElement::MaterialElement()
{}

MaterialElement::MaterialElement(Point p, Force res, Velocity vel, double masse, double charge_)
{
	Charge = charge_; 	// in Coulomb
	Mass = masse;   	// in kg
	V = vel;			// m/s
	NetForce = res;		// Newton
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

void MaterialElement::setResultant(Force F)
{
	NetForce = F;
}

//Simulation tool-------------------------------------
void MaterialElement::update(double dt) //computes and updates the state of the element at t+dt
{
	Acceleration a;
	a = getAcceleration();
	updateSpeedandPosition(a, dt);

}

Acceleration MaterialElement::getAcceleration()
{
	Acceleration a;
	a.nullify();

	Vect V = NetForce.getDirection();

	if (Mass != 0)
	{
		V = V / Mass;
		a.setDirection(V);
	}
	else
	{
		std::cout << "** No mass no accs :-( **" << '\n';
	}

	return a;
}

void MaterialElement::updateSpeedandPosition(Acceleration a, double dt)
{
	double Vx, Vy, Vz, X, Y, Z;

	//Initial speeds
	Vx = V.getDirection().xComponent();
	Vy = V.getDirection().yComponent();
	Vz = V.getDirection().zComponent();

	//Double integration of the accelerations gives final positions
	X = 0.5*a.getDirection().xComponent()*dt*dt + Vx*dt + Position.xComponent();
	Y = 0.5*a.getDirection().yComponent()*dt*dt + Vy*dt + Position.yComponent();
	Z = 0.5*a.getDirection().zComponent()*dt*dt + Vz*dt + Position.zComponent();
	Position.place(X, Y, Z);

	//integration of the accelerations gives final speeds
	Vx += a.getDirection().xComponent()*dt;
	Vy += a.getDirection().yComponent()*dt;
	Vz += a.getDirection().zComponent()*dt;
	V.setDirection(Vx, Vy, Vz);
}



// ------------------- Material Point ----------------

MaterialPoint::MaterialPoint() {}
MaterialPoint::~MaterialPoint() {}
