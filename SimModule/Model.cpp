#include "Model.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <sstream>


double Model::time = 0;

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

std::string Model::getDescription()
{
	std::string s;
	for (unsigned int i = 0; i < ObserverRef.size(); i++)
	{
		s += "element n° " + std::to_string(i) + "\n" + ObserverRef[i]->getDescription();
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

//MUTATORS
void Model::addMatPoint(double x, double y, double z, double Vx, double Vy, double Vz, double mass, double charge_)
{
	addMatPoint(Point(x, y, z), Vect(Vx, Vy, Vz), mass, charge_);
}

void Model::addMatPoint(Point p, Vect velocity, double mass, double charge_)
{
	MaterialPoint *Mp = new  MaterialPoint(mass, charge_, {});
	Calculator *C = ComputationUnit[0];
	ContentRef.addMatPoint(Mp);
	MaterialPointObserver *Obs = new MaterialPointObserver(*Mp, *C, p, velocity);
	ObserverRef.push_back(Obs);
}

void Model::addActionOnPoint(unsigned int elementReference, Vect A)
{
	auto M = std::make_shared<ActionOnPoint>(ActionOnPoint(A));
	dynamic_cast<MaterialPointObserver*>(ObserverRef[elementReference])->addAction(M);
}

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
	std::string s="t elem X Y Z Vx Vy Vz m C \n";
	while (time < duration)
	{
		//writeDescription(ResultFile);
		s.append(fileFormatedDescription());
		increment(step, accuracy);
	}
	ResultFile << s;
	ResultFile.close();
}

std::vector<Point> Model::Positions(double dt)
{
	std::vector<Point> pos = {};
	for (auto element : ObserverRef)
	{
		pos.push_back(element->position(dt));
	}
	return pos;
}

bool Model::RTIncrement(double dt, int SampSize)
{
	bool OnTime = false;
	int running = 0;
	std::vector<Observer*> &obsRef = ObserverRef;
	std::vector<Point> position = Positions(dt);
	std::vector<Vect> orientation = Orientations(dt);
	std::vector<std::thread> Refiner(position.size());

	auto refine = [&position, &orientation,&running, obsRef, SampSize, dt](int p)
	{
		position[p] = obsRef[p]->incrementedPos(time, dt, SampSize);
		orientation[p] = obsRef[p]->incrementedPos(time, dt, SampSize);
		running--;
	};

	auto send = [&obsRef, &OnTime, position, running, dt]()
	{
		std::chrono::duration<double, std::ratio<1,100>> dur(dt*100);
		std::this_thread::sleep_until(std::chrono::system_clock::now()+dur);
		for (unsigned int j = 0; j < obsRef.size(); j++)
		{
			obsRef[j]->changePosition(position[j]);
			std::cout << "position changed" << '\n';
		}
		OnTime = running == 0;
	};

	std::thread t(send);
	for (unsigned int i = 0; i < position.size(); i++)
	{
		running++;
		Refiner[i] = std::thread(refine, i);
		Refiner[i].detach();
	}
	t.join();

	return OnTime;
}

void Model::writeDescription(std::ofstream & Result)
{
	if (!Result.is_open())
	{
		throw std::ios_base::failure("The target file is not open");
	}
	for (unsigned int i = 0; i < ObserverRef.size(); i++)
	{
		auto desc = ObserverRef[i]->descriptionStream();
		Result << time << " " << i;
		for (auto field : desc) { Result << " " << field; }
		Result << "\n";
	}
}

std::string Model::fileFormatedDescription()
{
	std::ostringstream res;
	for (unsigned int i = 0; i < ObserverRef.size(); i++)
	{
		auto desc = ObserverRef[i]->descriptionStream();
		res << time << " " << i;
		for (auto field : desc) { res << " " << field; }
		res << "\n";
	}
	return res.str();
}


void Model::incrementTime(double dt)
{
	if (dt <= 0) { throw std::invalid_argument("time increment must be strictly positive"); }
	time += dt;
}