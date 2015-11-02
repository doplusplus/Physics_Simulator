#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SimModule2\Scene.h"

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

			double x = Sc.getElement(0)->pointerToPosition()->getX();
			double y = Sc.getElement(0)->pointerToPosition()->getY();
			double z = Sc.getElement(0)->pointerToPosition()->getZ();

			Assert::AreEqual(0.0,x);
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
			
			double FallTime = 10; //seconds
			double mass = 1;
			Force F;
			F.setDirection(0, 0, mass*9.81);

			Sc.getElement(0)->setMass(mass);
			Sc.getElement(0)->setPosition(0, 0, 0);
			Sc.setForce(F, 0);

			Sc.update(FallTime);

			Assert::AreEqual(0.5*9.81*FallTime*FallTime, Sc.getElement(0)->pointerToPosition()->getZ());
		
		}
		

	};
}
