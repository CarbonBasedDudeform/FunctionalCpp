#pragma once
#include <iostream>
#include <typeinfo>

#include <FunctionalCpp.hpp>

using namespace std;
using namespace FunctionalCPP;

int main()
{
	cout << "Demo App for functional C++" << endl;
	
	val<int> two = Functional::GetContext()->pure<val<int>>([](){
		return 1 + 1;
	});
	
	cout << "1 + 1 = " << two << endl;
	
	//not perfect as you still have state, but it can only change mutable types within the lambda, nothing outside of it.
	//not really pure as you could write to file or IO within the lambda and then retrieve that later in another call.
	//so F(1) = 1 in the first call, write that to disk, next call F(1) = 2.
	//but it makes it a hassle, making writing pure functions the path of least resistance.
	val<int> res = Functional::GetContext()->pure<val<int>>([](){
		int mutableZero = 0;
		mutableZero++;
		return mutableZero;
	});

	//ignores the constness of types when outputting.
	cout << typeid(res).name() << endl;

	List<float> myFloats = { 1.0f, 2.0f, 3.0f }; //defining a list via list initialisation

	std::cout << "==================" << std::endl;
	std::cout << "list comphrension" << std::endl;
	std::cout << "=================" << std::endl;
	List<float> numbers = generate<float>(0.0f, 1.0f, [](float val) {return true;}, 
													  [](float val) { return val + 0.1f;},
													  [](float val, float otherVal) { return (otherVal - val) < -0.1;});

	//using the map function as foreach...
	map<float>(numbers, [](float val) {
		std::cout << val << std::endl; //...yeah, not exactly pure functional programming
		return val;
	});

	std::cout << "=================================" << std::endl;
	std::cout << "list comphrension and composition" << std::endl;
	std::cout << "=================================" << std::endl;
	//using composition to define a list
	Func<bool(val<int>)> oddNumbers = [](val<int> val) { return (val % 2) != 0;};
	Func<val<int>(val<int>)> GreaterThanFive = [](val<int> val) { if (val > 5) return val; else return 0; };
	Func<val<int>(val<int>)> GreaterThanTen = [](val<int> val) { if (val > 10) return val; else return 0; };

	auto first = compose<val<int>,val<int>, val<int>>(GreaterThanTen, GreaterThanFive);
	auto second = compose<bool,val<int>, val<int>>(oddNumbers, first);
	List<int> oddsNsodds = generate<int>(0, 20, second);

	//using the map function as foreach...
	map<int>(oddsNsodds, [](int val) {
		std::cout << val << std::endl; //...yeah, still not exactly pure functional programming
		return val;
	});

	cin.get();
	return 0;
}