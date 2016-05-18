#include "Model.h"


Model::Model()
{
	Calculator *C = new Calculator();
	ComputationUnit.push_back(C);
}

Model::~Model()
{
	for (auto element : ComputationUnit) { delete element; }
	for (auto element : ObserverRef) { delete element; }
}



/*
void Model::showScene()const
{
	for (auto element : ObserverRef)
	{
		element->show();
	}
}

std::string Model::getDescription()
{
	std::string s;
	for (unsigned int i = 0; i < ObserverRef.size();i++)
	{
		s += "element n° "+ std::to_string(i)+"\n"+ ObserverRef[i]->getDescription();
	}
	return s;
}

void Model::addMatPoint(Point p, Vect velocity, double mass, double charge_)
{
	MaterialPoint *Mp = new MaterialPoint({},mass, charge_);
	ContentRef.addMatPoint(Mp);

	Calculator *C = ComputationUnit[0];
//	MaterialPointObserver *MpH = new MaterialPointObserver(Mp, C);
//	ObserverRef.push_back(MpH);
}


void Model::addActionOnPoint(unsigned int elementReference, Vect A)
{
	ActionOnPoint* M = new ActionOnPoint(A);
	((MaterialPointObserver*)(ObserverRef[elementReference]))->addAction(M);
};

void Model::setDomain(unsigned int elementReference, double accuracy, double range)
{
	Calculator *C = new Calculator(accuracy, range);
	ComputationUnit.push_back(C);
	//ObserverRef[elementReference]->setCalculator(C);
};


void Model::printState()
{
	if (GraphicalOutput){}

	if(DbOutput){}

	if(FileOutput){}

}

*/
void Model::simulate(double time, double dt, double accuracy)
{	
	double d = 0;
	do
	{
		for (auto element : ObserverRef)
		{
			element->increment(dt,accuracy);
		}
		d += dt;
		ContentRef.incrementTime(dt);
		//	
	} while (d < time);

}

void Model::simulateRT(double time, double dt)
{
	double d = 0;
	do
	{
		for (auto element : ObserverRef)
		{
			element->incrementRT(dt);
		}
		d += dt;
		ContentRef.incrementTime(dt);
		//	
	} while (d < time);

}
/*
void Model::showObservers()
{
	int i = 0;
	for (auto element : ObserverRef)
	{
		std::cout << "-------------element " << i << "-------------" << '\n';
		element->show();
		i++;
	}
}

*/