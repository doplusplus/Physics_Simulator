#pragma once

#include "Geo.h"
#include "Torsor.h"

 class MechanicalAction
{
public:
	MechanicalAction() {};
	virtual ~MechanicalAction() {};
	virtual void null()=0;
	virtual void add(MechanicalAction *A, MechanicalAction *result)=0;
	virtual void show() = 0;
};

class ActionOnPoint:public MechanicalAction
{
public:
	ActionOnPoint();
	ActionOnPoint(double x, double y, double z);
	ActionOnPoint(Vect V);
	~ActionOnPoint();

	void null() { Action = Vect(0, 0, 0); };
	void show() { Action.show(); };

	void add(MechanicalAction *A, MechanicalAction *result)
	{
		addAction((ActionOnPoint*)A, (ActionOnPoint*)result);
	}
	void addAction(ActionOnPoint *C, ActionOnPoint *result)
	{
		result->Action = result->Action + C->Action;
	};


	Vect force();

private:
	Vect Action = Vect(0, 0, 0);
//	Vect TimeDifferential; TBC
//	Vect SpaceDifferential;
};

class ActionOnSolid:public MechanicalAction
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

	void add(ActionOnSolid *A, ActionOnSolid *result)
	{
		result->Action = A->Action + result->Action;
	};

private:
	Torsor Action = Torsor::nullTorsor();
};


