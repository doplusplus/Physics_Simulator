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
	//Torsor(Vect resultant, Vect moment);
	~Torsor();

	//Accessors
	Vect VectComponent();
	Vect  moment();
	Point applicationPoint();

	//Display
	void show();

	//Modifiers

	void divideResultant(double d);

	//Transportation
	Vect momentAt(Point P);

	//Operators
	Torsor operator +(Torsor B);

	static Torsor nullTorsor();

private:
	Point	Application;
	Vect	Resultant;
	Vect	Moment;

	void nullify();  //sets the direction to 0

};

#endif