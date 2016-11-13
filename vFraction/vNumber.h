#pragma once

#include "vFraction.h"
#include "UsefullFunc.h"
#include <sstream>


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
		}
		else if (str == "-inf")
		{
			m_number = 0;
			m_isInfinite = true;
			m_isNegative = true;
		}
		else
		{
			m_number << str;
			m_isInfinite = false;
			m_isNegative = false;
		}
	}
	inline vNumber(const vFraction &frac) : m_isInfinite{ 0 }, m_number{ frac }, m_isNegative{ frac < 0 } {}
	inline std::string disp() {
		std::stringstream temp;
		if (m_isInfinite)
		{
			if (m_isNegative)
				temp << "-inf";
			else
				temp << "+inf";
		}
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
	inline vFraction number() const { return m_number; }
	inline vNumber& operator=(const vNumber other)
	{

	}

private:
	vFraction m_number;
	bool m_isInfinite;
	bool m_isNegative;
};