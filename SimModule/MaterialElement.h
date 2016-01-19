#ifndef MatElem
#define MatElem

#include<vector>
#include "Geo.h"

//===============================Material element==============================
class MaterialElement
{
public:

	//Constructors & destructor
	MaterialElement();
	MaterialElement(Point p, std::vector<Vect> actions, Vect velocity,
		double masse, double charge_);
	~MaterialElement();

	//Accessors
	Point *pointerToPosition();
	double getMass();
	double getCharge();

	//Display
	virtual void consoleShow();

	//Modifier
	void place(Point &p);
	void place(double x, double y, double z);
	void setMass(double m);
	void setCharge(double c);
	void addExternalAction(Vect MechanicalAction);

	//Simulation tool
	virtual void update(double dt); //computes and updates the state of the element to t+dt
	virtual Vect Acceleration();

private:
	double				Charge; 	// in Coulomb
	double				Mass;   	// in kg
	Vect				Velocity;	// m/s
	std::vector<Vect>	ExternalActions;
	Point				Position;	// m 

	virtual void updateSpeedandPosition(double dt);
};

class MaterialPoint : public MaterialElement
{
public:
	MaterialPoint();
	~MaterialPoint();
};

#endif
