#ifndef GEO_H
#define GEO_H

#include <vector>

//==================================== CartesianElement ====================================
class CartesianElement
{
public:
	CartesianElement();
	CartesianElement(double x, double y, double z);
	CartesianElement(const CartesianElement &C);
	virtual ~CartesianElement();

	//accessor
	double xComponent() { return X; };
	double yComponent() { return Y; };
	double zComponent() { return Z; };

	//Display
	void show();
	
	//Modifier
	void move(double dx, double dy, double dz);
	void nullify();

	//Algebraic operator
	CartesianElement operator +(const CartesianElement &B);
	CartesianElement operator-();
	CartesianElement operator -(CartesianElement B);

	CartesianElement operator *(double a);			// multiplication by a scalar
	CartesianElement operator /(double a);			// division by a scalar, exception thrown if null 

//logical operator	
	bool operator ==(CartesianElement B);

protected:
	double X;
	double Y;
	double Z;
};

//==================================== Point ====================================
class Vect;
class Point : public CartesianElement
{
public:
	Point();
	Point(double x, double y, double z);
	Point(CartesianElement C);
	Point(Vect V);				//At the non null extremity of V 
	Point(Point P, Vect V);		//At the image of P translated by V 
	~Point();
};

//==================================== Vect ====================================

class Vect : public CartesianElement
{
public:
	Vect();
	Vect(double x, double y, double z);
	Vect(CartesianElement C);
	Vect(Point A, Point B);
	~Vect();

	Vect operator ^(Vect &B);		// Vectorial multiplication
	double operator *(Vect &B);		// dot product	
	Vect unitVector();
	double norm();
};

#endif
