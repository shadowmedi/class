#pragma once
#include <string.h>
#include <assert.h>
#include <iostream>
namespace xm
{
	class string
	{
	public:
		//构造函数

		/*1 传过来的字符串可能是const，因此要new一块空间拷贝字符串
		string(const char* str)
			:_str(new char[strlen(str) + 1])
			, _capacity(strlen(str))
			, _size(0)
		{
			//_str目标字符串,str源字符串
			strcpy(_str, str);
		}*/

		/*2 默认构造函数:无参数
		string()
			:_str(new char[1])
			,_capacity(0)
			,_size(0)
		{
			_str[0] = '\0';
		}*/

		/*3 默认构造函数：全缺省
		初始化列表的成员定义 会按照 成员变量 的声明顺序
		string(const char* str = "")
			:_str(new char[strlen(str)+1])
			,_size(strlen(str))
			,_capacity(strlen(str))
		{
			strcpy(_str, str);
		}*/

//全缺省，因为上面strlen是O(N),进行了三次遍历，改进可以不考虑初始化列表
		string(const char* str = "")
		{
			_size = strlen(str);
			_capacity = _size;
			//注意要多开一个空间给'\0'
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		//拷贝构造函数(深拷贝)——不能让2个对象指向同一块空间
		/*string(const string& s)
			:_str(new char[s._capacity+1])
			,_capacity(s._capacity)
			,_size(s._size)
		{
			strcpy(_str, s._str);
		}*/

		//拷贝构造2.0
		string(const string& s)
			:_str(nullptr)
			, _capacity(0)
			,_size(0)
		{
			//调用构造函数实现拷贝构造
			string tmp = s._str;
			std::swap(tmp._str, _str);
			std::swap(tmp._size, _size);
			std::swap(tmp._capacity, _capacity);
		}


		//析构函数
		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = 0;
			_capacity = 0;
		}


		//普通迭代器——应用于 普通对象
		typedef char* iterator;
		iterator begin()
		{
			return _str;
		}

		iterator end()
		{
			return _str + _size;
		}

		//const迭代器——应用于const对象,只能读，不能修改
		typedef const char* const_iterator;
		const_iterator begin()const
		{
			return _str;
		}

		const_iterator end()const
		{
			return _str + _size;
		}

		//返回C形式的字符串“以'\0'结尾”
		const char* c_str()const
		{
			return _str;
		}

		//返回字符串的长度/大小
		size_t size()const
		{
			return _size;
		}

		//普通对象用[]访问字符时是可读可写的
		char& operator[](size_t pos)
		{
			assert(pos >= 0 && pos < _size);
			return _str[pos];
		}

		//const对象用[]访问字符时是不可修改的
		const char& operator[](size_t pos)const
		{
			assert(pos >= 0 && pos < _size);
			return _str[pos];
		}

		//赋值要手动释放原来的空间
		/*string& operator=(const string& s)
		{
			//自己给自己赋值不需要动
			if (this != &s)
			{
				//深拷贝
				char* tem = new char[s._capacity + 1];
				strcpy(tem, s._str);

				//手动释放原来的空间
				delete[] _str;

				_str = tem;
				_size = s._size;
				_capacity = s._capacity;
			}
			return *this;
		}*/

		void swap(string& s)
		{
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
		}

		////赋值2.0
		//string& operator=(const string& s)
		//{
		//	if (this != &s)
		//	{
		//		string tmp(s._str);
		//		string::swap(tmp);
		//	}
		//	return *this;
		//}

		//赋值3.0
		string& operator=(string s)
		{
			swap(s);
			return *this;
		}

		/*void push_back(char x);
		void append(const char* str);
		string& operator+=(char* str);
		string& operator+=(char x);*/

	private:
		//这里是成员的声明
		char* _str;
		size_t _capacity;
		size_t _size;
	};

	void test_string1()
	{
		string str1("abcdeft");
		str1[0] = '1';
		//[]遍历
		for (size_t i = 0; i < str1.size(); i++)
		{
			std::cout << str1[i];
		}
		std::cout << '\n';

		//迭代器遍历
		string::iterator it = str1.begin();
		while (it != str1.end())
		{
			std::cout << *it;
			it++;
		}
		std::cout << '\n';

		for (auto i : str1)
		{
			std::cout << i;
		}
	}

	void test_string2()
	{
		//拷贝构造
		string s1 = "abcd";
		string s2(s1);
		/*string::iterator it = s2.begin();
		while (it != s2.end())
		{
			std::cout << *it;
			it++;
		}*/

		//赋值
		string s3 = "cdef";
		s3 = s1;
		string::iterator it = s3.begin();
		while (it != s3.end())
		{
			std::cout << *it;
			it++;
		}
		s1 = s1;
	}
}