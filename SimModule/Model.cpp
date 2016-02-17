#include "Model.h"


Model::Model()
{
	Calculator *C = new Calculator();
	ComputationUnit.push_back(C);
}

Model::~Model()
{
	for (auto element : ComputationUnit) { delete element; }
	for (auto element : HandlerRef) { delete element; }
}

void Model::showScene()
{
	ContentRef.consoleShow();
}

void Model::addMatPoint(Point p, Vect velocity, double mass, double charge_)
{
	MaterialPoint *Mp = new MaterialPoint(p, velocity, mass, charge_);
	ContentRef.addMatPoint(Mp);

	Calculator *C = ComputationUnit[0];
	MaterialPointHandler *MpH = new MaterialPointHandler(Mp, C);
	HandlerRef.push_back(MpH);
}


void Model::addActionOnPoint(unsigned int elementReference, Vect A)
{
	ActionOnPoint* M = new ActionOnPoint(A);
	((MaterialPointHandler*)(HandlerRef[elementReference]))->addAction(M);
};

void Model::setDomain(unsigned int elementReference, double accuracy, double amplitude)
{
	Calculator *C = new Calculator(accuracy, amplitude);
	ComputationUnit.push_back(C);
	HandlerRef[elementReference]->setCalculator(C);
};

void Model::simulate(double time, double dt)
{
	double d = 0;
	do {
		for (auto element : HandlerRef)
		{
			element->forward(dt);
		}
		d += dt;
		ContentRef.forwardTime(dt);
	} while (d < time);

}

void Model::showHandlers()
{
	int i = 0;
	for (auto element : HandlerRef)
	{
		std::cout << "-------------element " << i << "-------------" << '\n';
		element->show();
		i++;
	}
}