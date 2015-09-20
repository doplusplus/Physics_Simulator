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
	InstanciatedVect(Vect V);
	InstanciatedVect(Point P, Vect V);
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

class Force : public InstanciatedVect                         //in Newton
{
	public:
	//Constructors and destructor
	Force();
	Force(Point P, Vect V);
	~Force();

	//Display
	void show();

	//Modifier	
    Force operator +(Force B);
    Force operator -();

};

class Acceleration : public InstanciatedVect                      // m/s²
{
	private:
    Point  *application;
	Vect direction;
	

	public:
	//Constructors and destructor
	Acceleration();
	Acceleration(Force F, double mass);				// valid for point element
	~Acceleration();
	
	//Display
	void show();
};

class Velocity : public InstanciatedVect                     // m/s
{
	public:
	//Constructors and destructor
	Velocity();
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
