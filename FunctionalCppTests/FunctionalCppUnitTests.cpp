#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>

#include <FunctionalCpp.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FunctionalCPP;

namespace FunctionalCppTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		int testOp(val<int> x, val<int> y, Func<val<int>(val<int>, val<int>)> op)
		{
			return op(x, y);
		}

		static val<int> add(val<int> x, val<int> y) {
			return x + y;
		}
		//Tests that a function can be passed into another function
		TEST_METHOD(HigherOrderFunctionTest)
		{
			Func<val<int>(val<int>, val<int>)> localAdd = add;
			auto expected = add(1, 1);
			auto result = testOp(1, 1, localAdd);

			Assert::AreEqual(expected, result);
		}

		//Lambdas can be passed into another function
		TEST_METHOD(LambdasHigherOrderFunctionTest)
		{
			Func<val<int>(val<int>, val<int>)> myAdd = [](val<int> x, val<int> y) { return x + y;  };
			auto expected = 1 + 1;
			auto result = testOp(1, 1, myAdd);

			Assert::AreEqual(expected, result);
		}


		//maps a function onto a set of values
		TEST_METHOD(MapValueOnToCollection)
		{
			std::vector<val<int>> myInts{ 1, 2, 3, 4, 5 };
			Functional F;
			auto newInts = F.map<val<int>>(myInts, [](val<int> x){ return x*x; });

			std::vector<int> expectedInts{ 1, 4, 9, 16, 25 };

			for (unsigned int i = 0; i < myInts.size(); ++i)
			{
				Assert::AreEqual(newInts[i], expectedInts[i]);
			}
		}
	};
}