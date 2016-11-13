#pragma once
#include "UsefullFunc.h"
#include "vNumber.h"
#include <string>
#include <sstream>

class vDefinition
{
public:

	vDefinition()
	{
	}

	~vDefinition()
	{
	}
private:

};



class vIntervalle
{
public:
	inline vIntervalle(const std::string &str)  //string is like "[a;b["   you can use +inf or -inf, this programme don't use complex for now
	{
		setIntervalle(str);
	}
	inline vIntervalle(const vIntervalle &other)
	{
		m_a = other.a();
		m_b = other.b();
		this->m_aInclude = other.aInclude();
		this->m_bInclude = other.bInclude();
	}
	inline void setIntervalle(const std::string &str) //string is like "[a;b["   you can use +inf or -inf, this programme don't use complex for now
	{
		if (str[0] == '[')
			this->m_aInclude = true;
		else if (str[0] == ']')
			this->m_aInclude = false;
		std::string test{ ++str.begin(),str.end() };
		test = utlity::readUntil(test, [](char car) {return car == ';' ||car == ','; });
		m_a = vFraction(test);
		bool boolean{ false };
		test.clear();
		for (auto i : str)
		{
			if (boolean)
				test += i;
			else if (i == ';' || i == ',')
				boolean = true;
		}
		if (test[test.length() - 1] == '[')
			this->m_bInclude = false;
		else if (test[test.length() - 1] == ']')
			this->m_bInclude = true;
		test.erase(test.length() - 1, 1);
		m_b = vFraction(test);
	}
	inline std::string disp() const {
		std::stringstream temp;
		if (m_aInclude)
			temp << '[';
		else
			temp << ']';
		temp << m_a << ';' << m_b;
		if (!m_bInclude)
			temp << '[';
		else
			temp << ']';
		return temp.str();
	}
	inline vFraction a() const { return m_a; }
	inline vFraction b() const { return m_b; }
	inline bool aInclude() const { return this->m_aInclude; }
	inline bool bInclude() const { return this->m_bInclude; }
	inline vIntervalle& operator=(const vIntervalle &other)
	{
		this->m_a = other.a();
		this->m_b = other.b();
		this->m_aInclude = other.aInclude();
		this->m_bInclude = other.bInclude();
		return *this;
	}
private:
	vNumber m_a;
	vNumber m_b;
	bool  m_aInclude;
	bool m_bInclude;
};
inline std::ostream& operator<<(std::ostream &os, const vIntervalle &inter)
{
	os << inter.disp();
	return os;
}
inline void operator>>(const std::string &str, vIntervalle &inter)
{
	inter.setIntervalle(str);
}
inline void operator<<(vIntervalle &inter, const std::string &str)
{
	inter.setIntervalle(str);
}
