#include "stdafx.h"
#include "CppUnitTest.h"

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

		static val<int> multiply(val<int> x, val<int> y) {
			return x * y;
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
			List<val<int>> myInts{ 1, 2, 3, 4, 5 };
			Functional F;
			auto newInts = F.map<val<int>>(myInts, [](val<int> x){ return x*x; });

			List<int> expectedInts{ 1, 4, 9, 16, 25 };

			for (int index = 0; index < 5; index++)
			{
				Assert::AreEqual( newInts.get(index), expectedInts.get(index) );
			}
		}

		//Gets a pure context where all functions are pure and nothing is mutable within
		TEST_METHOD(PureContextHappyPath)
		{
			auto fpContext = Functional::GetContext();

			val<int> expected = 1 + 1;
			val<int> result = fpContext->pure<int>([]() {
				Func<val<int>(val<int>, val<int>)> myAdd = [](val<int> x, val<int> y) { return x + y;  };

				return myAdd(1, 1);
			});

			Assert::AreEqual(expected, result);
		}

		//there's no such thing as a truly immutable type in C++
		TEST_METHOD(ToHellWithYourConst)
		{
			auto fpContext = Functional::GetContext();

			val<int> expected = 1 + 1;
			val<int> result = fpContext->pure<int>([]() {
				Func<val<int>(val<int>, val<int>)> myAdd = [](val<int> x, val<int> y) { return x + y;  };

				return myAdd(1, 1);
			});

			//turns the cosnt int (val<int>) into a non-const int and grabs the address of the result variable in memory
			int * ptrToResults = &(int)result;
			//modifies the value stored at the address of the const int variable
			*ptrToResults = 3;
			//result is now 3

			Assert::AreNotEqual(expected, result);
		}

		TEST_METHOD(FilterSequentualList1to10into1to5)
		{
			auto fpContext = Functional::GetContext();

			Assert::Fail();
		}

		//vs2015 no longer allows collections of type const, so testing hand-rolled const linked list
		TEST_METHOD(InsertElementAtEndOfList)
		{
			List<int> myList;

			myList.insert(5);

			val<int> expected = 5;
			val<int> result = myList.get(0);
			Assert::AreEqual(expected, result);
		}

		//Retrieve the size of a list
		TEST_METHOD(GetSizeOfList)
		{
			List<int> myList;

			myList.insert(5);
			val<int> expected = 1;
			val<int> result = myList.size();

			Assert::AreEqual(expected, result);
		}

		//create a copy of a list
		TEST_METHOD(ListCopyAssignment)
		{
			List<val<int>> myInts{ 1, 2, 3, 4, 5 };
			auto newInts = myInts;

			for (int index = 0; index < 5; index++)
			{
				Assert::AreEqual( newInts.get(index), myInts.get(index) );
			}
		}
		//ForEach over a List
		TEST_METHOD(ForEachOverList)
		{
			Assert::Fail();
		}

		//Function Composition Test: f . g = f(g(x))
		TEST_METHOD(SimpleFunctionCompositionTest)
		{
			auto F = Functional::GetContext();
			Func<val<int>(val<int>)> myFunc = [](val<int> x) { return x + 1; };
			Func<val<int>(val<int>)> myOtherFunc = [](val<int> x) { return x * 2; };

			Func<val<int>(val<int>)> composedFunction = F->compose<val<int>>(myOtherFunc, myFunc);

			val<int> expected = (2)*(1 + 1);
			val<int> result = composedFunction(1);

			Assert::AreEqual(expected, result);
		}
	};
}