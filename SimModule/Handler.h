#pragma once

#include "MaterialElement.h"
#include "Calculator.h"
#include "MechanicalAction.h"
#include <iostream>
#include <string>

class  MaterialElementHandler
{
public:
	MaterialElementHandler();
	~MaterialElementHandler();

	virtual void forward(double dt) = 0;
	virtual void show();
	virtual std::string getDescription() { return "element description"; };
	void setCalculator(Calculator *C);
	virtual Point position() = 0;

protected:
	Calculator *Calc;
};

class MaterialPointHandler :public MaterialElementHandler
{
public:

	MaterialPointHandler(MaterialPoint *Mp, Calculator *C);
	MaterialPointHandler(MaterialPoint *Mp, Calculator *C, std::vector< MechanicalAction* > &A);
	~MaterialPointHandler() ;

	void forward(double dt);
	void addAction(ActionOnPoint* action);
	void show();
	Point position() { return Element->CenterOfMassPosition; }
	std::string getDescription() 
	{
		std::string s = "mass: " + std::to_string(Element->Mass) +(Element->CenterOfMassPosition.getDescription())+"External Actions: ";
		for (auto a : ExternalActions) { s += a->force().getDescription(); }
		return s;
	};

	bool contentEquals(MaterialPoint M)
	{
			bool b= Element->Mass==M.Mass;
			b = b && Element->Charge == M.Charge;
			b = b && Element->CenterOfMassPosition == M.CenterOfMassPosition;
			b = b&& Element->CenterOfMassVelocity == M.CenterOfMassVelocity;
			return b;
	}

	bool contentEquals(MaterialPointHandler Mp)
	{
		return contentEquals(*Mp.Element);
	}
	
private:
	MaterialPoint* Element;
	std::vector< MechanicalAction* >	ExternalActions;
};