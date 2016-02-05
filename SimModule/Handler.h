#pragma once
#include "MaterialElement.h"
#include "Calculator.h"
#include "MechanicalAction.h"


class  MaterialElementHandler
{
public:
	MaterialElementHandler();
	~MaterialElementHandler();
	virtual void update(double dt) = 0;

protected:
	MaterialElement* Element;
	Calculator *Calc;
};


class MaterialPointHandler :public MaterialElementHandler
{
public:
	MaterialPointHandler() {};
	MaterialPointHandler(MaterialPoint *Mp, Calculator *C) { Element = Mp; Calc = C; };
	~MaterialPointHandler() {};

	void update(double dt);//TDF
	void addAction(ActionOnPoint* action) { ExternalActions.push_back(action); };

private:
	std::vector< MechanicalAction* >	ExternalActions;
};