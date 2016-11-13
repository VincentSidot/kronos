#pragma once
#include <cassert>
#include <iostream>
#include "UsefullFunc.h"


class vFraction
{
public:
	inline vFraction() : m_num{ 0 }, m_den{ 1 } {} // create a fract 0/1
	inline vFraction(const long &num) : m_num{ num }, m_den{ 1 } {} // create frac num/1
	inline vFraction(const int &num) : m_num{ num }, m_den{ 1 } {} // same with int instead of long
	inline vFraction(const std::string &str)
	{
		char buffer[50]{};
		bool test{ false };
		size_t i{ 0 };
		for (auto temp : str)
		{
			if ((temp <= '9' && temp >= '0') || temp == '-')
			{
				buffer[i] = temp;
				++i;
			}
			else if (temp == '/')
			{
				this->setNum(utlity::strto<long>(buffer, i));
				test = true;
				i = 0;
			}
		}
		if(test)
			this->setDen(utlity::strto<long>(buffer, i));
		else
		{
			this->setNum(utlity::strto<long>(buffer, i));
			this->setDen(1);
		}
		setThisIrrational();
	}
	inline vFraction(const long &num, const long &den) // create fraction num/den if den = 0 : assert
	{
		assert(den != 0); //check if den = 0
		if (den < 0) //m_den is unsigned so if den<0 num = -num and den = -den
		{
			m_den = (-den);
			m_num = (-num);
		}
		else //else all is OK 
		{
			m_den = den;
			m_num = num;
		}
		setThisIrrational();
	}
	inline vFraction(const int &num, const int &den) //same but with int 
	{
		assert(den != 0);
		if (den < 0)
		{
			m_den = (-den);
			m_num = (-num);
		}
		else
		{
			m_den = den;
			m_num = num;
		}
		setThisIrrational();
	}
	inline vFraction(const vFraction &frac) // create fraction from other fraction
	{
		this->m_den = frac.den();
		this->m_num = frac.num();
		setThisIrrational();
	}
	inline vFraction(const vFraction &num, const vFraction &den)
	{
		vFraction temp{num};
		temp /= den;
		this->m_den = temp.den();
		this->m_num = temp.num();
		setThisIrrational();
	}
	inline vFraction& operator=(const vFraction &frac)
	{
		this->m_den = frac.den();
		this->m_num = frac.num();
		setThisIrrational();
		return *this;
	}
	static inline vFraction inverse(const vFraction &frac)
	{
		return vFraction(frac.den(), frac.num());
	}
	static inline void sameDenominator(vFraction &frac1, vFraction &frac2)
	{
		frac1.setNum(frac1.num()*frac2.den());
		frac2.setNum(frac2.num()*frac1.den());
		frac1.setDen(frac1.den()*frac2.den());
		frac2.setDen(frac1.den()*frac2.den());
	}
	static inline vFraction setIrrational(const vFraction &frac)
	{
		long gcd{ utlity::getGcd<long>(utlity::abs<long>(frac.den()),utlity::abs<long>(frac.num())) };
		return vFraction(frac.num() / gcd, frac.den() / gcd);
	}
	inline void setDen(const long &den) {
		assert(den != 0);
		if (den < 0)
		{
			m_num = -m_num;
			m_den = -den;
		}
		else m_den = den;
	}
	inline void setNum(const long &num)
	{
		m_num = num;
	}
	inline long num() const { return m_num; }
	inline unsigned long den() const { return m_den; }
	inline vFraction& operator++()
	{
		this->m_num += this->m_den;
		setThisIrrational();
		return *this;
	} //operator ++
	inline vFraction& operator--()
	{
		this->m_num -= this->m_den;
		setThisIrrational();
		return *this;
	} //operator --
	inline vFraction operator++(int)
	{
		vFraction temp(*this);
		operator++();
		temp = setIrrational(temp);
		return temp;
	}
	inline vFraction operator--(int)
	{
		vFraction temp(*this);
		operator--();
		temp = setIrrational(temp);
		return temp;
	}
	inline vFraction& operator+=(const vFraction &frac)
	{
		vFraction temp1{ *this }, temp2{ frac };
		sameDenominator(temp1, temp2);
		this->m_num = temp1.num() + temp2.num();
		this->m_den = temp1.den();
		setThisIrrational();
		return *this;
	}
	inline vFraction& operator-=(const vFraction &frac)
	{
		vFraction temp1{ *this }, temp2{ frac };
		sameDenominator(temp1, temp2);
		this->m_num = temp1.num() - temp2.num();
		this->m_den = temp1.den();
		setThisIrrational();
		return *this;
	}
	inline vFraction& operator+=(const long &num)
	{
		this->m_num += num * this->m_den;
		setThisIrrational();
		return *this;
	}
	inline vFraction& operator-=(const long &num)
	{
		this->m_num -= num * this->m_den;
		setThisIrrational();
		return *this;
	}
	inline vFraction& operator*=(const long &num)
	{
		this->m_num *= num;
		setThisIrrational();
		return *this;
	}
	inline vFraction& operator/=(const long &num)
	{
		this->m_den *= num;
		setThisIrrational();
		return *this;
	}
	inline vFraction& operator*=(const vFraction &frac)
	{
		this->m_den *= frac.den();
		this->m_num *= frac.num();
		setThisIrrational();
		return *this;
	}
	inline vFraction& operator/=(const vFraction &frac)
	{
		this->m_den *= frac.num();
		this->m_num *= frac.den();
		setThisIrrational();
		return *this;
	}
	template<class T>
	inline T aproximateValue() const
	{
		T num{ static_cast<T>(this->m_num) };
		T den{ static_cast<T>(this->m_den) };
		return T{ num/den};
	}
	template<class T>
	static inline T aproximateValue(const vFraction &frac)
	{
		return frac.aproximateValue<T>();
	}
private:
	inline void setThisIrrational()
	{
		long gcd{ utlity::getGcd<long>(utlity::abs<long>(this->m_den),utlity::abs<long>(this->m_num)) };
		this->m_den = this->m_den / gcd;
		this->m_num = this->m_num / gcd;
	}
	long m_num;
	unsigned long m_den;
};


