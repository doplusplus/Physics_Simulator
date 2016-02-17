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


	//Display
	void show();

	//Algebraic operator
	CartesianElement operator +(const CartesianElement &B);
	CartesianElement operator-();
	CartesianElement operator -(CartesianElement B);

	CartesianElement operator *(double a);			// multiplication by a scalar
	CartesianElement operator /(double a);			// division by a scalar, exception thrown if null 

													//logical operator	
	bool operator ==(const CartesianElement &B);

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

private:
	void move(double dx, double dy, double dz);

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
	Vect operator *(double a);
	bool operator <(Vect C)
	{
		return (X < C.X) && (Y < C.Y) && (Z < C.Z);
	};

	double norm();
	Vect unitVector();
	
	//   member Time functions

	static Vect constant(Vect V, double time) { return V; };
	static Vect linear(Vect V, double time) { return V*time; };
	static Vect timeQuadratic(Vect V, double time) { return V*time*time; };
};












#endif
