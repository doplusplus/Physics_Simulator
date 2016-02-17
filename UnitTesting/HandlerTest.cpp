#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SimModule\Handler.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(HandlerTest)
	{
	public:
		
		TEST_METHOD(Position_at_unitForce)
		{
			Point P(0, 0, 0);
			double mass = 1;
			MaterialPoint M(P, Vect(0, 0, 0), mass);

			Vect F(1, 1, 1);
			//			M.addExternalAction(F);
			//			M.forward(1);

			//		Assert::IsTrue(*M.pointerToPosition() == Point(0.5, 0.5, 0.5));
		}

		TEST_METHOD(Position_at_10kg_10sec_underGravity)
		{
			double accuracy = 0.000001;
			double expectedZ = 490.5;

			Point P(0, 0, 0);
			double mass = 10;
			MaterialPoint M(P, Vect(0, 0, 0), mass);

			Vect F(0, 0, 98.1); // force set to gravity * mass

								//			M.addExternalAction(F);
								//			M.forward(10);  //seconds

								//	Assert::IsTrue(*M.pointerToPosition() == Point(0, 0, expectedZ));
		}

	};
}