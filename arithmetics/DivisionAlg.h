#pragma once
#include "BigInteger.h"

class DivisionAlg {
public:
	// pair{quotient, remainder}
	std::pair<BigInteger, BigInteger> div(const BigInteger&, const BigInteger&) const;
};