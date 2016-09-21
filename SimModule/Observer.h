#pragma once

#include "MaterialElement.h"
#include "Calculator.h"
#include "MechanicalAction.h"
#include <iostream>
#include <string>

class  Observer
{
public:
	Observer(Calculator &C, Vect initVelocity, Point initPosition) :Calc(C), CenterOfMassVelocity(initVelocity), CenterOfMassPosition(initPosition) {};
	~Observer();

	virtual std::string getDescription() const { return "element description"; };
	virtual std::vector<double> streamCoord() const = 0;

	virtual Point position(double dt = 0) const = 0;
	virtual void changePosition(Point newPos) { CenterOfMassPosition = newPos; };

	virtual Vect  velocity() const { return CenterOfMassVelocity; }

	virtual bool operator ==(const Observer & obs) const;

	virtual  Point incrementedPos(double time, double dt, int SampSize) const     { return this->position(); } ////////
	virtual  Vect incrementedOrientation(double time, double dt, int SampSize) const { return Vect(0, 0, 0); } /////

	virtual void increment(double currentTime, double dt, double precision) = 0;
	virtual void incrementRT(double dt) = 0;
	virtual std::vector<double> descriptionStream() const = 0;

protected:
	Calculator& Calc;
	Vect		CenterOfMassVelocity;	// m/s
	Point		CenterOfMassPosition;	// m 
};

class MaterialPointObserver :public Observer
{
public:
	MaterialPointObserver(MaterialPoint &Mp, Calculator &C, Point position, Vect initVelocity) :Observer(C, initVelocity, position), Element(Mp) {};
	~MaterialPointObserver();

	Point position(double dt) const;
	

	std::vector<double> streamCoord() const { return CenterOfMassPosition.coordStream(); };
	std::vector<double> descriptionStream() const;

	void increment(double currentTime, double dt, double precision);
	void incrementRT(double dt);
	bool operator ==(const MaterialPointObserver & obs);

	Vect  resultant(double t = 0) const;
	std::vector <Vect> resultants(double currentTime, double dt, int n); //n intervals, n+1 points

	void addAction(std::shared_ptr<ActionOnPoint> &action);


protected:
	MaterialPoint& Element;
};

class RigidSolidObserver //:public Observer
{

	Torsor Resultant(double time) {};
protected:
	RigidSolid& Element;

};