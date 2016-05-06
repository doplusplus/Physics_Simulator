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
	~Torsor();

	//Accessors
	Vect vectComponent() const;
	Vect  moment() const;
	Point applicationPoint() const;

	//Display
	void show() const;

	//Modifiers
	void divideResultant(double d);

	//Transportation
	Vect momentAt(Point P) const;

	//Operators
	Torsor operator +(Torsor B) const;
	bool operator ==(Torsor B) const;

	static Torsor nullTorsor();

private:
	Point	Application;
	Vect	Resultant;
	Vect	Moment;

	void nullify();  //sets the resultant to 0

};

#endif