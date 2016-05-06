#include "Geo.h"
#include <iostream>
#include <cmath>

//----------------------------- Cartesian element ------------------------------------
CartesianElement::CartesianElement():X(0),Y(0),Z(0) {}

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
void CartesianElement::show() const
{
	std::cout << "x:" << X << '\n' << "y:" << Y << '\n' << "z:" << Z << '\n';
}

//Algebraic operators
CartesianElement CartesianElement ::operator +(const CartesianElement &B) const
{
	CartesianElement C(X + B.X, Y + B.Y, Z + B.Z);
	return C;
}

CartesianElement CartesianElement ::operator -()const
{
	CartesianElement C;
	C.X = -X;
	C.Y = -Y;
	C.Z = -Z;
	return C;
}

CartesianElement CartesianElement ::operator -(CartesianElement B)const
{
	CartesianElement C;
	C.X = X - B.X;
	C.Y = Y - B.Y;
	C.Z = Z - B.Z;
	return C;
}

CartesianElement CartesianElement ::operator *(double a)const	//multiplication by a scalar
{
	CartesianElement C(X *a, Y *a, Z *a);
	return C;
}

CartesianElement CartesianElement ::operator /(double a)const
{
	if (a == 0)	throw "divideByZero";

	return CartesianElement(X / a, Y / a, Z / a);
}

//logical operator	
bool CartesianElement ::operator ==(const CartesianElement &B)const
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
Vect Vect::operator ^(const Vect &B)const
{
	double x, y, z;
	x = Y*B.Z - Z*B.Y;
	y = Z*B.X - X*B.Z;
	z = X*B.Y - Y*B.X;
	return Vect(x, y, z);
}

double Vect::operator *(const Vect &B)const
{
	double s =
		X*B.X
		+ Y*B.Y
		+ Z*B.Z;
	return s;
}

Vect Vect::operator *(double a)const
{
	return (Vect)((CartesianElement)(*this)*a);
};


// Characteristic elements
double Vect::norm() const
{
	Vect V =*this;
	double sq = V*V;
	sq = sqrt(sq);
	return sq;
}

Vect Vect::unitVector() const
{
	Vect u;
	u = (*this) / norm();
	return u;
}

