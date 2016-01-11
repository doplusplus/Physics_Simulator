#ifndef PhysElem
#define PhysElem

#include "Geo.h"



//****************************************************************************

class InstanciatedVect
{
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
	void nullify();  //sets the direction to 0

	//Operators
	InstanciatedVect operator +(InstanciatedVect&B);



private:
	Point *application;
	Vect  direction;
	bool owns = false;

};

//******************************************************************

class Force : public InstanciatedVect                         //in Newton
{
public:
	//Constructors and destructor
	Force();
	Force(InstanciatedVect V);
	Force(Point &P, Vect V);
	~Force();

	//Display
	void show();

	//Modifier	
	Force operator +(Force &B);
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
	double StartTime;
	double EndTime;
	Force F;
};


#endif
