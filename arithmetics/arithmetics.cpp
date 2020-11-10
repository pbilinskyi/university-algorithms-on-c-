/*#include "arithmetics.h"
#include <cmath>
#include <utility>
#include "cstring_mng.h"




BigInteger Naive::multiply(BigInteger const & i1, BigInteger const & i2)
{
	string s1 = i1.get(),
		   s2 = i2.get();
	return BigInteger(to_string(stoi(s1)*stoi(s2)));
	}


template<typename T> T max(T a, T b) {
	return a > b ? a : b;
}


const char* Karatsuba::mult(const char* s1, size_t N, const char* s2, size_t M)
{
	if ((N == M)&&(N%2 == 0)) {
		const char *u1 = cstr::substr(s1, 0, N / 2),
			*u2 = cstr::substr(s1, N / 2, N),
			*v1 = cstr::substr(s2, 0, M / 2),
			*v2 = cstr::substr(s2, M / 2, M);
		return mult(u1, N / 2, v1, N / 2);
	}
}

BigInteger Karatsuba::multiply(BigInteger const& i1, BigInteger const& i2) {
	const char* u = i1.get();
	const char*	v = i2.get();
	size_t N = 0, M = 0;
	while (u[++N]);
	while (v[++M]);

	return BigInteger(mult(u, N, v, M));
}
*/