#ifndef PhysElem
#define PhysElem

#include "Geo.h"



//****************************************************************************

class InstanciatedVect
{
private:
	Point * application;
	Vect  direction;

public:
	//Constructors and destructor
	InstanciatedVect();
	InstanciatedVect(const InstanciatedVect &Iv);
	InstanciatedVect(Vect V);
	InstanciatedVect(Point &P, Vect V);
	~InstanciatedVect();

	//Accessors
	Vect getDirection(); //**
	Point *getApplicationPoint(); //returns a pointer to the application point**

	//Display
	void show();

	//Modifier
	void setDirection(Vect V);     //**
	void setDirection(double x, double y, double z);
	void setApplication(Point *P);
	void nullify();
};

//******************************************************************

class Force : public InstanciatedVect    	//in Newton
{
public:
	//Constructors and destructor
	Force();
	Force(Point &P, Vect V);
	~Force();

	//Display
	void show();

	//Modifier	
	void operator +(Force &B);	 	//adds up the right end of the + to the left one; placing the force in the middle
	Force operator -();			//returns opposite force

};

class Acceleration : public InstanciatedVect                      // m/s²
{
public:
	//Constructors and destructor
	Acceleration();
	Acceleration(Point &P, Vect V);
	Acceleration(Force &Resultant, double mass);				// valid for point element
	~Acceleration();

	//Display
	void show();
};

class Velocity : public InstanciatedVect                     // m/s
{
public:
	//Constructors and destructor
	Velocity();
	Velocity(Point &P, Vect V);
	~Velocity();

	//Display
	void show();
};

struct timedForce  //all public
{
	double startTime;
	double endTime;
	Force F;
};


#endif
