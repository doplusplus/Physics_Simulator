#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SimModule2\PhysicalElement.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PhysTest
{
	TEST_CLASS(ForceTest)
	{
	public:

		TEST_METHOD(ForceConstructor)
		{
			Vect V(1, 1, 1), C(1, 1, 1);
			Point P;
			P.nullify();

			Force F(P, V);
			Assert::IsTrue(F.getApplicationPoint() == &P);
			Assert::IsTrue(F.getDirection() == C);
		}

		TEST_METHOD(applicationCheck)
		{
			Point P(1, 2, 3);
			Vect V;
			V.nullify();

			Force F(P, V);
			Assert::IsTrue((*(F.getApplicationPoint())).getX() == 1);
		}

		TEST_METHOD(ApplicationSetterTest)
		{
			Point P(1, 2, 3), J(4, 5, 6);
			Point * app = &J;
			Vect V;
			V.nullify();
			Force F(P, V);

			F.setApplication(app);
			Assert::IsTrue((*F.getApplicationPoint()).getX() == 4);
			Assert::IsTrue((*F.getApplicationPoint()).getY() == 5);
			Assert::IsTrue((*F.getApplicationPoint()).getZ() == 6);
		}

		TEST_METHOD(DirectionSetterTest)
		{
			Point P;
			P.nullify();
			Vect V(1, 2, 3), S(4, 5, 6);
			Force F(P, V);

			F.setDirection(S);
			Assert::IsTrue(F.getDirection().getX() == 4);
			Assert::IsTrue(F.getDirection().getY() == 5);
			Assert::IsTrue(F.getDirection().getZ() == 6);
		}

		TEST_METHOD(DirectionSetterTest2)
		{
			Point P;
			P.nullify();
			Vect V(1, 2, 3), S(4, 5, 6);
			Force F(P, V), G;

			F.setDirection(S);
			G.setDirection(4, 5, 6);

			Assert::IsTrue(F.getDirection().getX() == G.getDirection().getX());
			Assert::IsTrue(F.getDirection().getY() == G.getDirection().getY());
			Assert::IsTrue(F.getDirection().getZ() == G.getDirection().getZ());
		}

		TEST_METHOD(ForceAddition)
		{
			Point A(0, 34.606, 299.5), B(-1, 1, 0.5);
			Vect Va(1, 2, 3), Vb(4, 5, 6);
			Force Fa(A, Va), Fb(B, Vb);
			Fa + Fb;

			Assert::IsTrue(Fa.getDirection().getX() == 5);
			Assert::IsTrue(Fa.getDirection().getY() == 7);
			Assert::IsTrue(Fa.getDirection().getZ() == 9);

			Assert::IsTrue(Fa.getApplicationPoint()->getX() == -0.5);
			Assert::IsTrue(Fa.getApplicationPoint()->getY() == 17.803);
			Assert::IsTrue(Fa.getApplicationPoint()->getZ() == 150);
		}

		TEST_METHOD(OppositeForce)
		{
			Point A(0, 34.606, 299.5);
			Vect Va(1, 2.3, 3);
			Force Fa(A, Va);
			Fa = -Fa;

			Assert::IsTrue(Fa.getDirection().getX() == -1);
			Assert::IsTrue(Fa.getDirection().getY() == -2.3);
			Assert::IsTrue(Fa.getDirection().getZ() == -3);

			Assert::IsTrue(Fa.getApplicationPoint()->getX() == 0);
			Assert::IsTrue(Fa.getApplicationPoint()->getY() == 34.606);
			Assert::IsTrue(Fa.getApplicationPoint()->getZ() == 299.5);
		}

		/*		
		TEST_METHOD()
				{

				}
		*/

	};

	TEST_CLASS(VelocityTest)
	{
	public:

		TEST_METHOD(VelocityConstructor)
		{
			Vect V(1, 1, 1), C(1, 1, 1);
			Point P;
			P.nullify();

			Velocity Vel(P, V);
			Assert::IsTrue(Vel.getApplicationPoint() == &P);
			Assert::IsTrue(Vel.getDirection() == C);
		}

		TEST_METHOD(applicationCheck)
		{
			Point P(1, 2, 3);
			Vect V;
			V.nullify();

			Velocity Vel(P, V);
			Assert::IsTrue((*(Vel.getApplicationPoint())).getX() == 1);
		}

		TEST_METHOD(ApplicationSetterTest)
		{
			Point P(1, 2, 3), J(4, 5, 6);
			Point * app = &J;
			Vect V;
			V.nullify();
			Velocity Vel(P, V);

			Vel.setApplication(app);
			Assert::IsTrue((*Vel.getApplicationPoint()).getX() == 4);
			Assert::IsTrue((*Vel.getApplicationPoint()).getY() == 5);
			Assert::IsTrue((*Vel.getApplicationPoint()).getZ() == 6);
		}

		TEST_METHOD(DirectionSetterTest)
		{
			Point P;
			P.nullify();
			Vect V(1, 2, 3), S(4, 5, 6);
			Velocity Vel(P, V);

			Vel.setDirection(S);
			Assert::IsTrue(Vel.getDirection().getX() == 4);
			Assert::IsTrue(Vel.getDirection().getY() == 5);
			Assert::IsTrue(Vel.getDirection().getZ() == 6);
		}

		TEST_METHOD(DirectionSetterTest2)
		{
			Point P;
			P.nullify();
			Vect V(1, 2, 3), S(4, 5, 6);
			Velocity Vel(P, V), G;

			Vel.setDirection(S);
			G.setDirection(4, 5, 6);

			Assert::IsTrue(Vel.getDirection().getX() == G.getDirection().getX());
			Assert::IsTrue(Vel.getDirection().getY() == G.getDirection().getY());
			Assert::IsTrue(Vel.getDirection().getZ() == G.getDirection().getZ());
		}


		/*
		TEST_METHOD()
		{

		}
		*/



	};



}
