
#include "MaterialElement.h"
#include "Calculator.h"
#include <iostream>


//Constructors & destructor-------------------------------

MaterialElement::MaterialElement(double mass, double charge_) :Charge(charge_), Mass(mass)
{}

MaterialElement::~MaterialElement()
{}

//---------------------------------------------


//Display-----------------------------------------------
void MaterialElement::consoleShow() const
{
	std::cout << "mass: " << Mass << '\n';
	std::cout << "charge: " << Charge << '\n';
}


// ================================== Material Point==================================================================== 


MaterialPoint::MaterialPoint(double mass, double charge) :MaterialElement(mass, charge)
{}

MaterialPoint::MaterialPoint(double mass, double charge, std::vector<std::shared_ptr<ActionOnPoint>> ExtActions) : MaterialElement(mass, charge), ExternalActions(std::move(ExtActions))
{
	std::sort(ExternalActions.begin(), ExternalActions.end(), customLess_ActionOnPoint());
}

MaterialPoint::~MaterialPoint() {}

bool MaterialPoint::operator==(const MaterialPoint & B)
{
	return B.Mass == Mass&&B.Charge == Charge&&ExternalActions == B.ExternalActions;
}

void MaterialPoint::addAction(std::shared_ptr<ActionOnPoint> A)
{
	ExternalActions.push_back(std::move(A));
}





// ================================== Solids Point ==================================================================== 
RigidSolid::RigidSolid(double mass, double charge) :MaterialElement(mass, charge)
{}
RigidSolid::RigidSolid(double mass, double charge, std::vector<std::shared_ptr<ActionOnRigidSolid>> ExtActions)
	: MaterialElement(mass, charge), ExternalActions(std::move(ExtActions))
{}
RigidSolid::~RigidSolid() {}
