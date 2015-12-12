#include "Scene.h"
//#include "PhysicalElement.h" //for nullify function
//#include "MaterialElement.h" //for show function
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
		delete (*it);
	}
}


//Accessors

MaterialElement *Scene::getElement(unsigned int i)
{
 MaterialElement *M=NULL;

	if (i < S.size())
        {M = S[i];}
	else 
        {
            std::cout<<"No element"<<'\n';
        }
	return M;
}


//Display
void Scene::consoleShow()
{
	if (0 < S.size())
	{
		for (unsigned int i = 0; i < S.size(); i++)
		{
			std::cout<<"element "<<i+1<<": "<<'\n';  //from 1 to number of elements
			S[i]->consoleShow();
		}
	}
	else {std::cout<<"empty scene "<<'\n';}
}
	

//Modifier
void Scene::setForce(Force F, unsigned int place) // add force to element i
{
	S[place]->setResultant(F);
}

void Scene::update(double dt)
{
	//std::vector<MaterialElement*>::iterator it;
	for (auto it = S.begin(); it != S.end(); it++)
	{
		(*it)->update(dt);
	}

}	
	
void Scene::simulate(double step, double duration)
{
 double t=0;
	while(t <= duration)
	{
		update(step);
		t= t+step;
	}
}


//----------Model interface-----------------------

void Scene::addMatPoint()
{
	MaterialPoint *Mp = new MaterialPoint;
	S.push_back(Mp);
}

void Scene::addMatPoint(double x, double y, double z, double mass, double charge )
{
	MaterialPoint *Mp = new MaterialPoint;
	Mp->setPosition(x, y, z);
	Mp->setMass(mass);
	Mp->setCharge(charge);
    Mp->setMass(mass);
    Mp->setPosition(x,y,z);
	S.push_back(Mp);
}