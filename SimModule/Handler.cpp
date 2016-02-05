#include "Handler.h"



MaterialElementHandler::MaterialElementHandler()
{}

MaterialElementHandler::~MaterialElementHandler()
{}

void MaterialPointHandler::update(double dt)
{/*
	Vect acceleration = Calc->centerOfMassAcceleration(ExternalActions, Element->Mass);
	Vect velocity = Element->CenterOfMassVelocity;

	Vect diffPosition = Calc->positionVariation(acceleration, velocity, dt);
	Vect diffVelocity = Calc->velocityVariation(acceleration, dt);

	Element->move(diffPosition);
	Element->changeVelocity(diffVelocity);
	/**/
}