#include "Geo.h"
#include <iostream>
#include <cmath>

//------------------------------ GENERAL -----------------------------------------
//--------------------------------------//
/**/ const double geoAccuracy = 1E-10; /**/
//--------------------------------------//

bool geoEqual(double a, double b)
{
	return abs(a - b) < geoAccuracy;
}

CartesianElement operator +(const CartesianElement &A, const CartesianElement &B)
{
	CartesianElement C(A.X + B.X, A.Y + B.Y, A.Z + B.Z);
	return C;
}

CartesianElement operator -(const CartesianElement &A, const CartesianElement &B)
{
	CartesianElement C;
	C.X = A.X - B.X;
	C.Y = A.Y - B.Y;
	C.Z = A.Z - B.Z;
	return C;
}

bool operator <(const CartesianElement &left, const CartesianElement &right)
{
	return (left.X < right.X) && (left.Y < right.Y) && (left.Z < right.Z);
}


bool operator ==(const CartesianElement &left, const CartesianElement &right)
{
	return geoEqual(left.X, right.X)&& geoEqual(left.Y, right.Y) && geoEqual(left.Z, right.Z);
}


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



CartesianElement CartesianElement ::operator -()const
{
	CartesianElement C;
	C.X = -X;
	C.Y = -Y;
	C.Z = -Z;
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

Vect Vect::multiplyMemberwise(const Vect & B) const
{
	return Vect(X*B.X,Y*B.Y,Z*B.Z);
}

Vect Vect::absMultiplyMemberwise(const Vect & B) const
{
	return Vect(X*abs(B.X), Y*abs(B.Y), Z*abs(B.Z));
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

std::function<Vect(Vect, double)> operator+ (std::function<Vect(Vect, double)> a, std::function<Vect(Vect, double)> b)
{
	std::function<Vect(Vect, double)> sum = [a , b ](Vect v, double d){return a(v, d) + b(v, d); };
	return sum;
}

std::function<Vect(Vect, Vect)> operator+ (std::function<Vect(Vect, Vect)> a, std::function<Vect(Vect, Vect)> b)
{
	std::function<Vect(Vect, Vect)> sum = [a, b](Vect v, Vect d) {return a(v, d) + b(v, d); };
	return sum;
}