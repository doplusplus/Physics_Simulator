#pragma once

#include "Geo.h"
#include "Torsor.h"

class MechanicalAction
{
public:
	MechanicalAction() {};
	virtual ~MechanicalAction() {};
	virtual void null() = 0;
	virtual void add(MechanicalAction *A, MechanicalAction *result) = 0;
	virtual void show() = 0;
	virtual Vect force()=0;
	virtual MechanicalAction* copy()=0;
};

class ActionOnPoint :public MechanicalAction
{
public:
	ActionOnPoint();
	ActionOnPoint(double x, double y, double z);
	ActionOnPoint(Vect Action, Vect TimeBase = Vect(0, 0, 0),
		Vect SpaceBase = Vect(0, 0, 0), Vect(*timeDiff)(Vect, double) = Vect::constant,
		Vect(*spaceDiff)(Vect, double) = Vect::constant);
	~ActionOnPoint();

	void null();
	void show();
	void add(MechanicalAction *A, MechanicalAction *result);
	void addAction(ActionOnPoint *C, ActionOnPoint *result);
	MechanicalAction* copy() 
	{
		MechanicalAction* ptr=new ActionOnPoint(*this);
		return ptr;
	}
	Vect force();
	Vect differential(double t, double dt,
				Vect tBase = Vect(0, 0, 0), Vect sBase = Vect(0, 0, 0));
	void forward(double t, double dt);

private:
	Vect Action = Vect(0, 0, 0);
	Vect TimeBase = Vect(0, 0, 0);
	Vect SpaceBase = Vect(0, 0, 0);
	Vect(*TimeDifferential)(Vect, double) = Vect::constant;
	Vect(*SpaceDifferential)(Vect, double) = Vect::constant;
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
	void addAction(ActionOnSolid *C, ActionOnSolid *result);

private:
	Torsor Action = Torsor::nullTorsor();
};


