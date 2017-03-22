#pragma once
#ifndef COMPLEX_H
#define COMPLEX_H
#include <iostream>
#include <cmath>

using namespace std;

class Complex
{

	//NON-member functions:
	//overload: insertion
	friend ostream& operator<<(ostream&, const Complex&);
	//overload: extraction
	friend istream& operator>>(istream&, Complex&);

private:
	double real, //real value
		imag;	//imaginary value

public:
	//parameterized constructor with default arguments
	Complex(double = 0.0, double = 0.0);

	//setters
	void setComplex(double, double);

	//getters
	void getComplex(double&, double&) const;

	//overloaded operators
	//overload: sum
	Complex operator+(const Complex&) const;
	//overload: substraction
	Complex operator-(const Complex&) const;
	//overload: multiplication
	Complex operator*(const Complex&) const;
	//overload: division
	Complex operator/(const Complex&) const;
	//overload: conjugate
	Complex operator~() const;
	//overload: absolute value
	double operator!() const;
	//overload: if equals
	bool operator==(const Complex&) const;

};	
#endif

//parameterized constructor
Complex::Complex(double r, double i) : real(r), imag(i) {}

//setters
void Complex::setComplex(double r, double i)
{
	real = r;
	imag = i;
}

//getters
void Complex::getComplex(double & r, double & i) const
{
	r = real;
	i = imag;
}

//overloaded operators
//overload: sum
Complex Complex::operator+(const Complex&other) const
{
	//add real and imaginary values and initialize object
	//using these values
	return Complex(real + other.real, imag + other.imag);
}

//overload: substraction
Complex Complex::operator-(const Complex&other) const
{
	//substract real and imaginary values and initialize object
	//using these values
	return Complex(real - other.real, imag - other.imag);
}

//overload: multiplication
Complex Complex::operator*(const Complex&other) const
{
	//multiply real and imaginary values and initialize object
	//using these values
	return Complex((real*other.real - imag*other.imag),		/* real side */
		(real*other.imag + imag*other.real));			/* imaginary side */
}

//overload: division
Complex Complex::operator/(const Complex&other) const
{
	//divide real and imaginary values and initialize object
	//using these values

	return

		Complex((real*other.real + imag*other.imag) /
		(pow(other.real, 2) + pow(other.imag, 2)),		/* real side */

		(-1 * real*other.imag + imag*other.real) /
		(pow(other.real, 2) + pow(other.imag, 2)));		/* imaginary side */
}

//overload: conjugate
Complex Complex::operator~() const
{
	//conjugate complex object and return object initialized
	//with these values
	return Complex(real, -1 * imag);
}

//overload: absolute value
double Complex::operator!() const
{
	//compute absolute value and return an initialized object
	//with these values
	return (sqrt(pow(real, 2) + pow(imag, 2)));
}

//overload: if equals
bool Complex::operator==(const Complex& other) const
{
	//returns true if data members are equal
	//else returns false
	return (real == other.real && imag == other.imag);
}

//NON-member functions:
//overload: insertion
ostream& operator<<(ostream& output, const Complex& complex)
{
	//send complex number to output
	output << "(" 
			<< complex.real
			<< ", "
			<< complex.imag
			<< ")";
	//return complex number string
	return output;
}

//overload: extraction
istream& operator >> (istream& input, Complex& complex)
{
	char ch; //receives characters '('       ','        ')'
	input >> ch
		>> complex.real
		>> ch
		>> complex.imag
		>> ch;
	return input;
}