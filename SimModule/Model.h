#pragma once

#include "Handler.h"
#include "Scene.h"
#include <iostream>
#include <string>

class Model
{
public:
	Model();
	~Model();

	void showScene() const;

	void addMatPoint(double x, double y, double z, double Vx, double Vy, double Vz, double mass, double charge_)
	{
		addMatPoint(Point(x, y, z), Vect(Vx, Vy, Vz), mass, charge_);
	}

	void addMatPoint(Point p, Vect velocity = Vect(0, 0, 0), double mass = 1, double charge_ = 1);
	void addActionOnPoint(unsigned int elementReference, Vect A);
	void setDomain(unsigned int elementReference, double accuracy, double amplitude);
	
	//void printState();
	void simulate(double time, double dt);
	void showHandlers();
	
	Point getElementPosition(unsigned int rank) const { return HandlerRef[rank]->position(); };
	std::string getDescription();

	std::vector<double> getCoordinate()
	{
		return ContentRef.streamCoordinate();
	}

private:
	Scene ContentRef;
	std::vector<MaterialElementHandler*> HandlerRef;
	std::vector<Calculator*> ComputationUnit;
	
	bool GraphicalOutput = false;
	bool FileOutput = false;
	bool DbOutput = false;
};

