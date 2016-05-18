// PhysicsConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\SimModule\Calculator.h"
#include "..\SimModule\Geo.h"
#include "..\SimModule\Model.h"



int main()
{
	Vect F(10, 0, 0);
	Vect G(0, 10, 0);
	Vect H(0, 0, 10);
	auto VF = std::shared_ptr<ActionOnPoint>(new ActionOnPoint(F, Vect(1, 0, 0), Vect(1, 0, 0), Vect(0, 1, 0),
		Vect(0, 0, 1), Vect::linear, Vect::Vlinear, Vect::Vlinear, Vect::Vlinear));
	auto VG = std::shared_ptr<ActionOnPoint>(new ActionOnPoint(G, Vect(0, 0, 0), Vect(1, 1, 1), Vect(0, 1, 0),
		Vect(0, 0, 0), Vect::Quadratic, Vect::Vlinear, Vect::VQuadratic, Vect::Vlinear));
	auto VH = std::shared_ptr<ActionOnPoint>(new ActionOnPoint(H, Vect(0.9, 9.98, .20), Vect(0, 0, 0), Vect(0, 0, 0),
		Vect(0, 0, 1.1), Vect::constant, Vect::Vlinear, Vect::Vlinear, Vect::Vlinear));

	MaterialPoint M(9, 0, { VF,VG,VH });
	MaterialPointObserver Obs(M, Calculator(), Point(2, 3, 4), Vect(0, 0, 0));

	auto now = Obs.resultant();
	auto ten = Obs.resultant(10);


	return 0;
}