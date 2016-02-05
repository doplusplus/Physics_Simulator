#include "MechanicalAction.h"

//===================================================================================

ActionOnPoint::ActionOnPoint()
{}

ActionOnPoint::ActionOnPoint(double x, double y, double z)
{
	Action = Vect(x, y, z);
}

ActionOnPoint::ActionOnPoint(Vect V)
{
	Action = V;
}

ActionOnPoint::~ActionOnPoint()
{}


Vect ActionOnPoint::force()
{
	return Action;
}


//===================================================================================
ActionOnSolid::ActionOnSolid()
{}

ActionOnSolid::ActionOnSolid(Vect V, Point A)
{
	Action = Torsor(A, V, Vect(0, 0, 0));
}

ActionOnSolid::ActionOnSolid(Vect Res, Vect Moment, Point A)
{
	Action = Torsor(A, Res, Moment);
}

ActionOnSolid::~ActionOnSolid()
{}

Vect ActionOnSolid::force()
{
	return Action.VectComponent();
}
