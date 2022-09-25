#define _CRT_SECURE_NO_WARNINGS
class Date
{
public:
	// 全缺省的构造函数
	Date(int year = 1900, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
	}
	// 拷贝构造函数
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	// 析构函数
	~Date()
	{
		_day = _month = _year = 0;
	}

	// 获取某年某月的天数
	int GetMonthDay(int year, int month)
	{
		static int arr[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		if (month == 2 &&
			( (year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
		{
			arr[month] = 29;
		}
		return arr[month];
	}
	// 赋值运算符重载
  // d2 = d3 -> d2.operator=(&d2, d3)
	Date& operator=(const Date& d)
	{
		if (&d == this)
			return *this;
		(*this)._day = d._day;
		(*this)._month = d._month;
		(*this)._year = d._year;
		return *this;
	}
	// 日期+=天数
	Date& operator+=(int day)
	{
		_day += day;
		int x = 0;
		while ((x = GetMonthDay(_year, _month)) <  _day)
		{
			_day -= x;
			_month++;
			if (_month > 12)
			{
				_month = 1;
				_year++;
			}
		}
		return *this;
	}

	// 日期+天数
	Date operator+(int day)
	{
		Date newd(*this);
		newd._day += day;
		int x = 0;
		while ((x = GetMonthDay(newd._year, newd._month)) < newd._day)
		{
			newd._day -= x;
			newd._month++;
			if (newd._month > 12)
			{
				newd._month = 1;
				newd._year++;
			}
		}
		return newd;
	}

	// 日期-天数
	Date operator-(int day)
	{
		Date tmp(*this);
		tmp._day -= day;
		while (tmp._day <= 0)
		{
			--tmp._month;
			if (tmp._month == 0)
			{
				tmp._month = 12;
				tmp._year--;
			}
			tmp._day += GetMonthDay(tmp._year, tmp._month);
		}
		return tmp;
	}
	// 日期-=天数
	Date& operator-=(int day)
	{
		_day -= day;
		while (_day <= 0)
		{
			--_month;
			if (_month == 0)
			{
				_month = 12;
				_year--;
			}
			_day += GetMonthDay(_year, _month);
		}
		return *this;
	}
	// 前置++
	Date& operator++()
	{
		*this += 1;
		
		return *this;
	}
	// 后置++,返回++之前的值
	Date operator++(int)
	{
		Date tmp(*this);
		*this += 1;
		return tmp;
	}
	// 后置--
	Date operator--(int)
	{
		Date tmp(*this);
		*this -= 1;
		return tmp;
	}
	// 前置--
	Date& operator--()
	{
		*this -= 1;
		return *this;
	}
	// >运算符重载
	bool operator>(const Date& d)
	{
		//年大
		if (_year > d._year)
			return true;
		//年相等，月大
		else if (_year == d._year && _month > d._month)
			return true;
		//年相等，月相等，天大
		else if (_year == d._year && _month == d._month && _day > d._day)
			return true;
		else
			return false;
	}
	// ==运算符重载
	bool operator==(const Date& d)
	{
		return (_year == d._year)
			&&(_month == d._month)
			&& (_day == d._day);
	}
	// >=运算符重载
	bool operator >= (const Date& d)
	{
		return (*this > d) || (*this == d);
	}
	// <运算符重载
	bool operator < (const Date& d)
	{
		return !(*this >= d);
	}
	// <=运算符重载
	bool operator <= (const Date& d)
	{
		return !(*this > d);
	}
	// !=运算符重载
	bool operator != (const Date& d)
	{
		return !(*this == d);
	}
	// 日期-日期 返回天数
	int operator-(const Date& d)
	{
		Date max = *this;
		Date min = d;
		int flag = 1;
		if (max < min)
		{
			max = d;
			min = *this;
			flag = -1;
		}
		int n = 0;
		while (min != max)
		{
			n++;
			min++;
		}
		return flag*n;
	}
private:
	int _year;
	int _month;
	int _day;
};