#include "Geo.h"
#include <iostream>
#include <cmath>

//----------------------------- Cartesian element ------------------------------------

// Constructors and destructor
CartesianElement::CartesianElement() { X = Y = Z = 0; }

CartesianElement::CartesianElement(double x, double y, double z) 
{
	X = x;
	Y = y;
	Z = z;
}

CartesianElement::~CartesianElement(){}

// Accessors
double CartesianElement::getX() { return X; } //**  double
double CartesianElement::getY() { return Y; } //**
double CartesianElement::getZ() { return Z; } //**

// Display
void CartesianElement::show()
{
	std::cout << "x:" << X << '\n' << "y:" << Y << '\n' << "z:" << Z << '\n';
}

// Modifier
void CartesianElement::set(double x, double y, double z) // place the point a the coordinates (x,y,z)  **
{
	X = x;
	Y = y;
	Z = z;
}

void CartesianElement::set(CartesianElement C)
{
	X = C.X;
	Y = C.Y;
	Z = C.Z;
}

void CartesianElement::nullify() 
{
	X = Y = Z = 0;
}

// Algebraic operators
CartesianElement CartesianElement ::operator +(CartesianElement B)
{
	CartesianElement C(X + B.X, Y + B.Y, Z + B.Z);
	return C;
}

CartesianElement CartesianElement ::operator -()		// returns the opposite element
{
 CartesianElement C;
	C.X = -X;
	C.Y = -Y;
	C.Z = -Z;
 return C;
}

CartesianElement CartesianElement ::operator *(double a)	// multiplication by a scalar
{
	CartesianElement C(X *a, Y *a, Z *a);
	return C;
}

CartesianElement CartesianElement ::operator /(double a)	// division by a scalar **
{
 CartesianElement C;
	if (a == 0)
	{
		C.nullify();
		throw "divideByZero";
	}
	C.set(X / a, Y / a, Z / a);
 return C;
}				

//Logical operator	
bool CartesianElement ::operator ==(CartesianElement B) 
{
	return (X == B.X) && (Y == B.Y) && (Z == B.Z);
}
//--------------------------------------------------------------------------------------------------
//==================================================================================================






//----------------------------------------------- POINT -----------------------------------------------
// Constructors	and destructor
	Point::Point()
	{}
	
	Point::Point(double x,double y, double z):CartesianElement(x,y,z)
	{/*that's pretty it*/}

	Point::Point(CartesianElement C)
	{
		set(C);
	}

	Point::Point(Vect V)  //creates a point at the end of the instance of V starting at the origin
	{
		set(V);
	}

	Point::Point(Point P, Vect V) //creates a point at the end of the instance of V starting at point P
	{
		set(P + V);
	}
	
	Point::~Point()
	{}

//.................................End Point......................................
//================================================================================



//----------------------------------- Vect -------------------------------------
	
// Constructors	and destructor
	Vect::Vect()
	{}
	
	Vect::Vect(double x, double y, double z) : CartesianElement(x, y, z)
	{/*that's pretty it*/}

	Vect::Vect(CartesianElement C)
	{
		set(C);
	}

	Vect::Vect(Point P)
	{
		set(P);
	}

	Vect::Vect(Point start, Point end)
	{
		set(end + (-start));
	}
	
	Vect::~Vect()
	{}
	
	Vect Vect::operator ^( Vect &B ) //produit Vectiel
	{
	 double x, y, z;
		x = getY()*B.getZ()- getZ()*B.getY();
		y = getZ()*B.getX() - getX()*B.getZ();
		z = getX()*B.getY() - getY()*B.getX();
		Vect v(x, y, z);
	 return v;
	}
	
	double Vect::operator *(Vect &B) //dot product
    	{
         double s;
        	s= getX()*B.getX() + getY()*B.getY() + getZ()*B.getZ();
         return s;
    	}


// toolbox
	double Vect::norm()
	{
	double sq = *this * (*this);
		sq = sqrt(sq);
	 return sq;
	}
	
	Vect Vect::unitarized()
    	{
         Vect u;
		u = (*this) / norm();
         return u;
    	}
