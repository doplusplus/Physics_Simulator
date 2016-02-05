#ifndef MatElem
#define MatElem

#include<vector>
#include "Geo.h"
#include "Torsor.h"

//=============================== Material element ==============================
class MaterialElement
{
	friend class MaterialPointHandler;
public:
	//Constructors & destructor
	MaterialElement(Point G = Point(0, 0, 0), Vect velocity = Vect(0, 0, 0), double mass = 0, double charge = 0);
	virtual ~MaterialElement();

	//Accessors
//	Point *pointerToPosition();

	//Display
	virtual void consoleShow();

	//Modifier

	virtual void update(double dt)=0;
	//Operators
	bool operator==(const MaterialElement & B);


private:
	double	Charge = 0; 							// in Coulomb
	double	Mass = 0;   							// in kg
	Vect	CenterOfMassVelocity = Vect(0, 0, 0);	// m/s
	Point	CenterOfMassPosition = Point(0, 0, 0);	// m 

	void move(Vect dP);
	void changeVelocity(Vect dS);
};


class MaterialPoint : public MaterialElement
{
	using MaterialElement::MaterialElement;
	

public:
	MaterialPoint();
	~MaterialPoint();

	void update(double dt);
};

class Solid : public MaterialElement
{
	using MaterialElement::MaterialElement;

public:
	Solid();
	~Solid();

	void addExternalAction(Torsor MechanicalAction);
	void addExternalAction(Vect F, Torsor T);

	void update(double dt) {};


private:
	double	MomentOfInertia1;
	double	MomentOfInertia2;
	double	MomentOfInertia3;
	Vect	FirstPrincipalComponent;
	Vect	SecondPrincipalComponent;
	Vect	ThirdPrincipalComponent;
};



#endif