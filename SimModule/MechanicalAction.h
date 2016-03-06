#pragma once

#include "Geo.h"
#include "Torsor.h"
#include <memory>

class MechanicalAction
{
public:
	MechanicalAction() {};
	virtual ~MechanicalAction() {};
	virtual void null() = 0;
	virtual void show() = 0;

	virtual Vect force() = 0;
	virtual void add(MechanicalAction *A, MechanicalAction *result) = 0;
	virtual void add(std::shared_ptr<MechanicalAction> A) = 0;

	virtual MechanicalAction* copy() = 0;

};



class ActionOnPoint :public MechanicalAction
{
public:
	ActionOnPoint();
	ActionOnPoint(double x, double y, double z);
	ActionOnPoint(Vect action, Vect timeBase = Vect(0, 0, 0),
		Vect spaceBase = Vect(0, 0, 0), Vect(*timeDiff_)(Vect, double) = Vect::constant,
		Vect(*spaceDiff_)(Vect, double) = Vect::constant);
/*	ActionOnPoint(std::shared_ptr<ActionOnPoint> A)
	{
		Action = A->Action;
		TimeBase = A->TimeBase;
		SpaceBase = A->SpaceBase;
		TimeDerivative = A->TimeDerivative;
		SpaceDerivative = A->SpaceDerivative;
	};
*/
	~ActionOnPoint();

	void null();
	void show();

	void add(MechanicalAction *A, MechanicalAction *result);
	void add(std::shared_ptr<MechanicalAction> A)
	{
		ActionOnPoint a= * std::static_pointer_cast<ActionOnPoint>(A);

		Action = Action + a.Action;
		TimeBase = TimeBase + a.TimeBase;
		SpaceBase = SpaceBase + a.SpaceBase;

		//TimeDerivative = 

	};


	void addAction(ActionOnPoint *C, ActionOnPoint *result);
	MechanicalAction* copy();

	Vect force();
	Vect variation(double t, double dt,
		Vect tBase = Vect(0, 0, 0), Vect sBase = Vect(0, 0, 0));
	void forward(double t, double dt);

	bool operator ==(ActionOnPoint P)
	{
		bool b = Action == P.Action&&TimeBase == P.TimeBase&&SpaceBase == P.SpaceBase
			&&TimeDerivative == P.TimeDerivative&&SpaceDerivative == P.SpaceDerivative;
		return b;
	};

private:
	Vect Action = Vect(0, 0, 0);
	Vect TimeBase = Vect(0, 0, 0);
	Vect SpaceBase = Vect(0, 0, 0);
	Vect(*TimeDerivative)(Vect, double) = Vect::constant;
	Vect(*SpaceDerivative)(Vect, double) = Vect::constant;
};

class ActionOnSolid :public MechanicalAction
{
public:
	ActionOnSolid();
	ActionOnSolid(Vect V, Point A);
	ActionOnSolid(Vect V, Vect M, Point A);
	ActionOnSolid(Torsor T) { Action = T; };
	~ActionOnSolid();

	Vect force();
	void null() { Action = Torsor::nullTorsor(); };
	void show() { Action.show(); };
	MechanicalAction* copy()
	{
		MechanicalAction* ptr = new ActionOnSolid(*this);
		return ptr;
	}
	void add(MechanicalAction *A, MechanicalAction *result);
	void add(std::shared_ptr<MechanicalAction> A) {};

	void addAction(ActionOnSolid *C, ActionOnSolid *result);

private:
	Torsor Action = Torsor::nullTorsor();
};


