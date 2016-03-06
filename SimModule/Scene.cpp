#include "Scene.h"
#include "MaterialElement.h" 
#include <iostream>


//**************************************************************************************
//-----------------------------------SCENE------------------------------------

//Constructors and destructor
Scene::Scene()
{}

Scene::Scene(std::unordered_set<MaterialElement*> content)
{
	Content = content;
}

Scene::~Scene()
{
	for (auto it = Content.begin(); it != Content.end(); it++)
	{
		delete *it;
	}
}

//Display
void Scene::consoleShow()
{
	if (0 < Content.size())
	{
		for (auto element:Content)
		{
			element->consoleShow();
		}
	}
	else { std::cout << "empty scene " << '\n'; }
}

bool Scene::operator==(Scene s)
{
	unsigned int n = Content.size();

	if (s.Content.size() != n) { return false; }
	for (auto element:Content)
	{
		if (s.Content.find(element)==s.Content.end()) { return false; }
	}

	return true;
}

void Scene::addMatPoint(MaterialPoint *Mp)
{
	Content.insert(Mp);
}

void Scene::forwardTime(double dt)
{
	if (dt >= 0) { Time += dt; }
	else { throw "backward time travel"; }
}

