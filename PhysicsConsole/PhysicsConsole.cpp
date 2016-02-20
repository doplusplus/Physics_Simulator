// PhysicsConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\SimModule\Calculator.h"
#include "..\SimModule\Geo.h"
#include "..\SimModule\Model.h"

int main()
{
	/*
	Model M;
	M.addMatPoint(Point(0, 0, 0));
	M.addActionOnPoint(0, Vect(1, 2, 4));
	//M.showHandlers();
	
	
	M.setDomain(0, 0.0001, 123313131);
	M.simulate(10, 1);
	M.showScene();
	/**/

	
	double mass = 7;
	double timeStep = 0.1;

	Point P(0, 0, 0);
	MaterialPoint M(P, Vect(0, 0, 0), mass), clone = M;
	Vect F(1, 1, 1);
	Calculator C;
	ActionOnPoint *A= new ActionOnPoint(Vect(0,0,0));

	MaterialPointHandler H(&M, &C);
	H.addAction(A);
	H.forward(timeStep);

	H.show();
	clone.consoleShow();



	return 0;
}