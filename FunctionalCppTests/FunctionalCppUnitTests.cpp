#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>

#include <FunctionalCpp.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace Functional;

namespace FunctionalCppTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		int testOp(int x, int y, Func<int(int, int)> op)
		{
			return op(x, y);
		}

		static int add(int x, int y) {
			return x + y;
		}
		//Tests that a function can be passed into another function
		TEST_METHOD(HigherOrderFunctionTest)
		{
			Func<int(int, int)> localAdd = add;
			auto expected = add(1, 1);
			auto result = testOp(1, 1, localAdd);
			
			Assert::AreEqual(expected, result);
		}

		//Lambdas can be passed into another function
		TEST_METHOD(LambdasHigherOrderFunctionTest)
		{
			Func<int(int, int)> myAdd = [](int x, int y) { return x + y;  };
			auto expected = 1 + 1;
			auto result = testOp(1, 1, myAdd);

			Assert::AreEqual(expected, result);
		}


		//maps a function onto a set of values
		TEST_METHOD(MapValueOnToCollection)
		{
			std::vector<int> myInts{ 1, 2, 3, 4, 5 };

			auto newInts = map<int>(myInts, [](int x){ return x*x; });

			std::vector<int> expectedInts{ 1, 4, 9, 16, 25 };

			for (unsigned int i = 0; i < myInts.size(); ++i)
			{
				Assert::AreEqual(newInts[i], expectedInts[i]);
			}
		}

	};
}