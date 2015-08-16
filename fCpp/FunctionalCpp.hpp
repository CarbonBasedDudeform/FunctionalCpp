#pragma once
#include <functional>
#include <algorithm>
#include <memory>
#include <exception>

namespace FunctionalCPP {
	template<typename T>
	using val = const T;

	template<typename T>
	class ListNode {
	public:
		ListNode(T value) : _value(value), Next(nullptr) {};
		~ListNode() {};
		ListNode * Next;
		const T get() { return _value; }
	private:
		T _value;
	};

	template<class T>
	class List {
	public:
		List() : _head(nullptr), _tail(nullptr), _size(0) {};
		List(List & copy) : _head(nullptr), _tail(nullptr), _size(0) {
			auto size = copy.size();
			for (size_t i = 0; i < size; ++i)
			{
				insert(copy.get(i));
			}
		};

		List(std::initializer_list<val<T>> init_list) : _head(nullptr), _tail(nullptr), _size(0) {
			for (auto item : init_list)
			{
				insert(item);
			}
		}

		~List() {
			ListNode<val<T>> * cur = _head;
			
			bool ElementsExist = cur != nullptr;
			while ( ElementsExist )
			{
				auto NextElement = cur->Next;
				delete cur;
				cur = NextElement;

				ElementsExist = cur != nullptr;
			}
		};


		const bool insert(val<T> obj) {
			ListNode<val<T>> * temp = new ListNode<val<T>>(obj);

			const bool IsFirstElementInList = _head == nullptr;
			if (IsFirstElementInList) {
				_head = temp;
				_tail = temp;
			}
			else {
				_tail->Next = temp;
				_tail = temp;
			}

			++_size;
			return true;
		}

		const val<T> get(const size_t index) const {
			ListNode<val<T>> * elem = _head;
			for (size_t i = 0; i < index; ++i)
			{
				elem = elem->Next;
			}

			return elem->get();
		}

		const size_t size() const {
			return _size;
		}

	private:
		ListNode<val<T>> * _head;
		ListNode<val<T>> * _tail;
		size_t _size;
	};

	template<typename T>
	using Func = std::function < T > ;

	template<typename T>
	static Func<T(T)> curry(Func<T(T, T)> someFunction, T someArg) {
		return [=](T arg) { return someFunction(someArg, arg); };
	}

	template<typename T>
	static List<T> map(const List<T> collection, const Func<T(T)> op) {
		List<T> copy;

		const size_t size = collection.size();
		for (size_t i = 0; i < size; ++i)
		{
			copy.insert(op(collection.get(i)));
		}

		return copy;
	}

	template<typename T>
	static const Func<T(T)> compose(Func<T(T)> f, Func<T(T)> g)
	{
		auto composedFunc = [=](T arg) { return f(g(arg)); };
		return composedFunc;
	}

	template<typename T>
	static List<T> filter(const List<T> collection, Func<bool(T)> predicate)
	{
		List<T> copy;

		const size_t size = collection.size();
		for (size_t i = 0; i < size; ++i)
		{
			if (predicate(collection.get(i)))
			{
				copy.insert(collection.get(i));
			}
		}

		return copy;
	}

	template<typename T>
	static List<T> generate(T base, T limit, Func<bool(T)> predicate)
	{
		List<T> list;

		T current = base;

		while (current != limit)
		{
			if (predicate(current))
			{
				list.insert(current);
			}

			current++;
		}

		return list;
	}

	template<typename T>
	static List<T> generate(T base, T limit, Func<bool(T)> predicate, Func<T(T)> transform)
	{
		List<T> list;

		T current = base;

		while (current <= limit)
		{
			if (predicate(current))
			{
				list.insert(current);
			}

			current = transform(current);
		}

		return list;
	}

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
		const T pure(Func<const T()> const local) const {
			return local();
		}


	private:
		static std::shared_ptr<Functional> _pureContext;
	};

	std::shared_ptr<Functional> Functional::_pureContext = 0;

}