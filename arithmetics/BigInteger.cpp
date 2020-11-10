#include "BigInteger.h"
#include "cstring_mng.h"
#include "Karatsuba.h"
#include "DivisionAlg.h"
#include <utility>
#include <iostream>
#include <cstring>
#include <utility>


BigInteger::BigInteger()
{
	s = new char('0');
}

BigInteger::BigInteger(const char* s_init) {
	size_t N = 0;
	while (s_init[N]) ++N;
	s = new char[N + 1];
	strcpy_s(s, (N + 1)*sizeof(char), s_init);
}

BigInteger& BigInteger::operator=(BigInteger const& other) {
	*this = other.s;
	return *this;
}

BigInteger& BigInteger::operator=(BigInteger && other) {
	s = other.s;
	other.s = nullptr;
	return *this;
}

BigInteger & BigInteger::operator=(const char *s_other)
{
	size_t N = cstr::length(s_other);
	if (s) delete[] s;
	s = new char[N + 1];
	strcpy_s(s, (N + 1) * sizeof(char), s_other);
	return *this;
}

BigInteger::~BigInteger()
{
	delete[] s;
}

BigInteger::BigInteger(BigInteger const& i_init) {
	*this = i_init;
}

BigInteger::BigInteger(BigInteger&& i_init) {
	*this = std::move(i_init);
}


BigInteger BigInteger::operator*(const BigInteger & other) const
{
	Karatsuba alg;
	return alg.multiply(*this, other);
}

BigInteger BigInteger::operator/(const BigInteger & other) const
{
	DivisionAlg alg;
	return alg.div(*this, other).first;
}

BigInteger BigInteger::operator%(const BigInteger & other) const
{
	DivisionAlg alg;
	return alg.div(*this, other).second;
}

BigInteger BigInteger::operator<<(size_t N) const
{
	return BigInteger(cstr::left_shift(s, N));
}

BigInteger BigInteger::operator>>(size_t N) const
{
	if (!isNull())	return BigInteger(cstr::right_shift(s, N));
	else return BigInteger("0");
}


BigInteger BigInteger::operator+(const BigInteger & other) const
{
	return BigInteger(cstr::add(this->s, other.s));
}

BigInteger BigInteger::operator-(const BigInteger & other) const
{
	return BigInteger(cstr::subtract(s, other.s));
}

BigInteger& BigInteger::operator++()
{
	size_t N = 0;
	const char* s_init = cstr::add(this->get(), "1");

	while (s_init[N]) ++N;
	s = new char[N + 1];
	strcpy_s(s, (N + 1) * sizeof(char), s_init);
	
	return *this;
}

BigInteger & BigInteger::operator--()
{
	s = cstr::subtract(s, "1");
	return *this;
}

char BigInteger::operator[](int i) const
{
	if (i < 0) throw std::invalid_argument("index is out of array");
	return s[i];
}

bool BigInteger::operator==(const BigInteger & other) const
{
	return (std::strcmp(s, other.s) == 0);
}

bool BigInteger::operator>(const BigInteger & other) const
{
	return (cstr::compare(this->s, other.s) == 1);
}

bool BigInteger::operator>=(const BigInteger & other) const
{
	return (cstr::compare(this->s, other.s) >= 0);
}

bool BigInteger::operator<(const BigInteger & other) const
{
	return (cstr::compare(this->s, other.s) == -1);
}

bool BigInteger::operator<=(const BigInteger & other) const
{
	return (cstr::compare(this->s, other.s) <= 0);
}

char* BigInteger::get() const noexcept {
	return s;
}

void BigInteger::concat(const BigInteger & other)
{
	concat(other.s);
}

void BigInteger::concat(const char *s_other)
{
	size_t N1 = cstr::length(s_other),
		N2 = cstr::length(s);
	char* temp = s;
	s = cstr::merge(s, s_other);
	delete[] temp;
}

void BigInteger::concatFront(char c)
{
	const char* temp = s;
	size_t N = cstr::length(s);
	s = new char[N + 1 + 1];
	strcpy_s(s + 1, (N + 1)* sizeof(char), temp);
	s[0] = c;
	s[N + 1] = '\0';
}

bool BigInteger::isNull() const noexcept
{
	bool res = true;
	const char* c = s;
	while (*c) {
		if (*c != '0') res = false;
		++c;
	}
	return res;
}

void BigInteger::print() const noexcept
{
	std::cout << "-> (" << s << ")" << std::endl;
}

std::ostream & operator<<(std::ostream & output, const BigInteger & i)
{
		output << i.s;
		return output;	
}
