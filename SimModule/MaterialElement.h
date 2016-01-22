#ifndef MatElem
#define MatElem

#include<vector>
#include "Geo.h"
#include "Torsor.h"

//=============================== Material element ==============================
class MaterialElement
{
public:
	//Constructors & destructor
	MaterialElement();
	MaterialElement(Point p, Vect velocity, double mass, double charge_);
	virtual ~MaterialElement();

	//Accessors
	Point *pointerToPosition();
	double mass();
	double charge();

	//Display
	virtual void consoleShow();

	//Modifier
	void move(double dx, double dy, double dz);
	void setMass(double m);
	void setCharge(double c);

	//Simulation tool
	virtual void addExternalAction(Vect F=Vect(), Torsor T=Torsor()) = 0;
	virtual void update(double dt) = 0; //computes and updates the state of the element to t+dt
	virtual Vect Acceleration() = 0;

protected:
	double				Charge; 	// in Coulomb
	double				Mass;   	// in kg
	Vect				CenterOfMassVelocity;	// m/s
	Point				CenterOfMassPosition;	// m 
};

class MaterialPoint : public MaterialElement
{
public:
	MaterialPoint();
	MaterialPoint(Point G, Vect velocity=Vect(0,0,0), double mass=0, double charge=0);
	~MaterialPoint();

	void addExternalAction(Vect MechanicalAction);
	void addExternalAction(Vect F, Torsor T);
	Vect Acceleration();
	void update(double dt);

private:
	std::vector<Vect>	ExternalActions;
	
	void updateSpeedandPosition(double dt);
};

class Solid : public MaterialElement
{
public:
	Solid();
	Solid(Point G, Vect velocity=Vect(0,0,0), double mass=0, double charge=0);
	~Solid();

	void addExternalAction(Torsor MechanicalAction);
	void addExternalAction(Vect F, Torsor T);
	Vect Acceleration();
	void update(double dt);

private:
	std::vector<Torsor>	ExternalActions;

	void updateSpeedandPosition(double dt);

	double	FirstInertiaMoment;
	double	SecondInertiaMoment;
	double	ThirdInertiaMoment;
	Vect	FirstPrincipalComponent;
	Vect	SecondPrincipalComponent;
	Vect	ThirdPrincipalComponent;


};



#endif
