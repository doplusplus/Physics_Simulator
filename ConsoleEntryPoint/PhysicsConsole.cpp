// PhysicsConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\SimModule\Calculator.h"
#include "..\SimModule\Geo.h"
#include "..\SimModule\Model.h"

const double accuracy = double(1e-10); //approximately the diameter of an hydrogen atom in meter
const double rangeOfInterest = 384467000; //approximately the earth to moon distance


int main()
{
	Model M;
	std::string target = "C:\\Users\\Doz\\Source\\Repos\\Physics_Simulator\\ConsoleEntryPoint\\IOTestFile.txt";
	M.addMatPoint(Point(0, 0, 0));
	M.simulate(10, 0.1, target, accuracy);
	std::string s;
	std::fstream reader(target);

	std::getline(reader, s); //skip first line
	std::getline(reader, s);

	int a = 2;
	return 0;
}