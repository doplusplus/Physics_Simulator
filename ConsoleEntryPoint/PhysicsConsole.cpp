// PhysicsConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\SimModule\Calculator.h"
#include "..\SimModule\Geo.h"
#include "..\SimModule\Model.h"



int main()
{
	double expectedZ = 490.5;
	double mass = 10;
	double duration = 10; //s
	double accuracy = 1;
	double accuracy2 = 1E-2;
	double accuracy3 = 1E-5;
	double accuracy4 = 1E-7;
	double accuracy5 = 1E-10;

	Vect F(0, 0, 98.1);
	MaterialPoint M(mass, 0, { std::shared_ptr<ActionOnPoint>(new ActionOnPoint(F)) });
	MaterialPointObserver Obs(M, Calculator(), Point(0, 0, 0), Vect(0, 0, 0));
	//MaterialPointObserver Obs2=Obs, Obs3 = Obs, Obs4 = Obs, Obs5 = Obs;

	Obs.increment(duration, accuracy5);
	
	/*Obs2.increment(duration, accuracy2);
	Obs3.increment(duration, accuracy3);
	Obs4.increment(duration, accuracy4);
	Obs5.increment(duration, accuracy5);
	*/
	double e = abs(Obs.position().coordStream()[2] - expectedZ);
	/*double e2 = abs(Obs2.position().coordStream()[2] - expectedZ);
	double e3 = abs(Obs3.position().coordStream()[2] - expectedZ);
	double e4 = abs(Obs4.position().coordStream()[2] - expectedZ);
	double e5 = abs(Obs5.position().coordStream()[2] - expectedZ);
	*/


	return 0;
}