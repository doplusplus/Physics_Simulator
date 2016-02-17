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

	const double LOWEST = std::numeric_limits<double>::lowest();
	const double MIN = std::numeric_limits<double>::min();
	const double MAX = std::numeric_limits<double>::max();
	
	const double accuracy = double(1e-10); //approximately the diameter of an hydrogen atom in meter
	const double rangeOfInterest = 384467000; //approximately the earth to oon distance


	Vect l(-rangeOfInterest, accuracy, rangeOfInterest);
	std::cout << (l.unitVector() * l) << '\n';
	std::cout<< l.norm()<<'\n';

	std::cout << (l.unitVector() * l) - l.norm() << '\n';


	return 0;
}