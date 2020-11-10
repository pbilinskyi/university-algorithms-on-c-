#pragma once
#include "MultiplicationAlg.h"

class ToomCook : public MultiplicationAlg {
	BigInteger mult(const BigInteger& U, const BigInteger& V, size_t N);
public:
	BigInteger multiply(const BigInteger& i1, const BigInteger& i2);
};