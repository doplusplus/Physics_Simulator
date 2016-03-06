#include "MechanicalAction.h"

//===================================================================================

ActionOnPoint::ActionOnPoint()
{}

ActionOnPoint::ActionOnPoint(double x, double y, double z)
{
	Action = Vect(x, y, z);
}
ActionOnPoint::ActionOnPoint(Vect action, Vect timeBase, Vect spaceBase,
	Vect(*timeDiff)(Vect, double), Vect(*spaceDiff)(Vect, double))
{
	 Action = action;
	 TimeBase = timeBase;
	 SpaceBase = spaceBase;
	TimeDerivative =timeDiff ;
	SpaceDerivative = spaceDiff;
}

ActionOnPoint::~ActionOnPoint()
{}


Vect ActionOnPoint::force()
{
	return Action;
}


void ActionOnPoint::null() { Action = Vect(0, 0, 0); }
void ActionOnPoint::show() { Action.show(); }
void ActionOnPoint::add(MechanicalAction *A, MechanicalAction *result)
{
	addAction((ActionOnPoint*)A, (ActionOnPoint*)result);
}
void ActionOnPoint::addAction(ActionOnPoint *C, ActionOnPoint *result)
{
	result->Action = result->Action + C->Action;
}
MechanicalAction * ActionOnPoint::copy()
{
	MechanicalAction* ptr = new ActionOnPoint(*this);
	return ptr;
}
Vect ActionOnPoint::variation(double t, double dt, Vect tBase, Vect sBase)
{
	return TimeDerivative(tBase, t)*dt + SpaceDerivative(sBase, t)*dt;
}
void ActionOnPoint::forward(double t, double dt)
{
	Action = Action + variation(t, dt, TimeBase, SpaceBase);
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
	return Action.vectComponent();
}

void ActionOnSolid::add(MechanicalAction *A, MechanicalAction *result)
{
	addAction((ActionOnSolid*)A, (ActionOnSolid*)result);
}
void ActionOnSolid::addAction(ActionOnSolid *C, ActionOnSolid *result)
{
	result->Action = result->Action + C->Action;
}