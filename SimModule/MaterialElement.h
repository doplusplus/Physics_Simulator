#ifndef MatElem
#define MatElem

#include <vector>
#include "Geo.h"
#include "Torsor.h"
#include "MechanicalAction.h"

//=============================== Material element ==============================
class MaterialElement
{
public:
	//Constructors & destructor
	MaterialElement(double mass, double charge);
	virtual ~MaterialElement();

	//Display
	virtual void consoleShow() const;

protected:
	double	Charge; 							// in Coulomb
	double	Mass;   							// in kg
};

class MaterialPoint : public MaterialElement
{
	friend class MaterialPointObserver;

public:
	MaterialPoint(double mass = 0.0, double charge = 0.0);
	MaterialPoint(double mass, double charge, std::vector< std::shared_ptr<ActionOnPoint> > ExtActions);
	~MaterialPoint();

	bool operator ==(const  MaterialPoint& B);

protected:
	std::vector< std::shared_ptr<ActionOnPoint> >	ExternalActions;
	void addAction(std::shared_ptr<ActionOnPoint> A);
	void sortActions();
};

class RigidSolid : public MaterialElement
{
public:
	RigidSolid(double mass = 0.0, double charge = 0.0);
	RigidSolid(double mass, double charge, std::vector< std::shared_ptr<ActionOnRigidSolid> > ExtActions);
	~RigidSolid();

protected:
	std::vector< std::shared_ptr< ActionOnRigidSolid> >	ExternalActions;

	double	MomentOfInertia1;
	double	MomentOfInertia2;
	double	MomentOfInertia3;

	Vect	FirstPrincipalComponent;
	Vect	SecondPrincipalComponent;
	Vect	ThirdPrincipalComponent;
};



#endif