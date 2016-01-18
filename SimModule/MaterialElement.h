#ifndef MatElem
#define MatElem

#include "Geo.h"

//===============================Material element==============================
class MaterialElement
{
public:


	//Constructors & destructor
	MaterialElement();	
	MaterialElement(Point p, Vect resultantForce , Vect velocity,
		double masse = 0, double charge_ = 0);
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
	void setResultant(Vect force);

	//Simulation tool
	virtual void update(double dt); //computes and updates the state of the element to t+dt
	virtual Vect getAcceleration();

private:
	double		Charge; 	// in Coulomb
	double		Mass;   	// in kg
	Vect		Velocity;	// m/s
	Vect		NetForce;	// Newton
	Point		Position;	// m 

	virtual void updateSpeedandPosition(Vect acceleration, double dt);

};

class MaterialPoint : public MaterialElement
{
	public:
		MaterialPoint();
		~MaterialPoint();
};

#endif
