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

	//Display
	virtual void consoleShow();

	//Operators
	bool operator==(const MaterialElement & B);


private:
	double	Charge = 0; 							// in Coulomb
	double	Mass = 0;   							// in kg
	Vect	CenterOfMassVelocity = Vect(0, 0, 0);	// m/s
	Point	CenterOfMassPosition = Point(0, 0, 0);	// m 

protected:
	double mass() { return Mass; }
	Vect centerOfMassPosition() { return CenterOfMassPosition; };
	Vect centerOfMassVelocity() { return CenterOfMassVelocity; };

	void move(Vect dP);
	void changeVelocity(Vect dS);
};


class MaterialPoint : public MaterialElement
{
	using MaterialElement::MaterialElement;
	friend class MaterialPointHandler;

public:
	MaterialPoint();
	~MaterialPoint();
};

class Solid : public MaterialElement
{
	using MaterialElement::MaterialElement;

public:
	Solid();
	~Solid();


private:
	double	MomentOfInertia1;
	double	MomentOfInertia2;
	double	MomentOfInertia3;
	Vect	FirstPrincipalComponent;
	Vect	SecondPrincipalComponent;
	Vect	ThirdPrincipalComponent;

	void rotate(Vect dR) {};
};



#endif