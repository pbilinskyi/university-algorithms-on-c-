#pragma once
#include "BigInteger.h"
#include "MultiplicationAlg.h"

class Karatsuba : public MultiplicationAlg {
public:
	BigInteger multiply(const BigInteger & i1, const BigInteger & i2);
};

