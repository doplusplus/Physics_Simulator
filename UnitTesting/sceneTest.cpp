#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Scene.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SceneTest
{
	TEST_CLASS(TestOfScene)
	{
	public:

		TEST_METHOD(SceneCreationInit)
		{
			Scene Sc;
			Sc.addMatPoint();

			double x = Sc.getElement(0)->pointerToPosition()->xComponent();
			double y = Sc.getElement(0)->pointerToPosition()->yComponent();
			double z = Sc.getElement(0)->pointerToPosition()->zComponent();

			Assert::AreEqual(0.0, x);
			Assert::AreEqual(0.0, y);
			Assert::AreEqual(0.0, z);
		}

		TEST_METHOD(SceneCreationEmpty)
		{
			Scene Sc;
			Assert::IsNull(Sc.getElement(0));
		}

		TEST_METHOD(FreeFallEarth)
		{
			Scene Sc;
			Sc.addMatPoint();

			double FallTime = 10;	//seconds
			double mass = 1;		//kg	
			const double earthGravity = 9.81;

			Vect G(0, 0, mass*earthGravity);
			

			Sc.getElement(0)->setMass(mass);
			Sc.getElement(0)->place(0, 0, 0);
			//Sc.setForce(G, 0);
			Sc.getElement(0)->addExternalAction(G);

			Sc.update(FallTime);

			Assert::AreEqual(0.5*9.81*FallTime*FallTime, Sc.getElement(0)->pointerToPosition()->zComponent());
		}
		
	};
}
