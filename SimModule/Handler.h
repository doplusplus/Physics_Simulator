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

protected:
	Calculator *Calc;
};

class MaterialPointHandler :public MaterialElementHandler
{
public:
	MaterialPointHandler() {};
	MaterialPointHandler(MaterialPoint *Mp, Calculator *C);
	~MaterialPointHandler() ;

	void forward(double dt);
	void addAction(ActionOnPoint* action);
	void show();

private:
	MaterialPoint* Element;
	std::vector< MechanicalAction* >	ExternalActions;
};