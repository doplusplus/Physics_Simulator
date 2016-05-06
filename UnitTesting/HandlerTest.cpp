#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SimModule\Handler.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(MatPointTest)
	{
	public:

		TEST_METHOD(MovementNoActionNoSpeed)
		{
			double mass = 7;
			double timeStep = 0.1;

			Point P(0, 0, 0);
			MaterialPoint M(P, Vect(0, 0, 0), mass),clone=M;
			Vect F(1, 1, 1);
			Calculator C;

			MaterialPointHandler H(&M, &C);
			H.forward(timeStep);

			Assert::IsTrue(H.contentEquals(clone));
		}
	


		TEST_METHOD(Position_at_10kg_10sec_underGravity)
		{
			double accuracy = 0.000001;
			double expectedZ = 490.5;

			Point P(0, 0, 0);
			double mass = 10;
			MaterialPoint M(P, Vect(0, 0, 0), mass);

			Vect F(0, 0, 98.1);

			//	Assert::IsTrue(*M.pointerToPosition() == Point(0, 0, expectedZ));
		}

	};
}