#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SimModule\Geo.h"
#include <limits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GeoTest
{		
	TEST_CLASS(geoTest1)
	{
	public:
		
		TEST_METHOD(Nullity)
		{
			Point P;
			
			P.nullify();
			
			Assert::IsTrue(P.getX()==0);
			Assert::IsTrue(P.getY() == 0);
			Assert::IsTrue(P.getZ() == 0);
		}

		TEST_METHOD(CreatePoint_min200000_0_200000)
		{
			Point P(-200000,0,200000);
			
			Assert::IsTrue(P.getX() == -200000);
			Assert::IsTrue(P.getY() == 0);
			Assert::IsTrue(P.getZ() == 200000);
		}

		TEST_METHOD(CreatePoint_origin)
		{
			Point P(-200000, 0, 200000);
			
			Assert::IsTrue(P.getX() == -200000);
			Assert::IsTrue(P.getY() == 0);
			Assert::IsTrue(P.getZ() == 200000);
		}

		TEST_METHOD(CreatePoint_infRange_supRange_limitPrecision)
		{
			Point P(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());
			
			Assert::IsTrue(P.getX() == std::numeric_limits<double>::lowest());
			Assert::IsTrue(P.getY() == std::numeric_limits<double>::max());
			Assert::IsTrue(P.getZ() == std::numeric_limits<double>::min());
		}

		TEST_METHOD(PlaceTest_infRange_supRange_limitPrecision)
		{
			Point P;
			
			P.place(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());
			
			Assert::IsTrue(P.getX() == std::numeric_limits<double>::lowest());
			Assert::IsTrue(P.getY() == std::numeric_limits<double>::max());
			Assert::IsTrue(P.getZ() == std::numeric_limits<double>::min());
		}

		TEST_METHOD(AdditionTest_integers)
		{
			Point A(1000000,-2000000,0);
			Point B(1,1,1);

			A = A + B;

			Assert::IsTrue(A.getX() == 1000001);
			Assert::IsTrue(A.getY() == -1999999);
			Assert::IsTrue(A.getZ() == 1);
		}

		TEST_METHOD(AdditionTest_Doublelimits_suitableInterger)
		{
			Point A(1000000, -2000000, 0);
			Point B(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			A = A + B;

			Assert::IsTrue(A.getX() == std::numeric_limits<double>::lowest() + 1000000.0);
			Assert::IsTrue(A.getY() == std::numeric_limits<double>::max() - 2000000.0);
			Assert::IsTrue(A.getZ() == std::numeric_limits<double>::min());
		}

		TEST_METHOD(AdditionTest_Doublelimits_integerfraction)
		{
			Point A(1000000/2, -2000001/2, 3);
			Point B(1000000/2, -2000001/2, 0);

			A = A + B;

			Assert::IsTrue(A.getX() == 1000000);
			Assert::IsTrue(A.getY() == -2000001);
			Assert::IsTrue(A.getZ() == 3);
		}


	};
}
