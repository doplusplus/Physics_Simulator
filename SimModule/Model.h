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

	//	void showScene() const;

	void addMatPoint(double x, double y, double z, double Vx, double Vy, double Vz, double mass, double charge_);
	void addMatPoint(Point p, Vect velocity = Vect(0, 0, 0), double mass = 1, double charge_ = 1);

	void addActionOnPoint(unsigned int elementReference, Vect A); //starting from 0


/*	void setDomain(unsigned int elementReference, double accuracy, double amplitude);

	//void printState();
*/
//void simulate(double dt, double accuracy = 0.1);
	void increment(double dt, double accuracy);
	void simulate(double duration, double step, std::string target, double accuracy = 0.001);


	void writeDescription(std::ofstream &Result);
	
	




	void directIncrement(double dt) {};
	std::string getDescription();

	/*	void showObservers();

		Point getElementPosition(unsigned int rank) const { return ObserverRef[rank]->position(); };
		std::string getDescription();
	*/
	std::vector<double> getCoordinate();

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

