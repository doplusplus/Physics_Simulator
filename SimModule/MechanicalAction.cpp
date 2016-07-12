#include "MechanicalAction.h"

//===================================================================================



ActionOnPoint::ActionOnPoint(const Vect & action, const Vect & timeBase, const Vect & xBase, const Vect & yBase, const Vect & zBase, Vect(*timeDiff_)(Vect, double), double(*xDiff_)(Vect, Vect), double(*yDiff_)(Vect, Vect), double(*zDiff_)(Vect, Vect))
	:ActionOrigin(action), TimeBase(timeBase), XBase(xBase), YBase(yBase), ZBase(zBase), TimeVariation(timeDiff_), XVariation(xDiff_), YVariation(yDiff_), ZVariation(zDiff_)
{}

ActionOnPoint::ActionOnPoint(const Vect & action, const Vect & timeBase, const Vect & spaceBase, Vect(*timeDiff_)(Vect, double), double(*spaceDiff_)(Vect, Vect))
	: ActionOnPoint(action, timeBase, spaceBase, spaceBase, spaceBase, timeDiff_, spaceDiff_, spaceDiff_, spaceDiff_)
{}

ActionOnPoint::ActionOnPoint(const ActionOnPoint & toCopy)
	: ActionOrigin(toCopy.ActionOrigin), TimeBase(toCopy.TimeBase), XBase(toCopy.XBase), YBase(toCopy.YBase), ZBase(toCopy.ZBase), TimeVariation(toCopy.TimeVariation), XVariation(toCopy.XVariation), YVariation(toCopy.YVariation), ZVariation(toCopy.ZVariation)
{}

ActionOnPoint & ActionOnPoint::operator=(const ActionOnPoint & toAssign)
{
	ActionOrigin = toAssign.ActionOrigin;
	TimeBase = toAssign.TimeBase;
	XBase = toAssign.XBase;
	TimeVariation = toAssign.TimeVariation;
	XVariation = toAssign.XVariation;
	return *this;
}

ActionOnPoint::~ActionOnPoint() {}

Vect ActionOnPoint::force(Vect Position, double t)const
{
	return ActionOrigin + variation(Position, t, TimeBase, XBase, YBase, ZBase);
}

Vect ActionOnPoint::variation(Vect Position, double t, Vect tBase, Vect xBase, Vect yBase, Vect zBase)const
{
	return TimeVariation(tBase, t) + Vect(XVariation(xBase, Position), YVariation(yBase, Position), ZVariation(zBase, Position));
}

bool ActionOnPoint::operator==(const ActionOnPoint &P) const
{
	bool b = ActionOrigin == P.ActionOrigin&&TimeBase == P.TimeBase&&XBase == P.XBase
		&& *TimeVariation.target<Vect(*)(Vect, double)>() == *P.TimeVariation.target<Vect(*)(Vect, double)>()
		&& *XVariation.target<double(*)(Vect, Vect)>() == *P.XVariation.target<double(*)(Vect, Vect)>()
		&& *YVariation.target<double(*)(Vect, Vect)>() == *P.YVariation.target<double(*)(Vect, Vect)>()
		&& *ZVariation.target<double(*)(Vect, Vect)>() == *P.ZVariation.target<double(*)(Vect, Vect)>();
	return b;
}

std::tuple<Vect, Vect, Vect, Vect, Vect> ActionOnPoint::base() const
{
	return std::tuple<Vect, Vect, Vect, Vect, Vect>(ActionOrigin, TimeBase, XBase, YBase, ZBase);
}

void ActionOnPoint::null()
{
	ActionOrigin = Vect(0, 0, 0);
	TimeBase = Vect(0, 0, 0);
	XBase = Vect(0, 0, 0);
	YBase = Vect(0, 0, 0);
	ZBase = Vect(0, 0, 0);
	TimeVariation = Vect::constant;
	XVariation = Vect::Vconstant;
	YVariation = Vect::Vconstant;
	ZVariation = Vect::Vconstant;
}

void ActionOnPoint::show() const { ActionOrigin.show(); }

bool customLess_ActionOnPoint::operator()(std::shared_ptr<ActionOnPoint> A, std::shared_ptr<ActionOnPoint> B)
{
	return *(A->TimeVariation.target<Vect(*)(Vect, double)>()) > *(B->TimeVariation.target<Vect(*)(Vect, double)>());
}


//===================================================================================
ActionOnRigidSolid::ActionOnRigidSolid()
{}

ActionOnRigidSolid::ActionOnRigidSolid(Vect V, Point A)
{
	ActionOrigin = Torsor(A, V, Vect(0, 0, 0));
}

ActionOnRigidSolid::ActionOnRigidSolid(Vect Res, Vect Moment, Point A)
{
	ActionOrigin = Torsor(A, Res, Moment);
}

ActionOnRigidSolid::~ActionOnRigidSolid()
{}

Vect ActionOnRigidSolid::force()const
{
	return ActionOrigin.vectComponent();
}

void ActionOnRigidSolid::null() {ActionOrigin = Torsor::nullTorsor();}
/*
void ActionOnRigidSolid::add(MechanicalAction *A, MechanicalAction *result)
{
	addAction((ActionOnRigidSolid*)A, (ActionOnRigidSolid*)result);
}
void ActionOnRigidSolid::addAction(ActionOnRigidSolid *C, ActionOnRigidSolid *result)
{
	result->ActionOrigin = result->ActionOrigin + C->ActionOrigin;
}
*/


