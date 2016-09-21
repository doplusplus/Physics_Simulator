#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SimModule\Observer.h"
#include <functional>
#include <stdexcept>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	const double accuracy = 1E-10; //approximately the diameter of an hydrogen atom in meter
	const double rangeOfInterest = 12742000; //earth diameter

	const double maxMassRange = 5.9722E24; //kg EarthMass
	const double maxMassAccuracy = 1E-9; //kg -  microgram 
	const double maxChargeAccuracy = 1E-15; //C - femtoCoulomb : order of a dust particle's charge 
	const double maxChargeRange = 59E7; //BehemotBatteryCharge C

/*	TEST_CLASS(GeneralObserverTest)
	{
		
	};*/

	TEST_CLASS(MaterialPointObserverTest)
	{
	public:

		TEST_METHOD(PointObserverCreation)
		{
			MaterialPoint M(0.0, 0.0);
			MaterialPoint N(0.0, 0.0);
			MaterialPoint P(0.0, 10.0);

			MaterialPointObserver obs(M, Calculator(), Point(0, 0, 0), Vect(0, 0, 0));
			MaterialPointObserver obs2(N, Calculator(), Point(0, 0, 0), Vect(0, 0, 0));
			MaterialPointObserver obs3(P, Calculator(), Point(0, 0, 0), Vect(0, 0, 0));
			Assert::IsTrue(obs == obs2);
			Assert::IsFalse(obs == obs3);
		}

		TEST_METHOD(CoordinateStreaming)
		{
			MaterialPoint P(maxMassAccuracy, maxChargeAccuracy);
			MaterialPointObserver obs(P, Calculator(), Point(accuracy, -rangeOfInterest, rangeOfInterest), Vect(0, 0, 0));
			std::vector<double> v = { accuracy, -rangeOfInterest, rangeOfInterest };
			Assert::IsTrue(obs.streamCoord() == v);
		}

		TEST_METHOD(blankIncrementTest)
		{
			MaterialPoint P(maxMassAccuracy, maxChargeAccuracy);
			MaterialPointObserver obs(P, Calculator(), Point(accuracy, -rangeOfInterest, rangeOfInterest), Vect(0, 0, 0));
			double time = 10;
			double precision = time / 20;
			obs.increment(0,time, precision);
			Assert::IsTrue(obs.position(0) == Point(accuracy, -rangeOfInterest, rangeOfInterest));
		}

		TEST_METHOD(Position_at_10kg_10sec_underGravity)
		{
			double expectedZ = 490.5;
			double mass = 10;
			double duration = 10; //s

			Vect F(0, 0, 98.1);
			MaterialPoint M(mass, 0, { std::shared_ptr<ActionOnPoint>(new ActionOnPoint(F)) });
			MaterialPointObserver Obs(M, Calculator(), Point(0, 0, 0), Vect(0, 0, 0));

			Obs.increment(0,duration, accuracy);
			double e = abs(Obs.position(0).coordStream()[2] - expectedZ);
			Assert::IsTrue(e <= accuracy);
		}

		TEST_METHOD(ResultantTest)
		{
			Vect F(0, 0, 10);
			Vect G(0, 10, 0);
			Vect H(10, 0, 0);
			auto VF = std::shared_ptr<ActionOnPoint>(new ActionOnPoint(F, Vect(1,0,0), Vect(1,0, 0), Vect(0, 1, 0),
				Vect(0, 0, 1), Vect::linear, Vect::Vlinear, Vect::Vlinear, Vect::Vlinear));
			auto VG = std::shared_ptr<ActionOnPoint>(new ActionOnPoint(G, Vect(0, 0, 0), Vect(1, 1, 1), Vect(0, 1, 0), 
				Vect(0, 0, 0), Vect::Quadratic, Vect::Vlinear, Vect::VQuadratic, Vect::Vlinear));
			auto VH = std::shared_ptr<ActionOnPoint>(new ActionOnPoint(H, Vect(0.9, 9.98, .20), Vect(0, 0, 0), Vect(0, 0, 0),
				Vect(0, 0, 1.1), Vect::constant, Vect::Vlinear, Vect::Vlinear, Vect::Vlinear));

			MaterialPoint M(9, 0, {VF,VG,VH });
			MaterialPointObserver Obs(M, Calculator(), Point(2, 3, 4), Vect(0, 0, 0));
			
			auto ten=Obs.resultant(10);
			auto now = Obs.resultant();

			Assert::IsTrue(now == Vect(21, 22, 18.4) && ten == Vect(31, 22, 18.4));
		}

		TEST_METHOD(ResultantArrayCoherence)
		{
			Vect F(1,2,3);
			auto VF = std::shared_ptr<ActionOnPoint>(new ActionOnPoint(F, Vect(1, 1, 1), Vect(1, 0, 0), Vect(0, 1, 0),
				Vect(0, 0, 1), Vect::linear, Vect::Vlinear, Vect::Vlinear, Vect::Vlinear));
			
			MaterialPoint M(10, 0, { VF});
			MaterialPointObserver Obs(M, Calculator(), Point(10,10,10), Vect(0, 0, 0));

			Vect Res = Obs.resultant(10);
			auto ResArray=Obs.resultants(0,10/30.0, 30);
			double error = static_cast<Vect>(Res - ResArray.back()).norm();
			Assert::IsTrue(error < accuracy);
		}

		TEST_METHOD(ActionAdd)
		{
			Vect F(0, 0, 10);
			Vect G(0, 10, 0);
			Vect H(10, 0, 0);
			auto VF = std::shared_ptr<ActionOnPoint>(new ActionOnPoint(F, Vect(1, 0, 0), Vect(1, 0, 0), Vect(0, 1, 0),
				Vect(0, 0, 1), Vect::linear, Vect::Vlinear, Vect::Vlinear, Vect::Vlinear));
			auto VG = std::shared_ptr<ActionOnPoint>(new ActionOnPoint(G, Vect(0, 0, 0), Vect(1, 1, 1), Vect(0, 1, 0),
				Vect(0, 0, 0), Vect::Quadratic, Vect::Vlinear, Vect::VQuadratic, Vect::Vlinear));
			auto VH = std::shared_ptr<ActionOnPoint>(new ActionOnPoint(H, Vect(0.9, 9.98, .20), Vect(0, 0, 0), Vect(0, 0, 0),
				Vect(0, 0, 1.1), Vect::constant, Vect::Vlinear, Vect::Vlinear, Vect::Vlinear));
			MaterialPoint M(10, 0, { VF,VG,VH });
			MaterialPoint P(10, 0, {});
			MaterialPointObserver Obs(M, Calculator(), Point(10, 10, 10), Vect(0, 0, 0));
			MaterialPointObserver Obs2(P, Calculator(), Point(10, 10, 10), Vect(0, 0, 0));

			Obs2.addAction(VH);
			Obs2.addAction(VF);
			Obs2.addAction(VG);

			Assert::IsTrue(Obs==Obs2);
		}

	};
}