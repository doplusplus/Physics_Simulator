#ifndef MatElem
#define MatElem

#include "Geo.h"
#include "PhysicalElement.h"



//===============================Material element==============================
class MaterialElement
{
private:
	
	double mass;   	// in kg
	double charge; 	// in Coulomb
	Point position; // m 
	Force netForce; // Newton
	Velocity v;		// m/s	
	
public:


	//Constructors & destructor
	MaterialElement();	
	MaterialElement(Point P, double mass =0, double charge=0);
	~MaterialElement();		

	//Accessors
    Point *pointerToPosition();
    double getMass();

	//Display
	virtual void consoleShow();
	
	//Modifier
	void setPosition(Point &P);
	void setPosition(double x, double y, double z);
	void setMass(double m);
	
	//Simulation tool
	virtual void update(double dt); //computes and updates the state of the element at t+dt
	virtual Acceleration getAcceleration();
	virtual void updateSpeedandPosition(Acceleration a, double dt); 
	
};















#endif
