#pragma once
#include <ostream>

class BigInteger {
	char * s;
public:
	BigInteger();
	BigInteger(const char*);
	BigInteger(const BigInteger&);
	BigInteger(BigInteger&&);
	BigInteger& operator=(BigInteger const &);
	BigInteger& operator=(BigInteger&&);
	BigInteger& operator=(const char*);
	~BigInteger();


	BigInteger operator *(const BigInteger& other) const;
	BigInteger operator /(const BigInteger& other) const;
	BigInteger operator %(const BigInteger& other) const;

	friend std::ostream &operator<<(std::ostream &output, const BigInteger &i);

	//Left shift
	BigInteger operator <<(size_t) const;
	//Right shift
	BigInteger operator >>(size_t) const;

	BigInteger operator +(const BigInteger& other) const;
	BigInteger operator -(const BigInteger& other) const;

	BigInteger& operator++();
	BigInteger& operator--();

	char operator[](int i) const;

	bool operator==(const BigInteger& other) const;
	bool operator>(const BigInteger& other) const;
	bool operator>=(const BigInteger& other) const;
	bool operator<(const BigInteger& other) const;
	bool operator<=(const BigInteger& other) const;

	char* get() const noexcept;
	void concat(const BigInteger&);
	void concat(const char*);
	void concatFront(char);
	bool isNull() const noexcept;
	void print() const noexcept;
};