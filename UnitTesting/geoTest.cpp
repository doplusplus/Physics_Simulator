#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Geo.h"
#include <limits>
#include <iostream> 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GeoTest
{
	TEST_CLASS(CartesianTest)
	{
	public:
		TEST_METHOD(Nullity)
		{
			CartesianElement C;

			C.nullify();

			Assert::IsTrue(C.xComponent() == 0);
			Assert::IsTrue(C.yComponent() == 0);
			Assert::IsTrue(C.zComponent() == 0);
		}

		// Element Creation tests--------------------------------------------
		TEST_METHOD(CreateCartesianElement_min200000_0_200000)
		{
			CartesianElement C(-200000, 0, 200000);

			Assert::IsTrue(C.xComponent() == -200000);
			Assert::IsTrue(C.yComponent() == 0);
			Assert::IsTrue(C.zComponent() == 200000);
		}

		TEST_METHOD(CreateCartesianElement_origin)
		{
			CartesianElement C(-200000, 0, 200000);

			Assert::IsTrue(C.xComponent() == -200000);
			Assert::IsTrue(C.yComponent() == 0);
			Assert::IsTrue(C.zComponent() == 200000);
		}

		TEST_METHOD(CreateCartesianElement_infRange_supRange_limitPrecision)
		{
			CartesianElement C(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			Assert::IsTrue(C.xComponent() == std::numeric_limits<double>::lowest());
			Assert::IsTrue(C.yComponent() == std::numeric_limits<double>::max());
			Assert::IsTrue(C.zComponent() == std::numeric_limits<double>::min());
		}


		//Element setting tests--------------------------------------------------------------------
		TEST_METHOD(PlaceTest_infRange_supRange_limitPrecision)
		{
			CartesianElement C;

			C.place(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			Assert::IsTrue(C.xComponent() == std::numeric_limits<double>::lowest());
			Assert::IsTrue(C.yComponent() == std::numeric_limits<double>::max());
			Assert::IsTrue(C.zComponent() == std::numeric_limits<double>::min());
		}

		//Operators tests--------------------------------------------------
		TEST_METHOD(AdditionTest_integers)
		{
			CartesianElement A(1000000, -2000000, 0);
			CartesianElement B(1, 1, 1);

			A = A + B;

			Assert::IsTrue(A.xComponent() == 1000001);
			Assert::IsTrue(A.yComponent() == -1999999);
			Assert::IsTrue(A.zComponent() == 1);
		}

		TEST_METHOD(AdditionTest_Doublelimits_suitableInterger)
		{
			CartesianElement A(1000000, -2000000, 0);
			CartesianElement B(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			A = A + B;

			Assert::IsTrue(A.xComponent() == std::numeric_limits<double>::lowest() + 1000000.0);
			Assert::IsTrue(A.yComponent() == std::numeric_limits<double>::max() - 2000000.0);
			Assert::IsTrue(A.zComponent() == std::numeric_limits<double>::min());
		}

		TEST_METHOD(AdditionTest_integerfraction)  //assumes compiler performs integer division
		{
			CartesianElement A(1000000 / 2, -2000001 / 2, 3);
			CartesianElement B(1000000 / 2, -2000001 / 2, 0);

			A = A + B;
			Assert::IsTrue(A.xComponent() == 1000000);
			Assert::IsTrue(A.yComponent() == -2000000);
			Assert::IsTrue(A.zComponent() == 3);
		}

		TEST_METHOD(multiplication_integersZero)
		{
			CartesianElement A(1000000, -2000000, 2);

			Assert::IsTrue((A * 0).xComponent() == 0);
			Assert::IsTrue((A * 0).yComponent() == 0);
			Assert::IsTrue((A * 0).zComponent() == 0);
		}

		TEST_METHOD(multiplication_doubleZero)
		{
			CartesianElement A(1000.04400, -2000.0300, 2.1);

			Assert::IsTrue((A * 0).xComponent() == 0);
			Assert::IsTrue((A * 0).yComponent() == 0);
			Assert::IsTrue((A * 0).zComponent() == 0);
		}

		TEST_METHOD(multiplication_doublelimit_Zero)
		{
			CartesianElement A(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			Assert::IsTrue((A * 0).xComponent() == 0);
			Assert::IsTrue((A * 0).yComponent() == 0);
			Assert::IsTrue((A * 0).zComponent() == 0);
		}

		TEST_METHOD(multiplication_doublelimit_One)
		{
			CartesianElement A(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			Assert::IsTrue((A * 1).xComponent() == std::numeric_limits<double>::lowest());
			Assert::IsTrue((A * 1).yComponent() == std::numeric_limits<double>::max());
			Assert::IsTrue((A * 1).zComponent() == std::numeric_limits<double>::min());
		}

		TEST_METHOD(multiplication_5CartesianElement5_bye2)
		{
			CartesianElement A(0.5, 0.555, 555555.55555);

			Assert::IsTrue((A * 2).xComponent() == 1);
			Assert::IsTrue((A * 2).yComponent() == 1.11);
			Assert::IsTrue((A * 2).zComponent() == 1111111.1111);
		}

		TEST_METHOD(divide_doubleatlimit_byOne)
		{
			CartesianElement A(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			Assert::IsTrue((A / 1).xComponent() == std::numeric_limits<double>::lowest());
			Assert::IsTrue((A / 1).yComponent() == std::numeric_limits<double>::max());
			Assert::IsTrue((A / 1).zComponent() == std::numeric_limits<double>::min());
		}

		TEST_METHOD(divide_doubleatlimit_by0) //Checks how division by zero is handled
		{
			CartesianElement A(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			try
			{
				A = A / 0;
			}
			catch (char *S)
			{
				std::cerr << S << '\n';
				A.nullify();
			}

			Assert::IsTrue(A.xComponent() == 0);
			Assert::IsTrue(A.yComponent() == 0);
			Assert::IsTrue(A.zComponent() == 0);

		}


		TEST_METHOD(divide_doubleat0_byLimits)
		{
			CartesianElement A(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());
			A.nullify();

			Assert::IsTrue((A / std::numeric_limits<double>::lowest()).xComponent() == 0);
			Assert::IsTrue((A / std::numeric_limits<double>::max()).yComponent() == 0);
			Assert::IsTrue((A / std::numeric_limits<double>::min()).zComponent() == 0);
		}
		//------------------------------------------------------------------------------------

	};

	TEST_CLASS(PointTests)
	{
	public:

		TEST_METHOD(Nullity)
		{
			Point P;

			P.nullify();

			Assert::IsTrue(P.xComponent() == 0);
			Assert::IsTrue(P.yComponent() == 0);
			Assert::IsTrue(P.zComponent() == 0);
		}

		TEST_METHOD(CreatePoint_min200000_0_200000)
		{
			Point P(-200000, 0, 200000);

			Assert::IsTrue(P.xComponent() == -200000);
			Assert::IsTrue(P.yComponent() == 0);
			Assert::IsTrue(P.zComponent() == 200000);
		}

		TEST_METHOD(CreatePoint_origin)
		{
			Point P(-200000, 0, 200000);

			Assert::IsTrue(P.xComponent() == -200000);
			Assert::IsTrue(P.yComponent() == 0);
			Assert::IsTrue(P.zComponent() == 200000);
		}

		TEST_METHOD(CreatePoint_infRange_supRange_limitPrecision)
		{
			Point P(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			Assert::IsTrue(P.xComponent() == std::numeric_limits<double>::lowest());
			Assert::IsTrue(P.yComponent() == std::numeric_limits<double>::max());
			Assert::IsTrue(P.zComponent() == std::numeric_limits<double>::min());
		}

		TEST_METHOD(PlaceTest_infRange_supRange_limitPrecision)
		{
			Point P;

			P.place(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			Assert::IsTrue(P.xComponent() == std::numeric_limits<double>::lowest());
			Assert::IsTrue(P.yComponent() == std::numeric_limits<double>::max());
			Assert::IsTrue(P.zComponent() == std::numeric_limits<double>::min());
		}

		TEST_METHOD(AdditionTest_integers)
		{
			Point A(1000000, -2000000, 0);
			Point B(1, 1, 1);

			A = A + B;

			Assert::IsTrue(A.xComponent() == 1000001);
			Assert::IsTrue(A.yComponent() == -1999999);
			Assert::IsTrue(A.zComponent() == 1);
		}

		TEST_METHOD(AdditionTest_Doublelimits_suitableInterger)
		{
			Point A(1000000, -2000000, 0);
			Point B(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			A = A + B;

			Assert::IsTrue(A.xComponent() == std::numeric_limits<double>::lowest() + 1000000.0);
			Assert::IsTrue(A.yComponent() == std::numeric_limits<double>::max() - 2000000.0);
			Assert::IsTrue(A.zComponent() == std::numeric_limits<double>::min());
		}

		TEST_METHOD(AdditionTest_integerfraction)  //assumes compiler performs integer division
		{
			Point A(1000000 / 2, -2000001 / 2, 3);
			Point B(1000000 / 2, -2000001 / 2, 0);

			A = A + B;
			Assert::IsTrue(A.xComponent() == 1000000);
			Assert::IsTrue(A.yComponent() == -2000000);
			Assert::IsTrue(A.zComponent() == 3);
		}

		TEST_METHOD(multiplication_integersZero)
		{
			Point A(1000000, -2000000, 2);

			Assert::IsTrue((A * 0).xComponent() == 0);
			Assert::IsTrue((A * 0).yComponent() == 0);
			Assert::IsTrue((A * 0).zComponent() == 0);
		}

		TEST_METHOD(multiplication_doubleZero)
		{
			Point A(1000.04400, -2000.0300, 2.1);

			Assert::IsTrue((A * 0).xComponent() == 0);
			Assert::IsTrue((A * 0).yComponent() == 0);
			Assert::IsTrue((A * 0).zComponent() == 0);
		}

		TEST_METHOD(multiplication_doublelimit_Zero)
		{
			Point A(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			Assert::IsTrue((A * 0).xComponent() == 0);
			Assert::IsTrue((A * 0).yComponent() == 0);
			Assert::IsTrue((A * 0).zComponent() == 0);
		}

		TEST_METHOD(multiplication_doublelimit_One)
		{
			Point A(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			Assert::IsTrue((A * 1).xComponent() == std::numeric_limits<double>::lowest());
			Assert::IsTrue((A * 1).yComponent() == std::numeric_limits<double>::max());
			Assert::IsTrue((A * 1).zComponent() == std::numeric_limits<double>::min());
		}

		TEST_METHOD(multiplication_5Point5_bye2)
		{
			Point A(0.5, 0.555, 555555.55555);

			Assert::IsTrue((A * 2).xComponent() == 1);
			Assert::IsTrue((A * 2).yComponent() == 1.11);
			Assert::IsTrue((A * 2).zComponent() == 1111111.1111);
		}

		TEST_METHOD(divide_doubleatlimit_byOne)
		{
			Point A(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			Assert::IsTrue((A / 1).xComponent() == std::numeric_limits<double>::lowest());
			Assert::IsTrue((A / 1).yComponent() == std::numeric_limits<double>::max());
			Assert::IsTrue((A / 1).zComponent() == std::numeric_limits<double>::min());
		}

		TEST_METHOD(divide_doubleatlimit_by0) //Checks how division by zero is handled
		{
			Point A(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			try
			{
				A = A / 0;
			}
			catch (char *S)
			{
				std::cerr << S << '\n';
				A.nullify();
			}

			Assert::IsTrue(A.xComponent() == 0);
			Assert::IsTrue(A.yComponent() == 0);
			Assert::IsTrue(A.zComponent() == 0);
		}


		TEST_METHOD(divide_doubleat0_byLimits)
		{
			Point A(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());
			A.nullify();

			Assert::IsTrue((A / std::numeric_limits<double>::lowest()).xComponent() == 0);
			Assert::IsTrue((A / std::numeric_limits<double>::max()).yComponent() == 0);
			Assert::IsTrue((A / std::numeric_limits<double>::min()).zComponent() == 0);
		}

		TEST_METHOD(HeapPointsAllocation)
		{
			Point *A = new Point(1, 2, 3);
			Point *B = new Point(1, 2, 3);
			Point *C = new Point(1, 2, 3);
			Point *D = new Point(1, 2, 3);

			A->trackAsHeap();
			B->trackAsHeap();
			C->trackAsHeap();
			D->trackAsHeap();

			Assert::IsTrue(Point::PointsHeapSize() == 4);
			Point::clearHeapPoints();
			Assert::IsTrue(Point::PointsHeapSize() == 0);
		}

		TEST_METHOD(EmptyHeapPoints)
		{
			Assert::IsTrue(Point::PointsHeapSize() == 0);
			Point::clearHeapPoints();
			Assert::IsTrue(Point::PointsHeapSize() == 0);
		}


	};

	TEST_CLASS(VectTests)
	{
	public:

		TEST_METHOD(VectNullity)
		{
			Vect P;

			P.nullify();

			Assert::IsTrue(P.xComponent() == 0);
			Assert::IsTrue(P.yComponent() == 0);
			Assert::IsTrue(P.zComponent() == 0);
		}

		TEST_METHOD(CreateVect_min200000_0_200000)
		{
			Vect P(-200000, 0, 200000);

			Assert::IsTrue(P.xComponent() == -200000);
			Assert::IsTrue(P.yComponent() == 0);
			Assert::IsTrue(P.zComponent() == 200000);
		}

		TEST_METHOD(CreateVect_origin)
		{
			Vect P(-200000, 0, 200000);

			Assert::IsTrue(P.xComponent() == -200000);
			Assert::IsTrue(P.yComponent() == 0);
			Assert::IsTrue(P.zComponent() == 200000);
		}

		TEST_METHOD(CreateVect_infRange_supRange_limitPrecision)
		{
			Vect P(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			Assert::IsTrue(P.xComponent() == std::numeric_limits<double>::lowest());
			Assert::IsTrue(P.yComponent() == std::numeric_limits<double>::max());
			Assert::IsTrue(P.zComponent() == std::numeric_limits<double>::min());
		}

		TEST_METHOD(setVectTest_infRange_supRange_limitPrecision)
		{
			Vect P;

			P.place(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			Assert::IsTrue(P.xComponent() == std::numeric_limits<double>::lowest());
			Assert::IsTrue(P.yComponent() == std::numeric_limits<double>::max());
			Assert::IsTrue(P.zComponent() == std::numeric_limits<double>::min());
		}

		TEST_METHOD(VectAdditionTest_integers)
		{
			Vect A(1000000, -2000000, 0);
			Vect B(1, 1, 1);

			A = A + B;

			Assert::IsTrue(A.xComponent() == 1000001);
			Assert::IsTrue(A.yComponent() == -1999999);
			Assert::IsTrue(A.zComponent() == 1);
		}

		TEST_METHOD(VectAdditionTest_Doublelimits_suitableInterger)
		{
			Vect A(1000000, -2000000, 0);
			Vect B(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			A = A + B;

			Assert::IsTrue(A.xComponent() == std::numeric_limits<double>::lowest() + 1000000.0);
			Assert::IsTrue(A.yComponent() == std::numeric_limits<double>::max() - 2000000.0);
			Assert::IsTrue(A.zComponent() == std::numeric_limits<double>::min());
		}

		TEST_METHOD(VectAdditionTest_integerfraction)  //assumes compiler performs integer division
		{
			Vect A(1000000 / 2, -2000001 / 2, 3);
			Vect B(1000000 / 2, -2000001 / 2, 0);

			A = A + B;
			Assert::IsTrue(A.xComponent() == 1000000);
			Assert::IsTrue(A.yComponent() == -2000000);
			Assert::IsTrue(A.zComponent() == 3);
		}

		TEST_METHOD(Vectmultiplication_integersZero)
		{
			Vect A(1000000, -2000000, 2);
			A = (CartesianElement)A * 0;

			Assert::IsTrue(A.xComponent() == 0);
			Assert::IsTrue(A.yComponent() == 0);
			Assert::IsTrue(A.zComponent() == 0);
		}

		TEST_METHOD(Vectmultiplication_doubleZero)
		{
			Vect A(1000.04400, -2000.0300, 2.1);
			A = (CartesianElement)A * 0;

			Assert::IsTrue(A.xComponent() == 0);
			Assert::IsTrue(A.yComponent() == 0);
			Assert::IsTrue(A.zComponent() == 0);
		}

		TEST_METHOD(Vectmultiplication_doublelimit_Zero)
		{
			Vect A(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());
			A = (CartesianElement)A * 0;

			Assert::IsTrue(A.xComponent() == 0);
			Assert::IsTrue(A.yComponent() == 0);
			Assert::IsTrue(A.zComponent() == 0);
		}

		TEST_METHOD(Vectmultiplication_doublelimit_One)
		{
			Vect A(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());
			A = (CartesianElement)A * 1;

			Assert::IsTrue(A.xComponent() == std::numeric_limits<double>::lowest());
			Assert::IsTrue(A.yComponent() == std::numeric_limits<double>::max());
			Assert::IsTrue(A.zComponent() == std::numeric_limits<double>::min());
		}

		TEST_METHOD(Vectmultiplication_5point5_bye2)
		{
			Vect A(0.5, 0.555, 555555.55555);
			A = (CartesianElement)A * 2;

			Assert::IsTrue(A.xComponent() == 1);
			Assert::IsTrue(A.yComponent() == 1.11);
			Assert::IsTrue(A.zComponent() == 1111111.1111);
		}

		TEST_METHOD(Vectdivide_doubleatlimit_byOne)
		{
			Vect A(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			Assert::IsTrue((A / 1).xComponent() == std::numeric_limits<double>::lowest());
			Assert::IsTrue((A / 1).yComponent() == std::numeric_limits<double>::max());
			Assert::IsTrue((A / 1).zComponent() == std::numeric_limits<double>::min());
		}

		TEST_METHOD(Vectdivide_doubleatlimit_by0) //Checks how division by zero is handled
		{
			Vect A(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			try
			{
				A = A / 0;
			}
			catch (char *S)
			{
				std::cerr << S << '\n';
				A.nullify();
			}

			Assert::IsTrue(A.xComponent() == 0);
			Assert::IsTrue(A.yComponent() == 0);
			Assert::IsTrue(A.zComponent() == 0);
		}


		TEST_METHOD(Vectdivide_doubleat0_byLimits)
		{
			Vect A(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());
			A.nullify();

			Assert::IsTrue((A / std::numeric_limits<double>::lowest()).xComponent() == 0);
			Assert::IsTrue((A / std::numeric_limits<double>::max()).yComponent() == 0);
			Assert::IsTrue((A / std::numeric_limits<double>::min()).zComponent() == 0);
		}


		TEST_METHOD(VectEquality)
		{
			Vect A(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());
			Vect B(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			Assert::IsTrue(A == B);
		}

		TEST_METHOD(VectInequality)
		{
			Vect A(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());
			Vect B(std::numeric_limits<double>::lowest() + 1, std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			Assert::IsTrue(A == B);
		}
	};




}
