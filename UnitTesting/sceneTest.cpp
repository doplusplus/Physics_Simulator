#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SimModule\Scene.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SceneTest
{
	TEST_CLASS(TestOfScene)
	{
	public:

		TEST_METHOD(SceneCreationInit)
		{
			Scene Sc;
		//	Sc.addMatPoint();
		//	Assert::IsTrue(*(Sc.getElement(0)->pointerToPosition()) == Point(0, 0, 0));
		}

		TEST_METHOD(SceneCreationEmpty)
		{
			Scene Sc;
			Assert::IsNull(Sc.getElement(0));
		}

		TEST_METHOD(FreeFallEarth)
		{
			Scene Sc;
			double FallTime = 10;	//seconds
			double mass = 1;		//kg	
			const double earthGravity = 9.81;

			Vect G(0, 0, mass*earthGravity);
//			Sc.addMatPoint(Point(0, 0, 0), Vect(0, 0, 0), mass);
//			Sc.getElement(0)->addExternalAction(G);
//			Sc.forward(FallTime);

//			Assert::IsTrue(Point(0, 0, 0.5*9.81*FallTime*FallTime) == *(Sc.getElement(0)->pointerToPosition()));
		}
	};
}