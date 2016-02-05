#pragma once

#include "Handler.h"
#include "Scene.h"

class Model
{
public:
	Model();
	~Model();

	void showScene();

	void addMatPoint(Point p, Vect velocity = Vect(0, 0, 0), double mass = 0, double charge_ = 0);
	void addActionOnPoint(unsigned int elementReference, Vect A) {};//TDF

private:
	Scene ContentRef;
	std::vector<MaterialElementHandler*> HandlerRef;
	std::vector<Calculator> ComputationUnit;
};

