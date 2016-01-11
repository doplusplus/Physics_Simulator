#include "PhysicalElement.h"
#include <iostream>

//-------------------------- Instanciated Vector ------------------------------------

//Constructors and destructor
InstanciatedVect::InstanciatedVect()
{
}


InstanciatedVect::InstanciatedVect(const InstanciatedVect &Iv)
{
	application = Iv.application;
	direction = Iv.direction;
}


InstanciatedVect::InstanciatedVect(Vect V)
{
	Point P;
	P.nullify();
	application = &P;
	direction = V;
}

InstanciatedVect::InstanciatedVect(Point &P, Vect V)
{
	application = &P;
	direction = V;
}

InstanciatedVect::~InstanciatedVect()
{
}

//Accessors
Vect InstanciatedVect::getDirection() { return direction; }

Point *InstanciatedVect::getApplicationPoint()
{
	return application;
}

//Display
void InstanciatedVect::show()
{
	std::cout << "Direction:" << '\n';
	direction.show();

	std::cout << "Application point:" << '\n';
	application->show();
}

//Modifier
void InstanciatedVect::setDirection(Vect V)
{
	direction.place(V);
}

void InstanciatedVect::setDirection(double x, double y, double z)
{
	direction.place(x, y, z);
}


void InstanciatedVect::setApplication(Point *P)
{
	application = P;
}

void InstanciatedVect::nullify()
{
	direction.nullify();
}

InstanciatedVect InstanciatedVect::operator +(InstanciatedVect &B)
{
	InstanciatedVect I;
	
	Point *P = new Point(); P->trackAsHeap();
	*P = (*application + *B.application)*0.5;
	I.setDirection(getDirection()+ B.getDirection());
	I.setApplication(P);

	return I;
}



//-------------------------- Forces ------------------------------------

	//Constructors and destructor
Force::Force()
{}

Force::Force(Point &P, Vect V) : InstanciatedVect(P, V)
{}

Force::Force(InstanciatedVect V)
{
	this->setApplication( V.getApplicationPoint());
	this->setDirection(V.getDirection());
}

Force::~Force()
{}

//Display
void Force::show()
{
	std::cout << "   ---- Force ----   " << '\n';
	InstanciatedVect::show();
}

Force Force::operator +(Force &B)
{
	Force F = (InstanciatedVect)(*this) + B;
	return F;
}

Force Force::operator -()
{
	Force F;
	F.setApplication(this->getApplicationPoint());
	F.setDirection(-this->getDirection());
	return F;
}



//-------------------------- Acceleration ------------------------------------
//Constructors and destructor
Acceleration::Acceleration()
{}

Acceleration::Acceleration(Point &P, Vect V) : InstanciatedVect(P, V)
{
}

Acceleration::Acceleration(Force &Resultant, double mass) : InstanciatedVect(*(Resultant.getApplicationPoint()), Resultant.getDirection() / mass)
{
	//returns the linear acceleration of the center of gravity
	//of an object given its mass and resultant	
}

Acceleration::~Acceleration()
{}

//Display
void Acceleration::show()
{
	std::cout << "   ---- Acceleration ----   " << '\n';
	InstanciatedVect::show();
}

//-------------------------- Velocity ------------------------------------
//Constructors and destructor
Velocity::Velocity()
{}

Velocity::Velocity(Point &P, Vect V) : InstanciatedVect(P, V)
{
}

Velocity::~Velocity()
{}

//Display
void Velocity::show()
{
	std::cout << "   ---- Velocity ----   " << '\n';
	InstanciatedVect::show();
}
