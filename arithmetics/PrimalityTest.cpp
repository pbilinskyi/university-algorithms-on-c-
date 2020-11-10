#include "PrimalityTest.h"
#include <cstring>

BigInteger FermatTest::ModularExponentiation(const BigInteger & a, const BigInteger & pow, const BigInteger& N)
{
	BigInteger res = a % N;
	for (BigInteger k("01"); k < pow; ++k) {
		res = res * a;
	
		res = res %  N;
	};
	return res;
}

bool FermatTest::isPrime(const BigInteger& I)
{
	bool flag = true;
	BigInteger a("01");
	while (a < I && flag) {
		flag =  std::strcmp(ModularExponentiation(a, I - BigInteger("1"), I).get(), "1") == 0 ;
	}
	return flag;
}
