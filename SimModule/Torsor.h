#ifndef TORSOR
#define TORSOR

#include "Geo.h"



//****************************************************************************

class Torsor
{
public:
	//Constructors and destructor
	Torsor();
	Torsor(const Torsor &Iv);
	Torsor(Point P, Vect resultant, Vect moment);
	Torsor(Vect resultant, Vect moment);
	~Torsor();

	//Accessors
	Vect  resultant(); //**
	Vect  moment();
	Point applicationPoint();

	//Display
	void show();

	//Modifiers
	void nullify();  //sets the direction to 0
	void divideResultant(double d);
	
	//Transportation
	Vect momentAt(Point P);

	//Operators
	Torsor operator +(Torsor B);

private:
	Point	Application;
	Vect	Resultant;
	Vect	Moment;

};

#endif
