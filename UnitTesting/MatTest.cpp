#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SimModule\MaterialElement.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MatElementTest
{
	TEST_CLASS(MatPointTest)
	{
	public:

		TEST_METHOD(ParameterlessMat)
		{
			MaterialPoint M;
			Point P(0, 0, 0);
			MaterialPoint N(P);
			Assert::IsTrue(M == N);
		}

		TEST_METHOD(PositionPointer)
		{
			MaterialPoint M;
			M.move(23.3243, 324, 546.7856);

			Assert::IsTrue(*M.pointerToPosition() == Point(23.3243, 324, 546.7856));
		}

		TEST_METHOD(moveTest)
		{
			Point P(1, 2, 3);
			Vect V(2.3, 3.3, 4.4);
			double mass = 2002020202.333;
			double charge = 2.3423;

			MaterialPoint M(P, V, mass, charge);
			M.move(-13233, .2232, -232.2333);

			Assert::IsTrue(M == MaterialPoint(Point(-13232, 2.2232, -229.2333), V, mass, charge));
		}

		TEST_METHOD(equality)
		{
			Point P(13223.3232, 3223.23233232, 23222323232.276473);
			Vect V(2, 3.123, 4342.4352314);
			double mass = 44555456.545545543;
			double charge = 27357357654567475666.3423;

			MaterialPoint M(P, V, mass, charge);

			Assert::IsTrue(M == M);
		}


		TEST_METHOD(ZeroMassException)
		{
			auto func = []()
			{
				Point P(1, 2, 3);
				MaterialPoint M(P);
				M.update(123);
			};
			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(Position_at_unitForce)
		{
			Point P(0, 0, 0);
			double mass = 1;
			MaterialPoint M(P, Vect(0, 0, 0), mass);

			Vect F(1, 1, 1);
			M.addExternalAction(F);
			M.update(1);

			Assert::IsTrue(*M.pointerToPosition() == Point(0.5, 0.5, 0.5));
		}

		TEST_METHOD(Position_at_10kg_10sec_underGravity)
		{
			double accuracy = 0.000001;
			double expectedZ = 490.5;

			Point P(0, 0, 0);
			double mass = 10;
			MaterialPoint M(P, Vect(0, 0, 0), mass);

			Vect F(0, 0, 98.1); // force set to gravity * mass

			M.addExternalAction(F);
			M.update(10);  //seconds

			Assert::IsTrue(*M.pointerToPosition() == Point(0, 0, expectedZ));
		}
	};


}