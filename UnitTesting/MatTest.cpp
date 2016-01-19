#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\MaterialElement.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MatElementTest
{
	TEST_CLASS(MatTest1)
	{
	public:

		TEST_METHOD(settersTest)
		{
			MaterialElement M;
			Point P(1, 2, 3);

			M.place(P);
			M.setMass(2002020202.333);
			M.setCharge(2.3423);

			Assert::AreEqual(M.getMass(), 2002020202.333);
			Assert::AreEqual(M.getCharge(), 2.3423);
			Assert::AreEqual(P.xComponent(), M.pointerToPosition()->xComponent());
			Assert::AreEqual(P.yComponent(), M.pointerToPosition()->yComponent());
			Assert::AreEqual(P.zComponent(), M.pointerToPosition()->zComponent());
		}

		TEST_METHOD(ZeroMassException)
		{
			auto func = []() 
			{
				MaterialElement M;
				Point P(1, 2, 3);
				M.place(P);
				M.update(123);
			};
			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(Acceleration_at_unitForce)
		{
			MaterialElement M;
			Point P(0, 0, 0);
			M.place(P);
			M.setMass(1);

			Vect F(1, 1, 1);
			M.addExternalAction(F);
			M.update(1);

			double x = M.Acceleration().xComponent();
			double y = M.Acceleration().yComponent();
			double z = M.Acceleration().zComponent();

			Assert::AreEqual(1.0, x);
			Assert::AreEqual(1.0, y);
			Assert::AreEqual(1.0, z);
		}

		TEST_METHOD(Position_at_unitForce)
		{
			MaterialElement M;

			Point P(0, 0, 0);
			M.place(P);
			M.setMass(1);

			Vect F(1, 1, 1);
			M.addExternalAction(F);
			M.update(1);

			double x = M.pointerToPosition()->xComponent();
			double y = M.pointerToPosition()->yComponent();
			double z = M.pointerToPosition()->zComponent();

			Assert::AreEqual(0.5, x);
			Assert::AreEqual(0.5, y);
			Assert::AreEqual(0.5, z);
		}

		TEST_METHOD(Position_at_10kg_10sec_underGravity)
		{
			MaterialElement M;
			double accuracy = 0.000001;
			double expectedZ = 490.5;

			Point P(0, 0, 0);
			M.place(P);
			M.setMass(10); //kg

			Vect F(0, 0, 98.1); // force set to gravity * mass

			M.addExternalAction(F);
			M.update(10);  //seconds

			double x = M.pointerToPosition()->xComponent();
			double y = M.pointerToPosition()->yComponent();
			double z = M.pointerToPosition()->zComponent();

			Assert::AreEqual(0.0, x);
			Assert::AreEqual(0.0, y);
			Assert::IsTrue(abs(z - expectedZ) < accuracy);
		}


	};
}
