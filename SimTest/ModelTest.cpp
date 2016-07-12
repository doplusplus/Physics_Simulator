#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SimModule\Model.h"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	const double accuracy = double(1e-10); //approximately the diameter of an hydrogen atom in meter
	const double rangeOfInterest = 384467000; //approximately the earth to moon distance


	TEST_CLASS(ModelTest)
	{
	public:

		double compareCoords(std::vector<double> res, std::vector<double> coord)
		{
			double error = 0;
			for (int i = 0; i < res.size(); i++)
			{
				error += (res[i] - coord[i])*(res[i] - coord[i]);
			}
			error = std::sqrt(error);
			return error;
		}

		TEST_METHOD(AddingMatPoints)
		{
			Model M;
			M.addMatPoint(Point(-23, 34.43, 55));
			M.addMatPoint(Point(1, 2, 3));
			M.addMatPoint(Point());

			std::vector<double > V = { 0,0,0,1,2,3,-23,34.43,55 };

			Assert::IsTrue(M.getCoordinate() == V);
		}


		TEST_METHOD(negativeTimeIncrement)
		{
			std::function<void(void)> f1 = []
			{
				Model M;
				M.addMatPoint(Point(0, 0, 0));
				M.addActionOnPoint(0, Vect(1, 2, 4));
				M.increment(-3, 0.1);
			};


			Assert::ExpectException<std::invalid_argument>(f1);
		}

		TEST_METHOD(FreeFallOnEarth_at_1kg)
		{
			Model M;
			double FallTime = 10;	//seconds
			double mass = 1;		//kg
			const double earthGravity = 9.81;
			Vect G(0, 0, mass*earthGravity);

			M.addMatPoint(Point(0, 0, 0), Vect(0, 0, 0), mass);
			M.addActionOnPoint(0, G);
			M.increment(FallTime, accuracy);

			auto coord = M.getCoordinate();
			std::vector<double> res = { 0, 0, 0.5*earthGravity*FallTime*FallTime };

			double error = 0; bool b = false;
			if (coord.size() == res.size())
			{
				b = compareCoords(coord, res) < accuracy ? true : false;
			}
			Assert::IsTrue(b);
		}

		TEST_METHOD(simToFile)
		{
			Model M;
			std::string target="C:\\Users\\Doz\\Source\\Repos\\Physics_Simulator\\ConsoleEntryPoint\\IOTestFile.txt";
			M.addMatPoint(Point(0, 0, 0));
			M.simulate(10, 0.1, target,accuracy);
			std::string s;
			std::fstream reader(target);
			
			std::getline(reader, s); //skip first line
			std::getline(reader, s);

			Assert::IsTrue(s == "0 0 0 0 0 0 0 0 1 1");//t elem X Y Z Vx Vy Vz m C

		}



	};
}