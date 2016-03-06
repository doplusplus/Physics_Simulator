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
			ActionOnPoint A(0,0,0);
			ActionOnPoint B;
			Assert::IsTrue(A == B);
		}

		TEST_METHOD(ForceGetter)
		{
			ActionOnPoint A(1, 3, 5);
			Assert::IsTrue(A.force() == Vect(1, 3, 5));
		}






	};
}