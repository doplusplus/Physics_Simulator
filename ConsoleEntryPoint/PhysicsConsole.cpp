// PhysicsConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\SimModule\Calculator.h"
#include "..\SimModule\Geo.h"
#include "..\SimModule\Model.h"
#include <sstream>
#include <iostream>
#include <chrono>

const double accuracy = double(1e-10); //approximately the diameter of an hydrogen atom in meter
const double rangeOfInterest = 384467000; //approximately the earth to moon distance

int main()
{

	Model M;
	Point P(0, 0, 0);
	Vect v(0, 0, 0);
	M.addMatPoint(P, v, 2);

	Vect F(10, 10, 10);
	M.addActionOnPoint(0, F);

	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	M.increment(0.5, 0.1);
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	std::cout << duration<<"\n";

	t1 = std::chrono::high_resolution_clock::now();
	M.increment(0.5, 0.1);
	t2 = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	std::cout << duration << "\n";

	t1 = std::chrono::high_resolution_clock::now();
	M.increment(0.5, 0.1);
	t2 = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	std::cout << duration << "\n";

	t1 = std::chrono::high_resolution_clock::now();
	M.increment(0.5, 0.1);
	t2 = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	std::cout << duration << "\n";

	t1 = std::chrono::high_resolution_clock::now();
	M.increment(0.5, 0.1);
	t2 = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	std::cout << duration << "\n";

	t1 = std::chrono::high_resolution_clock::now();
	M.increment(0.5, 0.1);
	t2 = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	std::cout << duration << "\n";

	t1 = std::chrono::high_resolution_clock::now();
	M.increment(0.5, 0.1);
	t2 = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	std::cout << duration << "\n";

	t1 = std::chrono::high_resolution_clock::now();
	M.increment(0.5, 0.1);
	t2 = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	std::cout << duration << "\n";

	t1 = std::chrono::high_resolution_clock::now();
	M.increment(0.5, 0.1);
	t2 = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	std::cout << duration << "\n";

	t1 = std::chrono::high_resolution_clock::now();
	M.increment(0.5, 0.1);
	t2 = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	std::cout << duration << "\n";

	t1 = std::chrono::high_resolution_clock::now();
	M.increment(0.5, 0.1);
	t2 = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	std::cout << duration << "\n";

	t1 = std::chrono::high_resolution_clock::now();
	M.increment(0.5, 0.1);
	t2 = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	std::cout << duration << "\n";

	t1 = std::chrono::high_resolution_clock::now();
	M.increment(0.5, 0.1);
	t2 = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	std::cout << duration << "\n";

	t1 = std::chrono::high_resolution_clock::now();
	M.increment(0.5, 0.1);
	t2 = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	std::cout << duration << "\n";

	t1 = std::chrono::high_resolution_clock::now();
	M.increment(0.5, 0.1);
	t2 = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	std::cout << duration << "\n";

	t1 = std::chrono::high_resolution_clock::now();
	M.increment(0.5, 0.1);
	t2 = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	std::cout << duration << "\n";

	t1 = std::chrono::high_resolution_clock::now();
	M.increment(0.5, 0.1);
	t2 = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	std::cout << duration << "\n";

	t1 = std::chrono::high_resolution_clock::now();
	M.increment(0.5, 0.1);
	t2 = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	std::cout << duration << "\n";




	return 0;
}