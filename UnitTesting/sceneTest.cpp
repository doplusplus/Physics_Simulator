#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SimModule\Scene.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SceneTest
{
	TEST_CLASS(TestOfScene)
	{
	public:
		TEST_METHOD(ParameterlessMatPoint)
		{
			MaterialPoint M;
			Point P(0, 0, 0);
			MaterialPoint N(P);
			Assert::IsTrue(M == N);
		}

	};
}