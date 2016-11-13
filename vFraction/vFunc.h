#pragma once
#include <iostream>
#include <functional>
#include <string>
#include <cassert>

template<class T>
class vFunc
{
public:

	inline bool isSame(vFunc const &other) const {
		return this->m_id == other.id();
	}
	inline bool operator==(vFunc const &other) const {
		return issame(other);
	}
	inline vFunc(const std::string &name,const std::string &symbol) : m_symbol{symbol} , m_name{name} ,m_id{std::hash<std::string>()(name)}{}
	inline T operator()(const T &a, const T &b)
	{
		return func2arg(a, b);
	}
	inline T operator()(const T &a)
	{
		return func1arg(a);
	}

	inline virtual T func2arg(const T &a, const T &b) = 0 {}
	inline virtual T func1arg(const T &a) = 0 {}
	~vFunc()
	{
	}

	inline size_t id() const { return m_id; }
	inline std::string name() const { return m_name; }
	inline std::string symbol() const { return m_symbol; }
	inline void setSymbol(const std::string &sym) { this->m_symbol = sym; }
	inline void setName(const std::string &name) { this->m_name = name; this->m_id = std::hash<std::string>()(name); }

protected:
	size_t m_id;
	std::string m_name;
	std::string m_symbol;
};


template<class T>
class vAdd : public vFunc<T>
{
public:
	inline vAdd() : vFunc("addition","+") {}
	inline virtual T func(const T &a, const T &b) { return a + b; }
};
template<class T>
class vSub : public vFunc<T>
{
public:
	inline vSub() : vFunc("subtractions", "-") {}
	inline virtual T func(const T &a, const T &b) { return a - b; }
};
template<class T>
class vMult : public vFunc<T>
{
public:
	inline vMult() : vFunc("multiplication", "*") {}
	inline virtual T func(const T &a, const T &b) { return a * b; }
};
template<class T>
class vDiv : public vFunc<T>
{
public:
	inline vDiv() : vFunc("divide", "/") {}
	inline virtual T func(const T &a, const T &b) { assert(b != 0); return a / b; }
};
template<class T>
class vPow : public vFunc<T>
{
public:
	inline vPow() : vFunc("power", "^") {}
	inline virtual T func(const T &a, const T &b) {  return pow<a>(b); }
private:
	template<T x>
	inline T pow(const T &n)
	{
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
				return T{ pow<T, x*x>(n / 2) };
			}
			else
			{
				return T{ pow<T, x*x>(n / 2) * x };
			}
		}
	}
};
