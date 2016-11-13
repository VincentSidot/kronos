#pragma once

#include "vFraction.h"
#include "UsefullFunc.h"
#include <sstream>

vNumber max_sinf("+inf");
vNumber min_inf("-inf");

class vNumber
{
public:
	inline vNumber(const std::string &str)
	{
		if (str == "+inf")
		{
			m_number = 0;
			m_isInfinite = true;
			m_isNegative = false;
			m_exits = true;
		}
		else if (str == "-inf")
		{
			m_number = 0;
			m_isInfinite = true;
			m_isNegative = true;
			m_exits = true;
		}
		else
		{
			m_number << str;
			m_isInfinite = false;
			m_isNegative = false;
			m_exits = true;
		}
	}
	inline vNumber(const vFraction &frac) : m_isInfinite{ false }, m_number{ frac }, m_isNegative{ frac < 0 }, m_exits{ true } {}
	inline vNumber() : m_isInfinite{ false }, m_number{ 0 }, m_isNegative{ false }, m_exits{ false } {}
	inline std::string disp() const {
		std::stringstream temp;
		if (m_isInfinite)
		{
			if (m_isNegative)
				temp << "-inf";
			else
				temp << "+inf";
		}
		else if (!m_exits)
			temp << "non real rep";
		else
			temp << m_number;
		return temp.str();
	}
	inline vNumber(const vNumber &other)
	{
		this->m_isInfinite = other.isInfinite();
		this->m_isNegative = other.isnegative();
		this->m_number = other.number();
	}
	inline bool isInfinite() const { return m_isInfinite; }
	inline bool isnegative() const { return m_isNegative; }
	inline bool exits() const { return m_exits; }
	inline vFraction number() const { return m_number; }
	inline vNumber& operator=(const vNumber &other)
	{
		this->m_isInfinite = other.isInfinite();
		this->m_isNegative = other.isnegative();
		this->m_number = other.number();
		return *this;
	}
	inline bool operator==(const vFraction &other)
	{
		if (m_isInfinite)
			return false;
		else
			return m_number == other;
	}
	inline bool operator<=(const vFraction &frac)
	{

	}


private:
	vFraction m_number;
	bool m_isInfinite;
	bool m_isNegative;
	bool m_exits;
};
