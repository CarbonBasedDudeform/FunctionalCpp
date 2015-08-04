#pragma once
#include <iostream>
#include <typeinfo>

#include <FunctionalCpp.hpp>

using namespace std;
using namespace FunctionalCPP;

int main()
{
	cout << "Demo App for functional C++" << endl;
	/*
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

	List<float> myFloats = { 1.0f, 2.0f, 3.0f };
	*/
	cin.get();
	return 0;
}