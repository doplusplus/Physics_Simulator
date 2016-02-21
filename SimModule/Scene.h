#ifndef SCENE
#define SCENE

#include <unordered_set>
#include "MaterialElement.h"


class Scene
{
	friend class Model;
public:

	//Constructors and destructor
	Scene();
	Scene(std::unordered_set<MaterialElement*> content);
	~Scene();

	//Display
	void consoleShow();

	//Operators
	bool operator ==(Scene s);


private:
	std::unordered_set<MaterialElement*> Content;
	double Time = 0;
	
	void addMatPoint(MaterialPoint *Mp);
	//	void addSolid(Solid *Content);
	
	void forwardTime(double dt);
};


#endif