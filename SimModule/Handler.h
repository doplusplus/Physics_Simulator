#pragma once

#include "MaterialElement.h"
#include "Calculator.h"
#include "MechanicalAction.h"
#include <iostream>

class  MaterialElementHandler
{
public:
	MaterialElementHandler();
	~MaterialElementHandler();

	virtual void forward(double dt) = 0;
	virtual void show();
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
	Point position() { return Element->centerOfMassPosition(); }

	bool contentEquals(MaterialPoint M)
	{
		return *Element == M;
	}
	bool contentEquals(MaterialPointHandler Mp)
	{
		return contentEquals(*Mp.Element);
	}

private:
	MaterialPoint* Element;
	std::vector< MechanicalAction* >	ExternalActions;
};