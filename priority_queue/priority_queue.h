#pragma once
#include <iostream>
#include <vector>
using namespace std;
namespace xm
{
	//默认是大堆
	template<class T, class Container = vector<T>, class Compare = std::less<T>>
	class priority_queue
	{
	public:
		priority_queue()
		{
		}

		priority_queue(T* begin, T* end)
		{
			while (begin != end)
			{
				_con.push_back(*begin);
				begin++;
			}
			for (int i = (_con.size() - 1 - 1) / 2; i >= 0; i--)
			{
				adjustDown(i);
			}
		}

		//向上调整
		void adjustUp(int aim)
		{
			Compare com;
			int parent = (aim - 1) / 2;
			while (aim > 0)
			{
				if (com(_con[parent], _con[aim]))
				{
					std::swap(_con[aim], _con[parent]);
					aim = parent;
					parent = (aim - 1) / 2;
				}
				else
					return;
			}
		}

		void push(T& x)
		{
			_con.push_back(x);
			adjustUp(_con.size() - 1);
		}

		//向下调整
		void adjustDown(int aim)
		{
			Compare com;
			int max_child = aim * 2 + 1;
			while (max_child < _con.size())
			{
				if (
					max_child + 1 < _con.size() && 
					com(_con[max_child], _con[max_child + 1]) 
					)
				{
					max_child++;
				}
				if (com(_con[aim],_con[max_child]))
				{
					std::swap(_con[max_child], _con[aim]);
					aim = max_child;
				}
				else
					return;
			}
		}

		void pop()
		{
			swap(_con.front(), _con.back());
			_con.pop_back();
			adjustDown(0);
		}

	private:
		Container _con;
	};
}