#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
struct Complex {
	float re;
	float im;
	Complex(float _re, float _im);
	Complex(float _re);
	Complex();
	~Complex();
	Complex operator +(const Complex& c) const;
	Complex operator -(const Complex& c) const;
	Complex operator *(const Complex& c) const;
	Complex operator /(const Complex& c) const;
	bool operator == (const Complex& c) const;
	const Complex& operator = (const Complex& c);
	const Complex& operator += (const Complex& c);
	const Complex& operator -= (const Complex& c);
	Complex& operator ++();
	Complex& operator --();
	friend std::ostream& operator << (std::ostream& os, const Complex& c);
	friend std::istream& operator >> (std::istream& is, Complex& c);
};
#endif