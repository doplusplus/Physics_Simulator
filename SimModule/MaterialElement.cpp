
#include "MaterialElement.h"
#include "Calculator.h"
#include <iostream>
#include <stdexcept>

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

double MaterialElement::mass() const
{
	if (Mass <= 0) { throw std::domain_error("negative or null mass"); }
	return Mass;
}


// ================================== Material Point==================================================================== 


MaterialPoint::MaterialPoint(double mass, double charge) :MaterialElement(mass, charge)
{}

MaterialPoint::MaterialPoint(double mass, double charge, std::vector<std::shared_ptr<ActionOnPoint>> ExtActions) : MaterialElement(mass, charge), ExternalActions(std::move(ExtActions))
{
	sortActions();
}

MaterialPoint::~MaterialPoint() {}

bool MaterialPoint::operator==(const MaterialPoint & B)
{
	return B.Mass == Mass&&B.Charge == Charge&&ExternalActions == B.ExternalActions;
}

void MaterialPoint::addAction(std::shared_ptr<ActionOnPoint> A)
{
	ExternalActions.push_back(std::move(A));
	sortActions();
}

void MaterialPoint::sortActions()
{
	std::sort(ExternalActions.begin(), ExternalActions.end(), customLess_ActionOnPoint()); 
}



// ================================== Solids Point ==================================================================== 
RigidSolid::RigidSolid(double mass, double charge) :MaterialElement(mass, charge)
{}
RigidSolid::RigidSolid(double mass, double charge, std::vector<std::shared_ptr<ActionOnRigidSolid>> ExtActions)
	: MaterialElement(mass, charge), ExternalActions(std::move(ExtActions))
{}
RigidSolid::~RigidSolid() {}
