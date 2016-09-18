#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SimModule\Torsor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TorsorTest)
	{
	public:
		
		TEST_METHOD(Access)
		{
			Point P(0.00099292, 1231.241, -232.3442423);
			Vect Res(1, 1, 1);
			Vect Momnt(2, 5, 3);

			Torsor Tst(P, Res, Momnt);
			
			Assert::IsTrue(Tst.vectComponent() == Res);
			Assert::IsTrue(Tst.moment() == Momnt);
			Assert::IsTrue(Tst.applicationPoint() == P);
		}

		TEST_METHOD(Division)
		{
			Point P(0.00099292, 1231.241, -232.3442423);
			Vect Res(1, 1, 1);
			Vect Momnt(2, 5, 3);

			double div = 3.4343;
			Torsor Tst(P, Res, Momnt);
			Tst.divideResultant(div);

			Assert::IsTrue(Tst.vectComponent() == Res/div);
		}

		TEST_METHOD(MomentTransport)
		{
			Point P(10,0,0);
			Vect Res(0, 8, 0);
			Vect Momnt(2, 5, 3);
			Torsor Tst(P, Res, Momnt);

			Assert::IsTrue(Tst.momentAt(Point(0, 0, 0)) == Momnt + Vect(0, 0, 80));
		}

		TEST_METHOD(TorsorAddition)
		{
			Point P(10, 0, 0);
			Vect Res(0, 8, 0);
			Vect Momnt(2, 5, 3);
			Torsor A(P, Res, Momnt);

			Point Pb(10, 0, 0);
			Vect Resb(0, 8, 0);
			Vect Momntb(2, 5, 3);
			Torsor B(Pb, Resb, Momntb);

			Point Pc(10, 0, 0);
			Vect Resc(0, 16, 0);
			Vect Momntc(4, 10, 6);
			Torsor C(Pc, Resc, Momntc);

			Assert::IsTrue(A + B == C);
		}


	};
}