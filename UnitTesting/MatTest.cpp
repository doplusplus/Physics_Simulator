#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SimModule\MaterialElement.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MatElementTest
{
	TEST_CLASS(MatPointTest)
	{
	public:

		TEST_METHOD(ParameterlessMatPoint)
		{
			MaterialPoint M;
			Point P(0, 0, 0);
			MaterialPoint N(P);
			Assert::IsTrue(M == N);
		}


		TEST_METHOD(equality)
		{
			Point P(13223.3232, 3223.23233232, 23222323232.276473);
			Vect V(2, 3.123, 4342.4352314);
			double mass = 44555456.545545543;
			double charge = 27357357654567475666.3423;

			MaterialPoint M(P, V, mass, charge);

			Assert::IsTrue(M == M);
		}
	




	};


}