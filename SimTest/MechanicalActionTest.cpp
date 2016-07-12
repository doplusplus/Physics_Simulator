#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SimModule\MechanicalAction.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(ActionOnPointTest)
	{
	public:

		TEST_METHOD(Construction)
		{
			ActionOnPoint A;
			ActionOnPoint B(Vect(0, 0, 0), Vect(0, 0, 0), Vect(0, 0, 0), Vect::constant, Vect::Vconstant);
			Assert::IsTrue(A == B);
		}

		TEST_METHOD(Copy)
		{
			ActionOnPoint A(Vect(1.1, 1.1, 1.1), Vect(2.2, 2.2, 2.2), Vect(3.3, 3.3, 3.3), Vect::constant, Vect::Vconstant);
			ActionOnPoint B(A);
			ActionOnPoint C=A;
			Assert::IsTrue(A == B && C==A);
		}
		
		TEST_METHOD(Assign)
		{
			ActionOnPoint A(Vect(1.1, 1.1, 1.1), Vect(2.2, 2.2, 2.2), Vect(3.3, 3.3, 3.3), Vect::constant, Vect::Vconstant);
			ActionOnPoint B(Vect(0, 0, 0), Vect(0, 0, 0), Vect(0, 0, 0), Vect::constant, Vect::Vconstant);
			B = A;
			Assert::IsTrue(A == B);
		}
		
		TEST_METHOD(makePointActiontNull)
		{
			ActionOnPoint A(Vect(1.1, 1.1, 1.1), Vect(2.2, 2.2, 2.2), Vect(3.3, 3.3, 3.3), Vect::linear, Vect::VQuadratic);
			ActionOnPoint B(Vect(0, 0, 0), Vect(0, 0, 0), Vect(0, 0, 0), Vect::constant, Vect::Vconstant);
			A.null();
			Assert::IsTrue(A.base() == B.base());
		}

		TEST_METHOD(linearVariationInTime)
		{
			ActionOnPoint A(Vect(1, 2, 5), Vect(-2, 7, -17), Vect(0, 0, 0), Vect::linear, Vect::Vconstant);
			Assert::IsTrue(A.force(Vect(0,0,0),10)==Vect(-19,72,-165));
		}

		TEST_METHOD(linearVariationInSpace)
		{
			ActionOnPoint A(Vect(1, 2, 5), Vect(0, 0, 0), Vect(-2, 7, -17), Vect::constant, Vect::Vlinear);
			Assert::IsTrue(A.force(Vect(10, -10, 1), 0) == Vect(-106,-105,-102));
		}

		TEST_METHOD(quadraticVariationInTime)
		{
			ActionOnPoint A(Vect(1, 2, 5), Vect(-2, 7, -17), Vect(0, 0, 0), Vect::Quadratic, Vect::Vconstant);
			Assert::IsTrue(A.force(Vect(0, 0, 0), 10) == Vect(-199, 702, -1695));
		}

		TEST_METHOD(quadraticVariationInSpace)
		{
			ActionOnPoint A(Vect(1, 2, 5), Vect(0, 0, 0), Vect(-2, 7, -17), Vect::constant, Vect::VQuadratic);
			Assert::IsTrue(A.force(Vect(10, -10, 1), 0) == Vect(-916, -915, -912));
		}

/*		TEST_METHOD(Addition_Null)
		{
			ActionOnPoint A(Vect(0, 0, 0), Vect(0, 0, 0), Vect(0, 0, 0), Vect::constant, Vect::Vconstant);
			ActionOnPoint B(Vect(0, 0, 0), Vect(0, 0, 0), Vect(0, 0, 0), Vect::linear, Vect::VQuadratic);			
			Assert::IsTrue((A+B).force(Point(0,0,0),2)==Vect());
		}

		TEST_METHOD(Addition_NoVariationInTime)
		{
			ActionOnPoint A(Vect(1, 2, 5), Vect(0, 0, 0), Vect(0, 0, 0), Vect::constant, Vect::Vconstant);
			ActionOnPoint B(Vect(1, -2, -1), Vect(0, 0, 0), Vect(0, 0, 0), Vect::linear, Vect::VQuadratic);
			Assert::IsTrue((A + B).force(Point(0, 0, 0),10) == Vect(2,0,4));
		}

		TEST_METHOD(Addition_NoVariationInSpace)
		{
			ActionOnPoint A(Vect(1, 2, 5), Vect(0, 0, 0), Vect(0, 0, 0), Vect::constant, Vect::Vconstant);
			ActionOnPoint B(Vect(1, -2, -1), Vect(0, 0, 0), Vect(0, 0, 0), Vect::linear, Vect::VQuadratic);
			Assert::IsTrue((A + B).force(Point(3, -10, 90), 0) == Vect(2, 0, 4));
		}

		TEST_METHOD(Addition_VariationInTime)
		{
			ActionOnPoint A(Vect(1, 2, 5), Vect(1, 2, 3), Vect(0, 0, 0), Vect::Quadratic , Vect::Vconstant);
			ActionOnPoint B(Vect(1, -2, -1), Vect(1, 2, 3), Vect(0, 0, 0), Vect::linear, Vect::VQuadratic);
			Assert::IsTrue((A + B).force(Point(1, 2, 3), 10) == Vect(112,220,334));
		}

		TEST_METHOD(Addition_VariationInSpace)
		{
			ActionOnPoint A(Vect(1, 2, 5), Vect(0, 0, 0), Vect(1, 2, 3), Vect::constant, Vect::Vlinear);
			ActionOnPoint B(Vect(1, -2, -1), Vect(0, 0, 0), Vect(1, 2, 3), Vect::linear, Vect::VQuadratic);
			Assert::IsTrue((A + B).force(Point(3, -10, 100), 0) == Vect(10888, 10886, 10890));
		}

		//Not to implementable
*/
	};
}