#pragma once

#include "Handler.h"
#include "Scene.h"
#include <iostream>


class Model
{
public:
	Model();
	~Model();

	void showScene();

	void addMatPoint(Point p, Vect velocity = Vect(0, 0, 0), double mass = 1, double charge_ = 1);
	void addActionOnPoint(unsigned int elementReference, Vect A);
	void setDomain(unsigned int elementReference, double accuracy, double amplitude);
	
	//void printState();
	void simulate(double time, double dt);
	void showHandlers();
	
	Point getElementPosition(unsigned int rank) { return HandlerRef[rank]->position(); };


private:
	Scene ContentRef;
	std::vector<MaterialElementHandler*> HandlerRef;
	std::vector<Calculator*> ComputationUnit;
	
	bool GraphicalOutput = false;
	bool FileOutput = false;
	bool DbOutput = false;
};
