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

CartesianElement::CartesianElement(const CartesianElement &C)
{
	X = C.X;
	Y = C.Y;
	Z = C.Z;
}

CartesianElement::~CartesianElement() {}

//Displays
void CartesianElement::show()
{
	std::cout << "x:" << X << '\n' << "y:" << Y << '\n' << "z:" << Z << '\n';
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

CartesianElement CartesianElement ::operator -(CartesianElement B)
{
	CartesianElement C;
	C.X = X - B.X;
	C.Y = Y - B.Y;
	C.Z = Z - B.Z;
	return C;
}

CartesianElement CartesianElement ::operator *(double a)	//multiplication by a scalar
{
	CartesianElement C(X *a, Y *a, Z *a);
	return C;
}

CartesianElement CartesianElement ::operator /(double a)
{
	if (a == 0)	throw "divideByZero";

	return CartesianElement(X / a, Y / a, Z / a);
}

//logical operator	
bool CartesianElement ::operator ==(const CartesianElement &B)
{
	return (X == B.X) && (Y == B.Y) && (Z == B.Z);
}


//----------------------------------------------------------------------------------------------------
//--------------------------------POINT---------------------------------------------------------------
Point::Point()
{}

Point::Point(double x, double y, double z) :CartesianElement(x, y, z)
{}

Point::Point(CartesianElement C) : CartesianElement(C)
{}

Point::Point(Vect V) : CartesianElement(V)
{}

Point::Point(Point P, Vect V) : CartesianElement(P + V)
{}

Point::~Point()
{}

void Point::move(double dx, double dy, double dz)
{
	X += dx;
	Y += dy;
	Z += dz;
}
//================================================================================
//----------------------------------- Vect -------------------------------------

//constructors	and destructor
Vect::Vect()
{}

Vect::Vect(double x, double y, double z) :CartesianElement(x, y, z)
{}

Vect::Vect(CartesianElement C) : CartesianElement(C)
{}

Vect::Vect(Point A, Point B) : Vect(B - A)
{}

Vect::~Vect()
{}

//Operators
Vect Vect::operator ^(Vect &B)
{
	double x, y, z;
	x = Y*B.Z - Z*B.Y;
	y = Z*B.X - X*B.Z;
	z = X*B.Y - Y*B.X;
	return Vect(x, y, z);
}

double Vect::operator *(Vect &B)
{
	double s =
		X*B.X
		+ Y*B.Y
		+ Z*B.Z;
	return s;
}

Vect Vect::operator *(double a)
{
	return (Vect)((CartesianElement)(*this)*a);
};


// Characteristic elements
double Vect::norm()
{
	double sq = *this * *this;
	sq = sqrt(sq);
	return sq;
}

Vect Vect::unitVector()
{
	Vect u;
	u = (*this) / norm();
	return u;
}

