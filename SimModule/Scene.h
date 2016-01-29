#ifndef SCENE
#define SCENE

#include <vector>
#include "MaterialElement.h"


class Scene
{
public:

	//Constructors and destructor
	Scene();
	~Scene();

	//Accessors
	MaterialElement* getElement(unsigned int i);
	double getTime();

	//Display
	void consoleShow();

	//Modifier
	void addExternalAction(unsigned int place, Vect F, Torsor T = Torsor());	// adds force to element i starting from 0
	void addExternalAction(unsigned int place, Torsor T);
	void update(double dt);					 						// calculates the scene configuration in dt seconds
	void simulate(double step, double duration);					// simulates the scene of certain duration and increment

																	//---------- Model interface-----------------------
	void addMatPoint();
	void addMatPoint(Point p, Vect velocity = Vect(0, 0, 0), double mass = 0, double charge_ = 0);

	void addSolid();
	void addSolid(Point p, Vect velocity = Vect(0, 0, 0), double mass = 0, double charge_ = 0);

private:
	std::vector<MaterialElement*> S;
	double Time = 0;

};


#endif