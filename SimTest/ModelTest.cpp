#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SimModule\Model.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	const double accuracy = double(1e-10); //approximately the diameter of an hydrogen atom in meter
	const double rangeOfInterest = 384467000; //approximately the earth to moon distance


	TEST_CLASS(ModelTest)
	{
	public:
		
/*		TEST_METHOD(FreeFallOnEarth_at_1kg)
		{
			Model M;
			double FallTime = 10;	//seconds
			double mass = 1;		//kg	
			const double earthGravity = 9.81;
			Vect G(0, 0, mass*earthGravity);

			M.addMatPoint(Point(0, 0, 0), Vect(0, 0, 0), mass);
			M.addActionOnPoint(0, G);
			M.simulate(FallTime, 1);
			M.showScene();

			Assert::IsTrue((M.getElementPosition(0) - Point(0, 0, 0.5*earthGravity*FallTime*FallTime))<Point(accuracy,accuracy,accuracy));
		}
*/
	};
}