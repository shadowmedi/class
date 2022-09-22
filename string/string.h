#pragma once
#include <string.h>
#include <assert.h>
#include <iostream>
namespace xm
{
	
	class string
	{
	public:
		//���캯��

		/*1 ���������ַ���������const�����Ҫnewһ��ռ俽���ַ���
		string(const char* str)
			:_str(new char[strlen(str) + 1])
			, _capacity(strlen(str))
			, _size(0)
		{
			//_strĿ���ַ���,strԴ�ַ���
			strcpy(_str, str);
		}*/

		/*2 Ĭ�Ϲ��캯��:�޲���
		string()
			:_str(new char[1])
			,_capacity(0)
			,_size(0)
		{
			_str[0] = '\0';
		}*/

		/*3 Ĭ�Ϲ��캯����ȫȱʡ
		��ʼ���б�ĳ�Ա���� �ᰴ�� ��Ա���� ������˳��
		string(const char* str = "")
			:_str(new char[strlen(str)+1])
			,_size(strlen(str))
			,_capacity(strlen(str))
		{
			strcpy(_str, str);
		}*/

//ȫȱʡ����Ϊ����strlen��O(N),���������α������Ľ����Բ����ǳ�ʼ���б�
		string(const char* str = "")
		{
			_size = strlen(str);
			_capacity = _size;
			//ע��Ҫ�࿪һ���ռ��'\0'
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		//��������
		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = 0;
			_capacity = 0;
		}

		//��ͨ����������Ӧ���� ��ͨ����
		typedef char* iterator;
		iterator begin()
		{
			return _str;
		}

		iterator end()
		{
			return _str + _size;
		}

		//const����������Ӧ����const����,ֻ�ܶ��������޸�
		typedef const char* const_iterator;
		const_iterator begin()const
		{
			return _str;
		}

		const_iterator end()const
		{
			return _str + _size;
		}

		//����C��ʽ���ַ�������'\0'��β��
		const char* c_str()const
		{
			return _str;
		}

		//�����ַ����ĳ���/��С
		size_t size()const
		{
			return _size;
		}

		//��ͨ������[]�����ַ�ʱ�ǿɶ���д��
		char& operator[](size_t pos)
		{
			assert(pos >= 0 && pos < _size);
			return _str[pos];
		}

		//const������[]�����ַ�ʱ�ǲ����޸ĵ�
		const char& operator[](size_t pos)const
		{
			assert(pos >= 0 && pos < _size);
			return _str[pos];
		}


		void push_back(char x);
		void append(const char* str);
		string& operator+=(char* str);
		string& operator+=(char x);

	private:
		//�����ǳ�Ա������
		char* _str;
		size_t _capacity;
		size_t _size;
	};
	void test_string1()
	{
		string str1("abcdeft");
		str1[0] = '1';
		//[]����
		for (size_t i = 0; i < str1.size(); i++)
		{
			std::cout << str1[i];
		}
		std::cout << '\n';

		//����������
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
}