#include <iostream>
#include "complex.h"

struct Complex {
	float re;
	float im;
	Complex(float _re, float _im) : re(_re), im(_im) {};
	Complex(float _re) : re(_re), im(0) {};
	Complex() : re(0), im(0) {};
	~Complex() {};
	Complex operator +(const Complex& c) const
	{
		return Complex(this->re + c.re, this->im + c.im);
	}
	Complex operator -(const Complex& c) const
	{
		return Complex(this->re - c.re, this->im - c.im);
	}
	Complex operator *(const Complex& c) const
	{
		return Complex(this->re * c.re - this->im * c.im, this->im * c.re + this->re * c.im;);
	}
	Complex operator /(const Complex& c) const
	{
		float nre = (this->im * c.re + this->im * c.im) / (c.re * c.re + c.im * c.im);
		float nim = (this->im*c.re - c.im*this->re) / (c.re * c.re + c.im * c.im);
		return Complex(nre, nim);
	}
	bool operator == (const Complex& c) const
	{
		if ((this->im == c.im) && (this->re == c.re))
			return true;
		else
			return false;
	}
	const Complex& operator = (const Complex& c)
	{
		this->re = c.re;
		this->im = c.im;
	}
	const Complex& operator += (const Complex& c)
	{
		this->re = this->re + c.re;
		this->im = this->im + c.im;
	}
	const Complex& operator -= (const Complex & c)
	{
		this->re = this->re - c.re;
		this->im = this->im - c.im;
	}
	Complex& operator ++()
	{
		this->re = this->re + 1;
	}
	Complex& operator --()
	{
		this->re = this->re - 1;
	}
	friend std::ostream& operator << (std::ostream& os, const Complex& c)
	{
		os << c.re << " " << c.im << "i";
		return os;
	}
	friend std::istream& operator >> (std::istream& is, Complex& c)
	{
		is >> c.re >> c.im;
		return is;
	}
};