inline std::ostream& operator<<(std::ostream& os, const vFraction &frac)
{
	if (frac.den() == 1)
	{
		os << frac.num();
	}
	else
	{
		os << frac.num() << "/" << frac.den();
	}
	return os;
}
inline std::istream& operator >> (std::istream& is, vFraction &frac)
{
	char temp[1]{};
	char buffer[50]{};
	bool test{ false };
	size_t i{ 0 };
	while (is.read(temp, 1))
	{
		if ((*temp <= '9' && *temp >= '0') || *temp == '-')
		{
			buffer[i] = *temp;
			++i;
		}
		else if (*temp == '/')
		{
			frac.setNum(utlity::strto<long>(buffer, i));
			test = true;
			i = 0;
		}
	}
	if (test)
		frac.setDen(utlity::strto<long>(buffer, i));
	else
		frac.setDen(1);
	frac = vFraction::setIrrational(frac);
	return is;
}
inline void operator >> (const std::string& str, vFraction &frac)
{
	frac = vFraction(str);
}
inline void operator<<(vFraction &frac, const std::string &str)
{
	frac = vFraction(str);
}
inline vFraction operator+(const vFraction &frac1, const vFraction &frac2)
{
	vFraction temp1{ frac1 };
	temp1 += frac2;
	return temp1;
}
inline vFraction operator-(const vFraction &frac1, const vFraction &frac2)
{
	vFraction temp1{ frac1 };
	temp1 -= frac2;
	return temp1;
}
inline vFraction operator+(const vFraction &frac1, const long &num)
{
	vFraction temp1{ frac1 };
	temp1 += num;
	return temp1;
}
inline vFraction operator-(const vFraction &frac1, const long &num)
{
	vFraction temp1{ frac1 };
	temp1 -= num;
	return temp1;
}
inline vFraction operator+(const long &num, const vFraction &frac1)
{
	vFraction temp1{ frac1 };
	temp1 += num;
	return temp1;
}
inline vFraction operator-(const long &num, const vFraction &frac1)
{
	vFraction temp1{ frac1 };
	temp1 -= num;
	return temp1;
}
inline vFraction operator*(const vFraction &frac1, const vFraction &frac2)
{
	vFraction temp{ frac1 };
	temp *= frac2;
	return temp;
}
inline vFraction operator*(const long &num, const vFraction &frac1)
{
	vFraction temp{ frac1 };
	temp *= num;
	return temp;
}
inline vFraction operator*(const vFraction &frac1, const long &num)
{
	vFraction temp{ frac1 };
	temp *= num;
	return temp;
}
inline vFraction operator/(const vFraction &frac1, const vFraction &frac2)
{
	vFraction temp{ frac1 };
	temp /= frac2;
	return temp;
}
inline vFraction operator/(const long &num, const vFraction &frac1)
{
	vFraction temp{ frac1 };
	temp /= num;
	return temp;
}
inline vFraction operator/(const vFraction &frac1, const long &num)
{
	vFraction temp{ frac1 };
	temp /= num;
	return temp;
}
inline bool operator<(const vFraction &frac1, const vFraction &frac2)
{
	vFraction temp1{ frac1 }, temp2{ frac2 };
	vFraction::sameDenominator(temp1, temp2);
	return temp1.num() < temp2.num();
}
inline bool operator>(const vFraction &frac1, const vFraction &frac2)
{
	return !(frac1 < frac2);
}
inline bool operator==(const vFraction &frac1, const vFraction &frac2)
{
	vFraction temp1{ frac1 }, temp2{ frac2 };
	vFraction::sameDenominator(temp1, temp2);
	return temp1.num() == temp2.num();
}
inline bool operator!=(const vFraction &frac1, const vFraction &frac2)
{
	return !(frac1 == frac2);
}
inline bool operator>=(const vFraction &frac1, const vFraction &frac2)
{
	return (frac1 > frac2) || (frac1 == frac2);
}
inline bool operator<=(const vFraction  &frac1, const vFraction &frac2)
{
	return (frac1 < frac2) || (frac1 == frac2);
}

