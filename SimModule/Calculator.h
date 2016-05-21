#pragma once

#include <iostream>
#include <vector>
#include <algorithm> 
#include "Scene.h"
#include "Geo.h"
#include "Torsor.h"
#include "MechanicalAction.h"

class Calculator
{
public:
	Calculator();
	Calculator(double accuracy, double range);
	~Calculator();

	/*	void resultant(std::vector<MechanicalAction*> setOfT, MechanicalAction* result);
		std::shared_ptr<MechanicalAction> resultant(std::vector<MechanicalAction* > setOfT)
		{
			auto Res = std::shared_ptr<MechanicalAction>(setOfT[0]->copy());
			for (unsigned int i = 1; i < setOfT.size();i++)
			{
				*Res +=  *setOfT[i];
			}
			return Res;
		};
	*/
	Vect centerOfMassAcceleration(Vect resultant, double mass) const;
	//	Vect centerOfMassAcceleration(std::vector<MechanicalAction* > extActions, double mass);

	Vect positionVariationCoM(Vect acceleration, Vect currentVelocity, double dt)const;
	Vect velocityVariationCoM(Vect acceleration, double dt)const;

	template <typename T>
	std::vector <T> finDiffIntegration(std::vector<T> toIntegrate, double step);
	int samplesNb(double accuracy, double duration) 
	{
		int n= (int)(duration/std::sqrt(accuracy));
		return (n*1E-14) < accuracy ? n : static_cast<int>(accuracy * 1E14);
	}

private:
	double Accuracy;
	double Range;

};

template<typename T>
inline std::vector<T> Calculator::finDiffIntegration(std::vector<T> toIntegrate, double step)
{
	std::vector<T> res;
	res.push_back(T().null());

	for (unsigned int it = 0; it < toIntegrate.size() - 1; it++)
	{
		auto val = ((toIntegrate[it] + toIntegrate[it + 1])*0.5)*step + res[it];
		res.push_back(val);
	}

	return res;
}
