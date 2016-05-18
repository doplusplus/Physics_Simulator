#pragma once

#include "Geo.h"
#include "Torsor.h"
#include <memory>
#include <functional>

class MechanicalAction
{
public:
	MechanicalAction() {};
	virtual ~MechanicalAction() {};

	virtual void null() = 0;
	virtual void show() const = 0;
};



class ActionOnPoint :public MechanicalAction
{
	friend struct customLess_ActionOnPoint;

public:
	ActionOnPoint(const Vect &action , const Vect &timeBase ,
		const Vect &xBase , const Vect &yBase, const Vect &zBase , Vect(*timeDiff_)(Vect, double) ,
		double(*xDiff_)(Vect, Vect), double(*yDiff_)(Vect, Vect) , double(*zDiff_)(Vect, Vect));

	ActionOnPoint(const Vect &action = Vect(0, 0, 0), const Vect &timeBase = Vect(0, 0, 0),
		const Vect &spaceBase = Vect(0, 0, 0), Vect(*timeDiff_)(Vect, double) = Vect::constant,
		double(*spaceDiff_)(Vect, Vect) = Vect::Vconstant);

	ActionOnPoint(const ActionOnPoint & toCopy);
	ActionOnPoint& operator=(const ActionOnPoint &toAssign);
	~ActionOnPoint();

	std::tuple<Vect, Vect, Vect, Vect, Vect> base() const ;
	Vect force(Vect Position, double t) const;
	Vect variation(Vect Position, double t, Vect tBase, Vect xBase, Vect yBase, Vect zBase)const;	
	void show() const;
	void null();

	bool operator ==(const ActionOnPoint &P) const;

private:
	// Force at t=x=y=z=0
	Vect ActionOrigin;  
							
	//Time dependency
	Vect TimeBase;		
	std::function<Vect(Vect, double)> TimeVariation;

	//Space dependencies
	Vect XBase;     
	std::function<double(Vect, Vect)> XVariation;

	Vect YBase;
	std::function<double(Vect, Vect)> YVariation;

	Vect ZBase;
	std::function<double(Vect, Vect)> ZVariation;
};

struct customLess_ActionOnPoint {
	bool operator()(std::shared_ptr<ActionOnPoint> A, std::shared_ptr<ActionOnPoint> B);
};

class ActionOnRigidSolid :public MechanicalAction
{
public:
	ActionOnRigidSolid();
	ActionOnRigidSolid(Vect V, Point A);
	ActionOnRigidSolid(Vect V, Vect M, Point A);
	ActionOnRigidSolid(Torsor T) { ActionOrigin = T; };
	~ActionOnRigidSolid();

	Vect force() const;
	void show() const { ActionOrigin.show(); };

	void null();
	
	/*void add(MechanicalAction *A, MechanicalAction *result);
	void add(std::shared_ptr<MechanicalAction> A) {};
	void addAction(ActionOnRigidSolid *C, ActionOnRigidSolid *result);
	*/
private:
	Torsor ActionOrigin = Torsor::nullTorsor();
};


