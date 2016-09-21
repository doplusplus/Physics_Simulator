#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SimModule\MaterialElement.h"
#include "..\SimModule\MechanicalAction.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(MaterialPointTest)
	{
	public:

		TEST_METHOD(blankMatPointConstruction)
		{
			MaterialPoint A;
			MaterialPoint B(0.0, 0.0);
			MaterialPoint C(0.0, 0.0, {});

			Assert::IsTrue(A == B&&B == C);
		}

		TEST_METHOD(MatPointConstruction_WithSwapedActions)
		{
			auto a2 = std::make_shared<ActionOnPoint>
				(ActionOnPoint(Vect(0, 0, 0), Vect(0, 0, 0), Vect(0, 0, 0), Vect::linear, Vect::Vconstant));
			auto a3 = std::make_shared<ActionOnPoint>
				(ActionOnPoint(Vect(0, 0, 0), Vect(0, 0, 0), Vect(0, 0, 0), Vect::constant, Vect::Vlinear));

			MaterialPoint A(0.0, 0.0, { a2,a3 });
			MaterialPoint B(0.0, 0.0, { a3,a2 });

			Assert::IsTrue(A == B);
		}

		TEST_METHOD(MatPointConstruction_unequal)
		{
			auto a2 = std::make_shared<ActionOnPoint>
				(ActionOnPoint(Vect(0, 0, 0), Vect(0, 0, 0), Vect(0, 0, 0), Vect::linear, Vect::Vlinear));
			auto a3 = std::make_shared<ActionOnPoint>
				(ActionOnPoint(Vect(0, 0, 0), Vect(0, 0, 0), Vect(0, 0, 0), Vect::Quadratic, Vect::Vlinear));

			MaterialPoint A(0.0, 0.0, { a2 });
			MaterialPoint B(0.0, 0.0, { a3 });

			Assert::IsFalse(A == B);
		}


	};

}