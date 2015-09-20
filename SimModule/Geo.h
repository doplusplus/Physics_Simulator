#ifndef GEO_H
#define GEO_H

//------------------------------ CartesianElement-------------------------------------------------

class CartesianElement
{
	private:
		double X;
		double Y;
		double Z;

	public:
		CartesianElement();
		CartesianElement(double x, double y, double z);
		~CartesianElement();

//accessor
	double getX(); //**  double
	double getY(); //**
	double getZ(); //**

//Display
	void show();

//Modifier
	void set(double x,double y, double z);  // places the point a the coordinates (x,y,z)  **
	void set(CartesianElement C);			// changes the coordinates to the C one 
	void nullify();							// sets the point at the origin, to use as initializer **

//Algebraic operator
	CartesianElement operator +( CartesianElement B);	// adds each coordinate together
	CartesianElement operator-();						// reverses the sign of each coodinate 
	CartesianElement operator *( double a);				// multiplication by a scalar
	CartesianElement operator /( double a);				// division by a scalar **

//logical operator	
	bool operator ==(CartesianElement B);
};

class Point;

//--------------------------------- Vect --------------------------------------------------
class Vect : public CartesianElement
{
public:
	Vect();
	Vect(double x, double y, double z);
	Vect(CartesianElement C);
	Vect(Point P);					//creates a vector bringing the origin to P
	Vect(Point start, Point end);	//creates a vector bringing start to end
	~Vect();



	Vect operator ^(Vect &B);		// Vectorial multiplication
	double operator *(Vect &B);	// dot product
	double norm();					//returns the norm of a vector
	Vect unitarized();				//returns a vector of same direction with a norm of 1
};



//--------------------------------- Point --------------------------------------------------
					//forward declaring Vect used in Point class

class Point : public CartesianElement
{

public:
	Point();
	Point(double x, double y, double z);
	Point(CartesianElement C);
	Point(Vect V);						//creates a point at the extremity of the instance of V placed at the origin
	Point(Point P, Vect V);
	~Point();
};
//-----------------------------------------------------------------------------------------




#endif
