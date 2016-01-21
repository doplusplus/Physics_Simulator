#include "Geo.h"
#include <iostream>
#include <cmath>

//----------------------------- Cartesian element ------------------------------------
CartesianElement::CartesianElement() { X = Y = Z = 0; }

CartesianElement::CartesianElement(double x, double y, double z)
{
	X = x;
	Y = y;
	Z = z;
}

CartesianElement::~CartesianElement() {}

//Accessors
double CartesianElement::xComponent() { return X; }
double CartesianElement::yComponent() { return Y; }
double CartesianElement::zComponent() { return Z; }

//Displays
void CartesianElement::show()
{
	std::cout << "x:" << X << '\n' << "y:" << Y << '\n' << "z:" << Z << '\n';
}

//Modifiers
void CartesianElement::place(double x, double y, double z)
{
	X = x;
	Y = y;
	Z = z;
}

void CartesianElement::place(CartesianElement C)
{
	X = C.X;
	Y = C.Y;
	Z = C.Z;
}

void CartesianElement::nullify()
{
	X = Y = Z = 0;
}

//Algebraic operators
CartesianElement CartesianElement ::operator +(const CartesianElement &B)
{
	CartesianElement C(X + B.X, Y + B.Y, Z + B.Z);
	return C;
}

CartesianElement CartesianElement ::operator -()
{
	CartesianElement C;
	C.X = -X;
	C.Y = -Y;
	C.Z = -Z;
	return C;
}

CartesianElement CartesianElement ::operator *(double a)	//multiplication by a scalar
{
	CartesianElement C(X *a, Y *a, Z *a);
	return C;
}

CartesianElement CartesianElement ::operator /(double a)
{
	CartesianElement C;
	if (a == 0)
	{
		C.nullify();
		throw "divideByZero";
	}
	C.place(X / a, Y / a, Z / a);
	return C;
}

//logical operator	
bool CartesianElement ::operator ==(CartesianElement B)
{
	return (X == B.X) && (Y == B.Y) && (Z == B.Z);
}



//----------------------------------------------------------------------------------------------------
//--------------------------------POINT---------------------------------------------------------------
Point::Point()
{}

Point::Point(double x, double y, double z) :CartesianElement(x, y, z)
{}

Point::Point(CartesianElement C)
{
	place(C);
}

Point::Point(Vect V)
{
	place(V);
}

Point::Point(Point P, Vect V)
{
	place(P + V);
}

Point::~Point()
{}



//.................................End Point......................................
//================================================================================



//================================================================================
//----------------------------------- Vect -------------------------------------

//constructors	and destructor
Vect::Vect()
{}

Vect::Vect(double x, double y, double z) :CartesianElement(x, y, z)
{}

Vect::Vect(CartesianElement C)
{
	place(C);
}


Vect::~Vect()
{}

//Operators
Vect Vect::operator ^(Vect &B)
{
	double x, y, z;
	x = yComponent()*B.zComponent() - zComponent()*B.yComponent();
	y = zComponent()*B.xComponent() - xComponent()*B.zComponent();
	z = xComponent()*B.yComponent() - yComponent()*B.xComponent();
	return Vect(x, y, z);
}

double Vect::operator *(Vect &B)
{
	double s =
		  xComponent()*B.xComponent()
		+ yComponent()*B.yComponent()
		+ zComponent()*B.zComponent();
	return s;
}


// Characteristic elements
double Vect::norm()
{
	double sq = *this * (*this);
	sq = sqrt(sq);
	return sq;
}

Vect Vect::unitVector()
{
	Vect u;
	u = (*this) / norm();
	return u;
}
