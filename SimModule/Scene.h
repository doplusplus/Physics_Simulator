#ifndef SCENE
#define SCENE

#include <vector>
#include "MaterialElement.h"


class Scene
{
	friend class Model;
public:

	//Constructors and destructor
	Scene();
	Scene(std::vector<MaterialElement*> content);
	~Scene();

	MaterialElement* getElement(unsigned int i);
	double getTime();

	//Display
	void consoleShow();
														
	//---------- Model interface-----------------------

private:
	std::vector<MaterialElement*> S;
	double Time = 0;
	void addMatPoint(MaterialPoint *Mp);
//	void addSolid(Solid *S);
	void forwardTime(double dt) { Time += dt; };
};


#endif