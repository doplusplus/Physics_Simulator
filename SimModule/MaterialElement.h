#ifndef MatElem
#define MatElem

#include "Geo.h"
#include "PhysicalElement.h"



//===============================Material element==============================
class MaterialElement
{
private:
	
	double Mass;   	// in kg
	double Charge; 	// in Coulomb
	Point Position; // m 
	Force NetForce; // Newton
    Velocity V;		// m/s
	
	virtual void updateSpeedandPosition(Acceleration a, double dt);

public:


	//Constructors & destructor
	MaterialElement();	
    MaterialElement(Point p, double masse =0, double charge_=0);
	~MaterialElement();		

	//Accessors
    Point *pointerToPosition(); //** necessary for display
    double getMass(); //** necessary for display

	//Display
	virtual void consoleShow();
	
	//Modifier
    void setPosition(Point &p);
	void setPosition(double x, double y, double z);
	void setMass(double m);
	
	//Simulation tool
	virtual void update(double dt); //computes and updates the state of the element at t+dt
	virtual Acceleration getAcceleration();
};















#endif
