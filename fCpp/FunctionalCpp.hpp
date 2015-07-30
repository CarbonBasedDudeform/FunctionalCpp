#pragma once
#include <functional>
#include <algorithm>

namespace FunctionalCPP {
	template<typename T>
	using val = const T;

	template<typename T>
	using Func = std::function < T > ;

	class Functional {
	public :
		Functional() {};

		template<typename T>
		const std::vector<T> map(const std::vector<T> collection, const Func<T(T)> op) const {
			std::vector<T> copy;

			for (auto iter = collection.begin(); iter != collection.end(); iter++) {
				copy.push_back(op((*iter)));
			}

			return copy;
		};
	};

}