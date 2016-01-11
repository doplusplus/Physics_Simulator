#ifndef GEO_H
#define GEO_H

#include <vector>

//------------------------------ CartesianElement-------------------------------------------------

class CartesianElement
{
public:
	CartesianElement();
	CartesianElement(double x, double y, double z);
	~CartesianElement();

	//accessor
	double xComponent();
	double yComponent();
	double zComponent();

	//Display
	void show();

	//Modifier
	void place(double x, double y, double z);
	void place(CartesianElement C);					// places on C
	void nullify();

	//Algebraic operator
	CartesianElement operator +(const CartesianElement &B);
	CartesianElement operator-();
	CartesianElement operator *(double a);			// multiplication by a scalar
	CartesianElement operator /(double a);			// division by a scalar, exception thrown if null 

//logical operator	
	bool operator ==(CartesianElement B);

private:
	double X;
	double Y;
	double Z;
};



//--------------------------------- Vect --------------------------------------------------
class Vect : public CartesianElement
{
public:
	Vect();
	Vect(double x, double y, double z);
	Vect(CartesianElement C);
	~Vect();

	Vect operator ^(Vect &B);		// Vectorial multiplication
	double operator *(Vect &B);		// dot product
	Vect unitVector();
	double norm();

};



//--------------------------------- Point --------------------------------------------------

class Point : public CartesianElement
{
public:
	Point();
	Point(double x, double y, double z);
	Point(CartesianElement C);
	Point(Vect V);				//At the non null extremity of V 
	Point(Point P, Vect V);		//At the image of P translated by V 
	~Point();


	void trackAsHeap();			// tracking points allocated on the heap
	static void clearHeapPoints();
	static void showHeapPoints();
	static double PointsHeapSize();

private:
	static std::vector< Point* > OnHeap;
};
//-----------------------------------------------------------------------------------------


#endif
