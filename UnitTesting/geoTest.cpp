#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SimModule\Geo.h"
#include <limits>
#include <iostream> ///to remove in a bit

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GeoTest
{		
	TEST_CLASS(PointTests)
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

		TEST_METHOD(AdditionTest_integerfraction)  //assumes compiler performs integer division
		{
			Point A(1000000/2, -2000001/2, 3);
			Point B(1000000/2, -2000001/2, 0);

			A = A + B;
			Assert::IsTrue(A.getX() == 1000000);
			Assert::IsTrue(A.getY() == -2000000);
			Assert::IsTrue(A.getZ() == 3);
		}

		TEST_METHOD(multiplication_integersZero)
		{
			Point A(1000000, -2000000, 2);

			Assert::IsTrue((A * 0).getX() == 0);
			Assert::IsTrue((A * 0).getY() == 0);
			Assert::IsTrue((A * 0).getZ() == 0);
		}

		TEST_METHOD(multiplication_doubleZero)
		{
			Point A(1000.04400, -2000.0300, 2.1);

			Assert::IsTrue((A * 0).getX() == 0);
			Assert::IsTrue((A * 0).getY() == 0);
			Assert::IsTrue((A * 0).getZ() == 0);
		}

		TEST_METHOD(multiplication_doublelimit_Zero)
		{
			Point A(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			Assert::IsTrue((A * 0).getX() == 0);
			Assert::IsTrue((A * 0).getY() == 0);
			Assert::IsTrue((A * 0).getZ() == 0);
		}

		TEST_METHOD(multiplication_doublelimit_One)
		{
			Point A(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			Assert::IsTrue((A * 1).getX() == std::numeric_limits<double>::lowest());
			Assert::IsTrue((A * 1).getY() == std::numeric_limits<double>::max());
			Assert::IsTrue((A * 1).getZ() == std::numeric_limits<double>::min());
		}

		TEST_METHOD(multiplication_5Point5_bye2)
		{
			Point A(0.5, 0.555, 555555.55555);

			Assert::IsTrue((A * 2).getX() == 1);
			Assert::IsTrue((A * 2).getY() == 1.11);
			Assert::IsTrue((A * 2).getZ() == 1111111.1111);
		}

		TEST_METHOD(divide_doubleatlimit_byOne)
		{
			Point A(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			Assert::IsTrue((A / 1).getX() == std::numeric_limits<double>::lowest());
			Assert::IsTrue((A / 1).getY() == std::numeric_limits<double>::max());
			Assert::IsTrue((A / 1).getZ() == std::numeric_limits<double>::min());
		}

		TEST_METHOD(divide_doubleatlimit_by0) //Checks how division by zero is handled
		{
			Point A(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());
			
			try
			{
				A = A / 0;
			}
			catch(char *S)
			{
				std::cerr << S << '\n';
				A.nullify();
			}

			Assert::IsTrue( A.getX() == 0);
			Assert::IsTrue( A.getY() == 0);
			Assert::IsTrue( A.getZ() == 0);

		}
		

		TEST_METHOD(divide_doubleat0_byLimits)
		{
			Point A(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());
			A.nullify();

			Assert::IsTrue((A / std::numeric_limits<double>::lowest()).getX() == 0);
			Assert::IsTrue((A / std::numeric_limits<double>::max()).getY() == 0);
			Assert::IsTrue((A / std::numeric_limits<double>::min()).getZ() == 0);
		}

		 
	



	};

	TEST_CLASS(VectTests)
	{
	public:

		TEST_METHOD(VectNullity)
		{
			Vect P;

			P.nullify();

			Assert::IsTrue(P.getX() == 0);
			Assert::IsTrue(P.getY() == 0);
			Assert::IsTrue(P.getZ() == 0);
		}

		TEST_METHOD(CreateVect_min200000_0_200000)
		{
			Vect P(-200000, 0, 200000);

			Assert::IsTrue(P.getX() == -200000);
			Assert::IsTrue(P.getY() == 0);
			Assert::IsTrue(P.getZ() == 200000);
		}

		TEST_METHOD(CreateVect_origin)
		{
			Vect P(-200000, 0, 200000);

			Assert::IsTrue(P.getX() == -200000);
			Assert::IsTrue(P.getY() == 0);
			Assert::IsTrue(P.getZ() == 200000);
		}

		TEST_METHOD(CreateVect_infRange_supRange_limitPrecision)
		{
			Vect P(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			Assert::IsTrue(P.getX() == std::numeric_limits<double>::lowest());
			Assert::IsTrue(P.getY() == std::numeric_limits<double>::max());
			Assert::IsTrue(P.getZ() == std::numeric_limits<double>::min());
		}

		TEST_METHOD(setVectTest_infRange_supRange_limitPrecision)
		{
			Vect P;

			P.setVect(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			Assert::IsTrue(P.getX() == std::numeric_limits<double>::lowest());
			Assert::IsTrue(P.getY() == std::numeric_limits<double>::max());
			Assert::IsTrue(P.getZ() == std::numeric_limits<double>::min());
		}

		TEST_METHOD(VectAdditionTest_integers)
		{
			Vect A(1000000, -2000000, 0);
			Vect B(1, 1, 1);

			A = A + B;

			Assert::IsTrue(A.getX() == 1000001);
			Assert::IsTrue(A.getY() == -1999999);
			Assert::IsTrue(A.getZ() == 1);
		}

		TEST_METHOD(VectAdditionTest_Doublelimits_suitableInterger)
		{
			Vect A(1000000, -2000000, 0);
			Vect B(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			A = A + B;

			Assert::IsTrue(A.getX() == std::numeric_limits<double>::lowest() + 1000000.0);
			Assert::IsTrue(A.getY() == std::numeric_limits<double>::max() - 2000000.0);
			Assert::IsTrue(A.getZ() == std::numeric_limits<double>::min());
		}

		TEST_METHOD(VectAdditionTest_integerfraction)  //assumes compiler performs integer division
		{
			Vect A(1000000 / 2, -2000001 / 2, 3);
			Vect B(1000000 / 2, -2000001 / 2, 0);

			A = A + B;
			Assert::IsTrue(A.getX() == 1000000);
			Assert::IsTrue(A.getY() == -2000000);
			Assert::IsTrue(A.getZ() == 3);
		}

		TEST_METHOD(Vectmultiplication_integersZero)
		{
			Vect A(1000000, -2000000, 2);

			Assert::IsTrue((A * 0).getX() == 0);
			Assert::IsTrue((A * 0).getY() == 0);
			Assert::IsTrue((A * 0).getZ() == 0);
		}

		TEST_METHOD(Vectmultiplication_doubleZero)
		{
			Vect A(1000.04400, -2000.0300, 2.1);

			Assert::IsTrue((A * 0).getX() == 0);
			Assert::IsTrue((A * 0).getY() == 0);
			Assert::IsTrue((A * 0).getZ() == 0);
		}

		TEST_METHOD(Vectmultiplication_doublelimit_Zero)
		{
			Vect A(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			Assert::IsTrue((A * 0).getX() == 0);
			Assert::IsTrue((A * 0).getY() == 0);
			Assert::IsTrue((A * 0).getZ() == 0);
		}

		TEST_METHOD(Vectmultiplication_doublelimit_One)
		{
			Vect A(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			Assert::IsTrue((A * 1).getX() == std::numeric_limits<double>::lowest());
			Assert::IsTrue((A * 1).getY() == std::numeric_limits<double>::max());
			Assert::IsTrue((A * 1).getZ() == std::numeric_limits<double>::min());
		}

		TEST_METHOD(Vectmultiplication_5point5_bye2)
		{
			Vect A(0.5, 0.555, 555555.55555);

			Assert::IsTrue((A * 2).getX() == 1);
			Assert::IsTrue((A * 2).getY() == 1.11);
			Assert::IsTrue((A * 2).getZ() == 1111111.1111);
		}

		TEST_METHOD(Vectdivide_doubleatlimit_byOne)
		{
			Vect A(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());

			Assert::IsTrue((A / 1).getX() == std::numeric_limits<double>::lowest());
			Assert::IsTrue((A / 1).getY() == std::numeric_limits<double>::max());
			Assert::IsTrue((A / 1).getZ() == std::numeric_limits<double>::min());
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

			Assert::IsTrue(A.getX() == 0);
			Assert::IsTrue(A.getY() == 0);
			Assert::IsTrue(A.getZ() == 0);

		}


		TEST_METHOD(Vectdivide_doubleat0_byLimits)
		{
			Vect A(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::min());
			A.nullify();

			Assert::IsTrue((A / std::numeric_limits<double>::lowest()).getX() == 0);
			Assert::IsTrue((A / std::numeric_limits<double>::max()).getY() == 0);
			Assert::IsTrue((A / std::numeric_limits<double>::min()).getZ() == 0);
		}


	};


}
