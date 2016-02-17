#include "Scene.h"
#include "MaterialElement.h" 
#include <iostream>


//**************************************************************************************
//-----------------------------------SCENE------------------------------------

//Constructors and destructor
Scene::Scene()
{}

Scene::Scene(std::vector<MaterialElement*> content)
{
	S = content;
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

void Scene::addMatPoint(MaterialPoint *Mp)
{
	S.push_back(Mp);
}
