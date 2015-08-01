#pragma once
#include <functional>
#include <algorithm>
#include <memory>
#include <vector>

namespace FunctionalCPP {
	template<typename T>
	using val = const T;

	template<typename T>
	using Func = std::function < T > ;

	class Functional {
	public :
		static std::shared_ptr<Functional> GetContext() {
			if (_pureContext == nullptr) {
				_pureContext = std::make_shared<Functional>();
			}

			return _pureContext;
		}

		Functional() {};

		template<typename T>
		const std::vector<T> map(const std::vector<T> collection, const Func<T(T)> op) const {
			std::vector<T> copy;

			for (auto iter = collection.begin(); iter != collection.end(); iter++) {
				copy.push_back(op((*iter)));
			}

			return copy;
		}

		template<typename T>
		const T pure(Func<const T()> const local) const {
			return local();
		}

	private:
		static std::shared_ptr<Functional> _pureContext;
	};

	std::shared_ptr<Functional> Functional::_pureContext = 0;

}