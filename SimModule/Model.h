#pragma once

#include "Observer.h"
#include "Scene.h"
#include <iostream>
#include <string>
#include <fstream>



class Model
{
public:
	Model();
	~Model();

	void writeDescription(std::ofstream &Result);
	std::string fileFormatedDescription();
	std::string getDescription();
	std::vector<double> getCoordinate();

	void addMatPoint(double x, double y, double z, double Vx, double Vy, double Vz, double mass, double charge_);
	void addMatPoint(Point p, Vect velocity = Vect(0, 0, 0), double mass = 1, double charge_ = 1);

	void addActionOnPoint(unsigned int elementReference, Vect A); //starting from 0
	void addActionOnSolid(unsigned int elementReference, Vect A) {}; //starting from 0

	void increment(double dt, double accuracy);
	void simulate(double duration, double step, std::string target, double accuracy = 0.001);
	
	std::vector<Point> Positions(double dt);	
	std::vector<Vect> Orientations(double dt) { return{}; }

	bool RTIncrement(double dt, int SampSize);
	

private:
	Scene ContentRef;
	std::vector<Observer*> ObserverRef;
	std::vector<Calculator*> ComputationUnit;

	bool GraphicalOutput = false;
	bool FileOutput = false;
	bool DbOutput = false;

	static void incrementTime(double dt);
	static double time;
};

