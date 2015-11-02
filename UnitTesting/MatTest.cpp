#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SimModule2\MaterialElement.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MatElementTest
{		
	TEST_CLASS(MatTest1)
	{
	public:
		
		TEST_METHOD(ElementConstruction)
		{
			MaterialElement M;
			Point P(1,2,3),*C;
			C = M.pointerToPosition();

			M.setPosition(P);
			M.setMass(2002020202.333);
			M.setCharge(2.3423);

			Assert::AreEqual(M.getMass(), 2002020202.333);
			Assert::AreEqual(M.getCharge(), 2.3423);
			Assert::AreEqual(P.getX(), (*M.pointerToPosition()).getX());
			Assert::AreEqual(P.getY(), (*M.pointerToPosition()).getY());
			Assert::AreEqual(P.getZ(), (*M.pointerToPosition()).getZ());
		}

		TEST_METHOD(MassLess)
		{
			MaterialElement M;
			
			Point P(1, 2, 3), *C;
			C = M.pointerToPosition();
			M.setPosition(P);

			Vect V(4, 5, 6);
			Force F;
			F.setApplication(C);
			F.setDirection(V);
			
			M.update(2345.8778);

			double x = (M.getAcceleration().getDirection()).getX();
			double y = (M.getAcceleration().getDirection()).getY();
			double z = (M.getAcceleration().getDirection()).getZ();
			
			Assert::AreEqual(0.0, x);
			Assert::AreEqual(0.0, y);
			Assert::AreEqual(0.0, z);
		}

		TEST_METHOD(Accel_AllSetatUnit)
		{
			MaterialElement M;

			Point P(0, 0, 0), *C;
			C = M.pointerToPosition();
			M.setPosition(P);

			M.setMass(1);

			Vect V(1, 1, 1);
			Force F;
			F.setApplication(C);
			F.setDirection(V);
			
			M.setResultant(F);
			M.update(1);

			double x = (M.getAcceleration().getDirection()).getX();
			double y = (M.getAcceleration().getDirection()).getY();
			double z = (M.getAcceleration().getDirection()).getZ();

			Assert::AreEqual(1.0, x);
			Assert::AreEqual(1.0, y);
			Assert::AreEqual(1.0, z);
		}

		TEST_METHOD(Position_AllSetatUnit)
		{
			MaterialElement M;

			Point P(0, 0, 0), *C;
			C = M.pointerToPosition();
			M.setPosition(P);

			M.setMass(1);

			Vect V(1, 1, 1);
			Force F;
			F.setApplication(C);
			F.setDirection(V);

			M.setResultant(F);
			M.update(1);

			double x = M.pointerToPosition()->getX();
			double y = M.pointerToPosition()->getY();
			double z = M.pointerToPosition()->getZ();

			Assert::AreEqual(0.5, x);
			Assert::AreEqual(0.5, y);
			Assert::AreEqual(0.5, z);
		}

	};
}
