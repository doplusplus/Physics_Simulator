#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SimModule\Calculator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(CalculatorTest)
	{
	public:

	/*	TEST_METHOD(ZeroMass)
		{
			Calculator C;

			auto f1 = [C] { return C.centerOfMassAcceleration(Vect(11,1.2, 20), 0); };
			Assert::ExpectException<std::invalid_argument>(f1);
		}

		TEST_METHOD(Static)
		{
			Calculator C;
			Assert::IsTrue(C.centerOfMassAcceleration(Vect(0,0,0),10)==Vect(0,0,0));
		}

		TEST_METHOD(gravity)
		{
			Calculator C;
			double mass = 10;
			Assert::IsTrue(C.centerOfMassAcceleration(Vect(0, 0, -9.81*mass), mass) == Vect(0, 0, -9.81));
		}

		TEST_METHOD(freeFallSpeed_10s)
		{
			Calculator C;
			double mass = 10;
			double dt = 10;
			Assert::IsTrue(C.velocityVariationCoM(C.centerOfMassAcceleration(Vect(0, 0, -9.81*mass), mass),dt)== Vect(0, 0, -9.81)*10);
		}
*/

	};
}