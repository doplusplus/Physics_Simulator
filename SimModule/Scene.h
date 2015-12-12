#ifndef SCENE
#define SCENE

#include <vector>
#include "MaterialElement.h"
#include "PhysicalElement.h"



class Scene
{
	private:
		std::vector<MaterialElement*> S;
	
	public:

	//Constructors and destructor
	Scene();
	~Scene();
	
	//Accessors
    MaterialElement* getElement(unsigned int i);

	//Display
	void consoleShow();

	//Modifier
    void setForce(Force F, unsigned int place);				// adds force to element i starting from 0
    void update(double dt);							//calculates the scene configuration in dt seconds
	void simulate(double step, double duration);	//simulates the scene of certain duration and increment
	
	
	//----------Model interface-----------------------
	void addMatPoint();
    void addMatPoint(double x, double y, double z, double mass = 0, double charge = 0);
	
};


#endif