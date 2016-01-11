#ifndef MatElem
#define MatElem

#include "Geo.h"
#include "PhysicalElement.h"



//===============================Material element==============================
class MaterialElement
{
public:


	//Constructors & destructor
	MaterialElement();	

	MaterialElement(Point p, Force res = Force() , Velocity vel = Velocity() , double masse = 0, double charge_ = 0);
	~MaterialElement();		

	//Accessors
    Point *pointerToPosition(); 
    double getMass();		
	double getCharge();

	//Display
	virtual void consoleShow();
	
	//Modifier
    void setPosition(Point &p);
	void setPosition(double x, double y, double z);
	void setMass(double m);
	void setCharge(double c);
	void setResultant(Force F);

	//Simulation tool
	virtual void update(double dt); //computes and updates the state of the element to t+dt
	virtual Acceleration getAcceleration();

private:
	double		Charge; 	// in Coulomb
	double		Mass;   	// in kg
	Velocity	V;			// m/s
	Force		NetForce;	// Newton
	Point		Position;	// m 

	virtual void updateSpeedandPosition(Acceleration a, double dt);

};

class MaterialPoint : public MaterialElement
{
	public:
		MaterialPoint();
		~MaterialPoint();
};













#endif
