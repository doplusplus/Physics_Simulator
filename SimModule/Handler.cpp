#include "Handler.h"


//============================= MaterialElement Handler ===============================
MaterialElementHandler::MaterialElementHandler()
{}

MaterialElementHandler::~MaterialElementHandler()
{}

void MaterialElementHandler::show()
{
	std::cout << "material element: ";
}

void MaterialElementHandler::setCalculator(Calculator *C)
{
	Calc = C;
}




//============================= MaterialPoint Handler ===============================

MaterialPointHandler::MaterialPointHandler(MaterialPoint *Mp, Calculator *C)
{
	Element = Mp; Calc = C;
	ActionOnPoint *A = new ActionOnPoint(Vect(0, 0, 0));
	ExternalActions.push_back(A);
}

MaterialPointHandler::MaterialPointHandler(MaterialPoint *Mp, Calculator *C, std::vector< MechanicalAction* > &A):MaterialPointHandler(Mp,C)
{
	ExternalActions = A;
}


MaterialPointHandler::~MaterialPointHandler()
{
	std::cout << "handler breaks free" << '\n';
	for (auto element : ExternalActions) delete element;
	std::cout << "...without troubles" << '\n';
}

void MaterialPointHandler::forward(double dt)
{
	Vect acceleration = Calc->centerOfMassAcceleration(ExternalActions, Element->Mass);
	Vect velocity = Element->CenterOfMassVelocity;

	Vect diffPosition = Calc->positionVariationCoM(acceleration, velocity, dt);
	Vect diffVelocity = Calc->velocityVariationCoM(acceleration, dt);

	Element->move(diffPosition);
	Element->changeVelocity(diffVelocity);
}

void MaterialPointHandler::addAction(ActionOnPoint* action)
{
	ExternalActions.push_back(action);
}

void MaterialPointHandler::show()
{
	MaterialElementHandler::show();
	std::cout << " Point"<<'\n';

	std::cout << "Mechanical actions" << '\n';
	for (auto act : ExternalActions) act->show();

	std::cout << "Position" << '\n';
	Element->consoleShow();
}