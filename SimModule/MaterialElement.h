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
	MaterialElement(Point G , Vect velocity , double mass, double charge);
	virtual ~MaterialElement();

	//Display
	virtual void consoleShow() const;

	
	std::vector<double> streamCoord() { return CenterOfMassPosition.coordStream(); };


protected:
	double	Charge = 0; 							// in Coulomb
	double	Mass = 0;   							// in kg
	Vect	CenterOfMassVelocity = Vect(0, 0, 0);	// m/s
	Point	CenterOfMassPosition = Point(0, 0, 0);	// m 


	void move(Vect dP);
	void changeVelocity(Vect dS);
};


class MaterialPoint : public MaterialElement
{
	friend class MaterialPointHandler;
public:
	MaterialPoint(Point G = Point(0, 0, 0), Vect velocity = Vect(0, 0, 0), double mass = 0, double charge = 0);
	~MaterialPoint();

};

class Solid : public MaterialElement
{
public:
	Solid(Point G = Point(0, 0, 0), Vect velocity = Vect(0, 0, 0), double mass = 0, double charge = 0);
	~Solid();


private:
	double	MomentOfInertia1;
	double	MomentOfInertia2;
	double	MomentOfInertia3;

	Vect	FirstPrincipalComponent;
	Vect	SecondPrincipalComponent;
	Vect	ThirdPrincipalComponent;

	void rotate(Vect dR) {};
	void changeRotationalSpeed(Vect dS) {}; //around instantaneous rotation axis
};



#endif