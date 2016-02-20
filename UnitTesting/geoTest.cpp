#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SimModule\Geo.h"
#include <limits>
#include <iostream> 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GeoTest
{
	const double accuracy = double(1e-10); //approximately the diameter of an hydrogen atom in meter
	const double rangeOfInterest = 384467000; //approximately the earth to moon distance

	const double LOWEST = std::numeric_limits<double>::lowest();
	const double MIN = std::numeric_limits<double>::min();
	const double MAX = std::numeric_limits<double>::max();

	TEST_CLASS(CartesianTest)
	{
	public:

		TEST_METHOD(ParameterlessCartesian)
		{
			CartesianElement C;
			Assert::IsTrue(C == CartesianElement(0, 0, 0));
		}

		TEST_METHOD(CopyConstructor)
		{
			CartesianElement C(1234142.124214, 2411.24, 45.4500000000787);
			CartesianElement Copied(C);

			Assert::IsTrue(C == Copied);
		}

		//Operators tests--------------------------------------------------
		TEST_METHOD(AdditionTest_integers)
		{
			CartesianElement A(1000000, -2000000, 0);
			CartesianElement B(1, 1, 1);

			Assert::IsTrue(A + B == CartesianElement(1000001, -1999999, 1));
		}

		TEST_METHOD(AdditionTest_Doublelimits_suitableInterger)
		{
			CartesianElement A(1000000, -2000000, 0);
			CartesianElement B(LOWEST, MAX, MIN);

			Assert::IsTrue(A + B ==
				CartesianElement(LOWEST + 1000000.0,
					MAX - 2000000.0,
					MIN
					)
				);
		}

		TEST_METHOD(AdditionTest_integerfraction)  //assumes compiler performs integer division
		{
			CartesianElement A(1000000 / 2, -2000001 / 2, 3);
			CartesianElement B(1000000 / 2, -2000001 / 2, 0);

			Assert::IsTrue(A + B == CartesianElement(1000000, -2000000, 3));
		}

		TEST_METHOD(multiplication_integersZero)
		{
			CartesianElement A(1000000, -2000000, 2);

			Assert::IsTrue(A * 0 == CartesianElement(0, 0, 0));
		}

		TEST_METHOD(multiplication_doubleZero)
		{
			CartesianElement A(1000.04400, -2000.0300, 2.1);

			Assert::IsTrue(A * 0 == CartesianElement(0, 0, 0));
		}

		TEST_METHOD(multiplication_integerLimits_Zero)
		{
			CartesianElement A(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::max(), std::numeric_limits<int>::min());

			Assert::IsTrue(A * 0 == CartesianElement(0, 0, 0));
		}

		TEST_METHOD(multiplication_doubleLimits_Zero)
		{
			CartesianElement A(LOWEST, MAX, MIN);

			Assert::IsTrue(A * 0 == CartesianElement(0, 0, 0));
		}

		TEST_METHOD(multiplication_doublelimit_One)
		{
			CartesianElement A(LOWEST, MAX, MIN);

			Assert::IsTrue(A * 1 ==
				CartesianElement(LOWEST,
					MAX,
					MIN
					)
				);
		}

		TEST_METHOD(multiplication_by2)
		{
			CartesianElement A(0.5, 0.555, 555555.55555);

			Assert::IsTrue(A * 2 == CartesianElement(1, 1.11, 1111111.1111));
		}

		TEST_METHOD(divide_doubleatlimit_byOne)
		{
			CartesianElement A(LOWEST, MAX, MIN);

			Assert::IsTrue(A / 1 ==
				CartesianElement(LOWEST,
					MAX,
					MIN
					)
				);
		}

		TEST_METHOD(divide_doubleatlimit_by0) //Checks how division by zero is handled
		{
			auto func = []()
			{
				CartesianElement A(LOWEST, MAX, MIN);
				A / 0;
			};

			Assert::ExpectException<const char[13]>(func);
		}
	};

	//============================================================================================
	TEST_CLASS(PointTests)
	{
	public:
		TEST_METHOD(ParameterlessPoint)
		{
			Point C;
			Assert::IsTrue(C == Point(0, 0, 0));
		}

		TEST_METHOD(PointCopyConstructor)
		{
			CartesianElement C(1234142.124214, 2411.24, 45.4500000000787);
			Point Copied(C);

			Assert::IsTrue(Point(1234142.124214, 2411.24, 45.4500000000787) == Copied);
		}

		//SPECIFIC TO POINT CLASS INTERFACE================================
		TEST_METHOD(VectToPoint)
		{
			Vect V(2, 352, .5643566);
			Point P(V);

			Assert::IsTrue(P == Point(2, 352, .5643566));
		}

		TEST_METHOD(ImagePoint)
		{
			Vect V(2, 352, .5643566);
			Point A(-35353, 342, 4);
			Point P(A, V);

			Assert::IsTrue(P == Point(-35351, 694, 4.5643566));
		}
		//===============================================================================
		// Element Creation tests--------------------------------------------


		//Operators tests--------------------------------------------------
		TEST_METHOD(AdditionTest_integers_Point)
		{
			Point A(1000000, -2000000, 0);
			Point B(1, 1, 1);

			Assert::IsTrue(A + B == Point(1000001, -1999999, 1));
		}

		TEST_METHOD(AdditionTest_Doublelimits_suitableInterger)
		{
			Point A(1000000, -2000000, 0);
			Point B(LOWEST, MAX, MIN);

			Assert::IsTrue(A + B ==
				Point(LOWEST + 1000000.0,
					MAX - 2000000.0,
					MIN
					)
				);
		}

		TEST_METHOD(AdditionTest_integerfraction_Point)  //assumes compiler performs integer division
		{
			Point A(1000000 / 2, -2000001 / 2, 3);
			Point B(1000000 / 2, -2000001 / 2, 0);

			Assert::IsTrue(A + B == Point(1000000, -2000000, 3));
		}

		TEST_METHOD(multiplication_integersZero_Point)
		{
			Point A(1000000, -2000000, 2);

			Assert::IsTrue(A * 0 == Point(0, 0, 0));
		}

		TEST_METHOD(multiplication_doubleZero_Point)
		{
			Point A(1000.04400, -2000.0300, 2.1);

			Assert::IsTrue(A * 0 == Point(0, 0, 0));
		}

		TEST_METHOD(multiplication_integerLimits_Zero_Point)
		{
			Point A(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::max(), std::numeric_limits<int>::min());

			Assert::IsTrue(A * 0 == Point(0, 0, 0));
		}

		TEST_METHOD(multiplication_doubleLimits_Zero_Point)
		{
			Point A(LOWEST, MAX, MIN);

			Assert::IsTrue(A * 0 == Point(0, 0, 0));
		}

		TEST_METHOD(multiplication_doublelimit_One_Point)
		{
			Point A(LOWEST, MAX, MIN);

			Assert::IsTrue(A * 1 ==
				Point(LOWEST,
					MAX,
					MIN
					)
				);
		}

		TEST_METHOD(multiplication_by2_Point)
		{
			Point A(0.5, 0.555, 555555.55555);

			Assert::IsTrue(A * 2 == Point(1, 1.11, 1111111.1111));
		}

		TEST_METHOD(divide_doubleatlimit_byOne_Point)
		{
			Point A(LOWEST, MAX, MIN);

			Assert::IsTrue(A / 1 ==
				Point(LOWEST,
					MAX,
					MIN
					)
				);
		}

		TEST_METHOD(divide_doubleatlimit_by0_Point) //Checks how division by zero is handled
		{
			auto func = []()
			{
				Point A(LOWEST, MAX, MIN);
				A / 0;
			};

			Assert::ExpectException<const char[13]>(func);
		}
	};

	//============================================================================================
	TEST_CLASS(VectTests)
	{
	public:

		TEST_METHOD(ParameterlessVect)
		{
			Vect C;
			Assert::IsTrue(C == Vect(0, 0, 0));
		}

		TEST_METHOD(VectCopyConstructor)
		{
			CartesianElement C(1234142.124214, 2411.24, 45.4500000000787);
			Vect Copied(C);

			Assert::IsTrue(Vect(1234142.124214, 2411.24, 45.4500000000787) == Copied);
		}

		TEST_METHOD(VectFromPoints)
		{
			Point C(1234142.124214, 2411.24, 45.4500000000787);
			Point D(.34234, 23423, 45634563.346);

			Assert::IsTrue(Vect(C, D) == Vect(.34234 - 1234142.124214, 23423 - 2411.24, 45634563.346 - 45.4500000000787));
		}

		//==============================FROM BASE CLASS=================================================
		//Operators tests--------------------------------------------------
		TEST_METHOD(AdditionTest_integers_Vect)
		{
			Vect A(1000000, -2000000, 0);
			Vect B(1, 1, 1);

			Assert::IsTrue(A + B == Vect(1000001, -1999999, 1));
		}

		TEST_METHOD(AdditionTest_Doublelimits_suitableInterger)
		{
			Vect A(1000000, -2000000, 0);
			Vect B(LOWEST, MAX, MIN);

			Assert::IsTrue(A + B ==
				Vect(LOWEST + 1000000.0,
					MAX - 2000000.0,
					MIN
					)
				);
		}

		TEST_METHOD(AdditionTest_integerfraction_Vect)
		{
			Vect A(1000000 / 2, -2000001 / 2, 3);
			Vect B(1000000 / 2, -2000001 / 2, 0);

			Assert::IsTrue(A + B == Vect(1000000, -2000000, 3));
		}

		TEST_METHOD(divide_doubleatlimit_byOne_Vect)
		{
			Vect A(LOWEST, MAX, MIN);


			Assert::IsTrue(A / 1 ==
				Vect(LOWEST,
					MAX,
					MIN
					)
				);
		}

		TEST_METHOD(divideBy0_doubleatlimit_Vect)
		{
			auto func = []()
			{
				Vect A(LOWEST, MAX, MIN);
				A / 0;
			};

			Assert::ExpectException<const char[13]>(func);
		}


		//========================VECT CLASS SPECIFIC============================================================
		TEST_METHOD(VectEquality)
		{
			Vect A(LOWEST, MAX, MIN);
			Vect B(LOWEST, MAX, MIN);

			Assert::IsTrue(A == B);
		}

		TEST_METHOD(VectInequality)  //FAIL -- Precision lost for big numbers -- 
		{
			Vect A(-rangeOfInterest, rangeOfInterest, accuracy);
			Vect B(1 - rangeOfInterest, rangeOfInterest, accuracy);

			Assert::IsFalse(A == B);
		}

		TEST_METHOD(CanonicVectorialProducts)
		{
			Vect x(1, 0, 0), y(0, 1, 0), z(0, 0, 1);

			Assert::IsTrue((x^y) == z);
			Assert::IsTrue((y^z) == x);
			Assert::IsTrue((z^x) == y);

			Assert::IsTrue((y^x) == -z);
			Assert::IsTrue((z^y) == -x);
			Assert::IsTrue((x^z) == -y);
		}

		TEST_METHOD(LimitsVectorialProducts)
		{
			Vect v(LOWEST, MIN, MAX), u(1, 1, 1);
			Assert::IsTrue((v^u) == Vect(MIN - MAX, MAX - LOWEST, LOWEST - MIN));
		}

		TEST_METHOD(ScalarProductLimits)
		{
			Vect a(MIN, MAX, 1), b(LOWEST, LOWEST, 1);
			Assert::IsTrue(a*b == MIN*LOWEST + MAX*LOWEST + 1);
		}

		TEST_METHOD(CanonicScalarlProducts)
		{
			Vect x(1, 0, 0), y(0, 1, 0), z(0, 0, 1);

			Assert::IsTrue((x*y) == 0);
			Assert::IsTrue((y*z) == 0);
			Assert::IsTrue((z*x) == 0);
		}

		TEST_METHOD(NormalityTest)
		{
			Vect l(234, 0, 0);
			Vect mn(0, 453415.451454, 0);
			Vect mx(0, 0, .001000262434);

			Assert::IsTrue(l.norm() == 234);
			Assert::IsTrue(mn.norm() == 453415.451454);
			Assert::IsTrue(mx.norm() == .001000262434);
		}

		TEST_METHOD(limitNormalityTest)
		{
			Vect l(-rangeOfInterest, 0, 0);
			Vect mn(0, accuracy, 0);
			Vect mx(0, 0, rangeOfInterest);

			Assert::IsTrue(l.norm() == rangeOfInterest);
			Assert::IsTrue(mn.norm() == accuracy);
			Assert::IsTrue(mx.norm() == rangeOfInterest);
		}

		TEST_METHOD(limitNormOfVectorialProduct)
		{
			Vect l(-rangeOfInterest, 0, 0);
			Vect mn(0, accuracy, 0);
			Vect mx(0, rangeOfInterest, 0);

			Assert::IsTrue(((l^mn) ^ mx).norm() == rangeOfInterest*rangeOfInterest*accuracy);
		}

		TEST_METHOD(NormOfVectorialProduct)
		{
			Vect l(234, 0, 0);
			Vect mn(0, 453415.451454, 0);
			Vect mx(0, .001000262434, 0);

			Assert::IsTrue(((l^mn) ^ mx).norm() == 234 * 453415.451454*.001000262434);
		}

		TEST_METHOD(UnityVectNormAndDirection)
		{
			Vect l(2, 978.98, 78989);

			Assert::IsTrue(l.unitVector().norm() == 1);
			Assert::IsTrue(l.unitVector() * l == l.norm());
		}

		TEST_METHOD(UnityVectorialLow)
		{
			Vect l(2, 9, 9);

			Assert::IsTrue((l.unitVector() ^ l) == Vect(0, 0, 0));
		}

		TEST_METHOD(UnityVectorialHigh)
		{
			Vect l(2, 978.98, 78989);

			Assert::IsTrue((l.unitVector() ^ l) < Vect(accuracy, accuracy, accuracy));
		}

		TEST_METHOD(LimitsUnitNorm)
		{
			Vect l(-rangeOfInterest, accuracy, rangeOfInterest);
			Assert::IsTrue(l.unitVector().norm() == 1);
		}

		TEST_METHOD(LimitsUnitScalar) //rounding error in e-6
		{
			Vect l(-rangeOfInterest, accuracy, rangeOfInterest);
			Assert::IsTrue(abs(l.unitVector() * l - l.norm()) < accuracy);
		}


	};

}