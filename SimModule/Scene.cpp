#include "Scene.h"
#include "MaterialElement.h" 
#include <iostream>


//**************************************************************************************
//-----------------------------------SCENE------------------------------------

//Constructors and destructor
Scene::Scene()
{
}

Scene::~Scene()
{
	for (auto it = S.begin(); it != S.end(); it++)
	{
		delete *it;
	}
}


//Accessors

MaterialElement *Scene::getElement(unsigned int i)
{
	MaterialElement *M = nullptr;

	if (i < S.size())
	{
		M = S[i];
	}
	else
	{
		std::cout << "No element" << '\n';
	}
	return M;
}

double Scene::getTime()
{
	return Time;
}

//Display
void Scene::consoleShow()
{
	if (0 < S.size())
	{
		for (unsigned int i = 0; i < S.size(); i++)
		{
			std::cout << "element " << i + 1 << ": " << '\n';  //from 1 to number of elements
			S[i]->consoleShow();
		}
	}
	else { std::cout << "empty scene " << '\n'; }
}


//Modifier

void Scene::addExternalAction(unsigned int place, Vect F, Torsor T)	// adds force to element i starting from 0
{
	S[place]->addExternalAction(F, T);
}

void Scene::addExternalAction(unsigned int place, Torsor T)
{
	addExternalAction(place, Vect(0, 0, 0), T);
}

void Scene::update(double dt)
{
	for (auto it = S.begin(); it != S.end(); it++)
	{
		(*it)->update(dt);
	}
}

void Scene::simulate(double step, double duration)
{
	double t = 0;
	while (t < duration)
	{
		update(step);
		t = t + step;
	}
	Time += t;
}


//----------Model interface-----------------------

void Scene::addMatPoint()
{
	MaterialPoint *Mp = new MaterialPoint;
	S.push_back(Mp);
}

void Scene::addMatPoint(Point p, Vect velocity, double mass, double charge_)
{
	MaterialElement *Mp = new MaterialPoint(p, velocity, mass, charge_);
	S.push_back(Mp);
}


void Scene::addSolid()
{
	Solid *Sol = new Solid;
	S.push_back(Sol);
}

void Scene::addSolid(Point p, Vect velocity, double mass, double charge_)
{
	Solid *Sol = new Solid(p, velocity, mass, charge_);
	S.push_back(Sol);
}
