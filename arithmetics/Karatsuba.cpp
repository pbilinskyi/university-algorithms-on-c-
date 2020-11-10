#include "Karatsuba.h"
#include "BigInteger.h"
#include "cstring_mng.h"


BigInteger Karatsuba::multiply(const BigInteger & U, const BigInteger & V) {
	int N = cstr::length(U.get());
	int M = cstr::length(V.get());

	if (N == M) {
		if (N == 1) {
			return (U == V) ? U : BigInteger("0");
		}

		size_t n = N - N / 2;
		BigInteger U1 = U << n,
			U0 = BigInteger(cstr::substr(U.get(), 0, n)),
			V1 = V << n,
			V0 = BigInteger(cstr::substr(V.get(), 0, n));

		BigInteger C0 = U0 * V0,
			C1 = U1 * V1,
			C2 = U1 * V0 + V1 * U0;

		BigInteger temp1 = (C1 >> (2 * n)),
			temp2 = C2 >> n,
			temp3 = temp1 + temp2,
			temp4 = temp3 + C0;

		return temp4;
	}
	else if (M > N) {
		BigInteger V1 = V << N,
			V0 = BigInteger(cstr::substr(V.get(), 0, N));

		return ((V1*U) >> N) + (V0*U);
	}

	else if (N > M){
		BigInteger U1 = U << M,
			U0 = BigInteger(cstr::substr(U.get(), 0, M));

		return ((U1*V) >> M) + (U0*V);
	}
}
