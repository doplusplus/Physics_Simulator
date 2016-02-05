// PhysicsConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\SimModule\Calculator.h"


int main()
{
	Calculator Calc;
	ActionOnPoint *A = new ActionOnPoint(Vect(1, 1, 1));
	ActionOnPoint *B = new ActionOnPoint(Vect(1, 1, 1));
	ActionOnPoint *C = new ActionOnPoint(Vect(1, 1, 1));
	ActionOnPoint *result = new ActionOnPoint();

	std::vector<MechanicalAction*> V;

	V.push_back(A);
	V.push_back(B);
	V.push_back(C);
	Calc.resultant(V, result);

	result->show();
	return 0;
}