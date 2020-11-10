#pragma once
#include "BigInteger.h"

class MultiplicationAlg {
public:
	virtual BigInteger multiply(BigInteger const& i1, BigInteger const& i2) = 0;
};
