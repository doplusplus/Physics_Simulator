#include "Torsor.h"
#include <iostream>

//-------------------------- Instanciated Vector ------------------------------------

//Constructors and destructor
Torsor::Torsor()
{
	nullify();
}

Torsor::Torsor(const Torsor &Iv)
{
	Application = Iv.Application;
	Resultant = Iv.Resultant;
	Moment = Iv.Moment;
}

Torsor::Torsor(Point P, Vect force, Vect moment)
{
	Application = P;
	Resultant = force;
	Moment = moment;
}

/*Torsor::Torsor(Vect force, Vect moment)
{
	Resultant = force;
	Moment = moment;
}
*/

Torsor::~Torsor()
{
}

//Accessors
Vect Torsor::VectComponent() { return Resultant; }
Vect Torsor::moment() { return Moment; }
Point Torsor::applicationPoint() { return Application; }

//Display
void Torsor::show()
{
	std::cout << "Point" << '\n';
	Application.show();

	std::cout << "Resultant:" << '\n';
	Resultant.show();

	std::cout << "Moment:" << '\n';
	Moment.show();
}

//Modifiers
void Torsor::nullify()
{
	Resultant = Vect(0, 0, 0);
	Moment = Vect(0, 0, 0);
}


void Torsor::divideResultant(double d)
{
	Resultant = Resultant / d;
}

//Vector transport
Vect Torsor::momentAt(Point P)
{
	Vect M = Moment + (Vect(P, Application) ^ Resultant);
	return M;
}

Torsor Torsor::operator +(Torsor B)
{
	Torsor I;
	Point P = I.Application = Application + B.Application;

	I.Resultant = Resultant + B.Resultant;
	I.Moment = momentAt(P) + B.momentAt(P);

	return I;
}

Torsor Torsor::nullTorsor()
{
	return Torsor();
}
