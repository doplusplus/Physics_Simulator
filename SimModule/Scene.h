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
	void update(double dt);					 		// calculates the scene configuration in dt seconds
	void simulate(double step, double duration);	// simulates the scene of certain duration and increment
														
	//---------- Model interface-----------------------
/*	void addMatPoint();
	void addMatPoint(Point p, Vect velocity = Vect(0, 0, 0), double mass = 0, double charge_ = 0);

	void addSolid();
	void addSolid(Point p, Vect velocity = Vect(0, 0, 0), double mass = 0, double charge_ = 0);
*/
private:
	std::vector<MaterialElement*> S;
	double Time = 0;

	void addMatPoint(MaterialPoint *Mp);

};


#endif