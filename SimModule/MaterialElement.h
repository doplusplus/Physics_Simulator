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
	MaterialElement(Point G = Point(0, 0, 0), Vect velocity = Vect(0, 0, 0), double mass = 0, double charge = 0);
	virtual ~MaterialElement();

	//Accessors
	Point *pointerToPosition();
	double mass();
	double charge();

	//Display
	virtual void consoleShow();

	//Modifier
	void move(double dx, double dy, double dz);

	//Operators
	bool operator==(const MaterialElement & B);

	//Simulation tool
	virtual void addExternalAction(Vect F = Vect(), Torsor T = Torsor()) = 0;
	virtual void update(double dt) = 0; //computes and updates the state of the element to t+dt


protected:
	double	Charge = 0; 							// in Coulomb
	double	Mass = 0;   							// in kg
	Vect	CenterOfMassVelocity = Vect(0, 0, 0);	// m/s
	Point	CenterOfMassPosition = Point(0, 0, 0);	// m 
};

class MaterialPoint : public MaterialElement
{
	using MaterialElement::MaterialElement;

public:
	MaterialPoint();
	~MaterialPoint();

	void addExternalAction(Vect MechanicalAction);
	void addExternalAction(Vect F, Torsor T);

	void update(double dt);

private:
	std::vector<Vect>	ExternalActions;
	void updateSpeedandPosition(double dt);
};

class Solid : public MaterialElement
{
	using MaterialElement::MaterialElement;

public:
	Solid();
	~Solid();

	void addExternalAction(Torsor MechanicalAction);
	void addExternalAction(Vect F, Torsor T);

	void update(double dt);

private:
	std::vector<Torsor>	ExternalActions;

	void updateSpeedandPosition(double dt);

	double	MomentOfInertia1;
	double	MomentOfInertia2;
	double	MomentOfInertia3;
	Vect	FirstPrincipalComponent;
	Vect	SecondPrincipalComponent;
	Vect	ThirdPrincipalComponent;
};



#endif
