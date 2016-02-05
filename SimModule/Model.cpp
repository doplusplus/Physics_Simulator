#include "Model.h"


Model::Model()
{
	ComputationUnit.push_back(Calculator());
}

Model::~Model()
{}

void Model::showScene()
{
	ContentRef.consoleShow();
}

void Model::addMatPoint(Point p, Vect velocity , double mass, double charge_ )
{
	MaterialPoint *Mp = new MaterialPoint(p, velocity, mass, charge_);
	ContentRef.addMatPoint(Mp);

	Calculator *C = &ComputationUnit[0];
	MaterialPointHandler *MpH =new MaterialPointHandler(Mp,C);
	HandlerRef.push_back(MpH);
}



