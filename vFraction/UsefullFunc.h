#pragma once
#include <string>
class utlity
{
public:

	template<class T>
	static inline T strto(const char* str, const size_t &strlen)
	{
		T temp{ 0 };
		if (str[0] != '-')
		{
			for (size_t i{ 0 }; i < strlen; ++i)
			{
				temp += (str[i] - '0')* pow<T, 10>((strlen - 1) - i);
			}
		}
		else
		{
			for (size_t i{ 1 }; i < strlen; ++i)
			{
				temp += (str[i] - '0')* pow<T, 10>((strlen - 1) - i);
			}
			temp = -temp;
		}
		return temp;
	}
	template<class T>
	static inline T strto(const std::string &str)
	{
		return strto<T>(str.c_str(), str.length());
	}
	template<class T, T x>
	static inline T pow(size_t n)
	{
		if (x == 0)
		{
			return T{ 0 };
		}
		else if (n == 0)
		{
			return T{ 1 };
		}
		else if (n == 1)
		{
			return T{ x };
		}
		else if (n % 2 == 0)
		{
			return T{ utlity::pow<T, x * x>(n / 2) };
		}
		else
		{
			return T{ utlity::pow<T, x * x>(n / 2) * x };
		}
	}
	template<class T>
	static inline T abs(const T &a)
	{
		return (a < 0) ? -a : a;
	}
	template<class T>
	static inline T getGcd(T a, T b)
	{
		return (b == 0) ? a : getGcd(b, a % b);
	}
	template<typename U>
	static inline std::string readUntil(const std::string &str,const U &test)
	{
		std::string temp{};
		for (auto i : str)
		{
			if (!test(i))
			{
				temp += i;
			}
			else if (test(i))
				return temp;
		}
		return temp;
	}
	template<typename U>
	static inline std::string readUntil(const char *str,size_t strlen, const U &test)
	{
		std::string temp{};
		char tmp{ '\0' };
		for (size_t i{ 0 }; i < strlen || test(tmp); i++)
		{
			tmp = str[i];
			if (!test(tmp))
			{
				temp += tmp;
			}
			else if (test(tmp))
				return temp;
		}
		return temp;
	}

};

