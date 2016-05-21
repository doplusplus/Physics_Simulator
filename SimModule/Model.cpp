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

void Model::addMatPoint(double x, double y, double z, double Vx, double Vy, double Vz, double mass, double charge_)
{
	addMatPoint(Point(x, y, z), Vect(Vx, Vy, Vz), mass, charge_);
}

/*
void Model::showScene()const
{
	for (auto element : ObserverRef)
	{
		element->show();
	}
}
*/
std::string Model::getDescription()
{
	std::string s;
	for (unsigned int i = 0; i < ObserverRef.size();i++)
	{
		s += "element n° "+ std::to_string(i)+"\n"+ ObserverRef[i]->getDescription();
	}
	return s;
}

std::vector<double> Model::getCoordinate()
{
	std::vector<double> Coord = {};

	for (auto elem : ObserverRef)
	{
		auto locCoord = elem->streamCoord();
		Coord.insert(Coord.begin(), locCoord.begin(), locCoord.end());
	}
	return Coord;
}

void Model::addMatPoint(Point p, Vect velocity, double mass, double charge_)
{
	MaterialPoint *Mp =new  MaterialPoint(mass, charge_, {});
	Calculator *C = ComputationUnit[0];
	ContentRef.addMatPoint(Mp);
	MaterialPointObserver *Obs = new MaterialPointObserver(*Mp, *C, p, velocity);
	ObserverRef.push_back(Obs);
}


void Model::addActionOnPoint(unsigned int elementReference, Vect A)
{
	//ActionOnPoint* M = new ActionOnPoint(A);
	auto M = std::make_shared<ActionOnPoint>(ActionOnPoint(A));
	dynamic_cast<MaterialPointObserver*>(ObserverRef[elementReference])->addAction(M);
};

/*
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

}*/

/*
void Model::simulate( double dt, double accuracy)
{	
	for (auto element : ObserverRef)
		{
			element->increment(time, dt,accuracy);
		}
		incrementTime(dt);
}
*/

void Model::increment(double dt, double accuracy)
{
	for (auto element : ObserverRef)
	{
		element->increment(time, dt, accuracy);
	}
	incrementTime(dt);
}

void Model::simulate(double duration, double step, std::string target, double accuracy)
{
	if (duration <= 0) { throw std::invalid_argument("time increment must be positive"); }
	std::ofstream ResultFile(target, std::ofstream::out);
	ResultFile << "t elem X Y Z Vx Vy Vz m C \n";

	while (time<duration)
	{
		writeDescription(ResultFile);
		increment(step, accuracy);
	}
}

void Model::writeDescription(std::ofstream & Result)
{
	if (!Result.is_open()) {
		throw std::ios_base::failure("The target file is not open");
	}

	for (int i = 0; i < ObserverRef.size(); i++)
	{
		auto desc = ObserverRef[i]->descriptionStream();
		Result << time << " " << i;
		for (auto field : desc) { Result << " " << field; }
		Result << "\n";
	}
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
double Model::time = 0;
void Model::incrementTime(double dt)
{
	if (dt <= 0) { throw std::invalid_argument("time increment must be strictly positive"); }
	time += dt;
}