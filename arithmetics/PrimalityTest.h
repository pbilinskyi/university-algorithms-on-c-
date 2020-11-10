#pragma once
#include "BigInteger.h"



class PrimalityTest {
public: 
	virtual bool isPrime(const BigInteger&) = 0;
};

class FermatTest : public PrimalityTest {
public:
	BigInteger ModularExponentiation(const BigInteger& a, const BigInteger& pow, const BigInteger& N);
	bool isPrime(const BigInteger&);
};