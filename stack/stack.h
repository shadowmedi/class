#pragma once
#include <vector>
#include <deque>
using namespace std;
namespace xm
{
	template <class T, class Container = deque<T>>
	class stack
	{
	public:
		void push(T& x)
		{
			_con.push_back(x);
		}

		void pop()
		{
			_con.pop_back();
		}

		T& top()
		{
			return _con.back();
		}

		const T& top()const
		{
			return _con.back();
		}

		bool empty()const
		{
			return _con.empty();
		}

		int size()const
		{
			return _con.size();
		}

	private:
		Container _con;
	};
}