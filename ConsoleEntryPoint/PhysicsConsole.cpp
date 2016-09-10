// PhysicsConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\SimModule\Calculator.h"
#include "..\SimModule\Geo.h"
#include "..\SimModule\Model.h"
#include <sstream>

const double accuracy = double(1e-10); //approximately the diameter of an hydrogen atom in meter
const double rangeOfInterest = 384467000; //approximately the earth to moon distance


int main()
{
	std::string target = "C:\\Users\\Doz\\Source\\Repos\\Physics_Simulator\\ConsoleEntryPoint\\IOTestFile.txt";

	double FallTime = 10;	//seconds
	double mass = 1;		//kg
	const double earthGravity = 9.81;
	Vect G(0, 0, mass*earthGravity);

	Model M;
	M.addMatPoint(Point(0, 0, 0), Vect(0, 0, 0), mass);
	M.addActionOnPoint(0, G);
	M.addMatPoint(Point(0, 0, 0));
	M.simulate(10, 0.1, target, accuracy);

	std::ostringstream strs;
	strs << 10 << " " << 0 << " " << 0 << " " << 0 << " " << 0.5*earthGravity*FallTime*FallTime
		<< " " << 0 << " " << 0 << " " << earthGravity*FallTime << " " << mass << " " << 1;

	std::string s;
	std::fstream reader(target);

	while (std::getline(reader, s)) {/*just get this damn line*/ };

	return 0;
}