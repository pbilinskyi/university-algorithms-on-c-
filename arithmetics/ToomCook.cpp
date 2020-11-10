#include <iostream>
#include <list>
#include "cstring_mng.h"
#include "ToomCook.h"
#include "Karatsuba.h"
using namespace std;

BigInteger ToomCook::mult(const BigInteger & U, const BigInteger& V, size_t N)
{

	int k = 1,
		q1 = 16, q0 = q1,
		r1 = 4, r0 = r1,
		Q = 4, R = 2;

	while (q0 + q1 < N) {
		++k;
		Q += R;
		R = (R + 1)*(R + 1) <= Q ? R + 1 : R;
		q0 = q1; r0 = r1;
		q1 = pow(2, Q);
		r1 = pow(2, R);
		cout << " qk = " << q1 << " rk = " << r1 << endl;
	}

	--k;
	if (k == 0) {
		Karatsuba kara;
		return kara.multiply(U, V);
	}

	int r = r1, q = q1;
	//segmentation - split into r + 1 parts with q bits 
	//order: U_r, U_r-1, ... , U_0
	BigInteger *U_segm = new BigInteger[r + 1],
		*V_segm = new BigInteger[r + 1];

	for (int i = r; i >= 0; --i) {
		U_segm[r - i] = cstr::substrUnlim(U.get(), i*q, q);
		V_segm[r - i] = cstr::substrUnlim(V.get(), i*q, q);
	}

	//order in Wj: W_0, W_1, ..., W_2r
	size_t deg_W = 2 * r;
	BigInteger* W = new BigInteger[deg_W + 1];
	BigInteger j("0"), U_j, V_j;

	for (size_t i = 0; i <= deg_W; ++i) {
		U_j = "0";
		V_j = "0";
		for (size_t k = 0; k <= r; ++k) {
			U_j = (U_j * j) + U_segm[k];
			V_j = (V_j * j) + V_segm[k];
		}
		W[i] = U_j * V_j;
		++j;
	}

	// find all a
	j = "1";
	for (size_t i = 1; i <= deg_W; ++i) {
		for (size_t t = deg_W; t >= i; --t) {
			W[t] = (W[t] - W[t - 1]) / j;
		}
		++j;
	}

	//find all W_j
	--(--j);
	for (size_t i = deg_W - 1; i >= 1; --i) {
		for (size_t t = i; t <= deg_W - 1; ++t) {
			W[t] = W[t] - (W[t + 1] * j);
		}
		--j;
	}
	//W = U*V, shift and addition of segments
	BigInteger Res("0");
	for (int i = 0; i <= deg_W; ++i) {
		Res = Res + (W[i] >> i * q);
	}
	return Res;

}

BigInteger ToomCook::multiply(const BigInteger& i1, const BigInteger &i2) {
	size_t N1 = cstr::length(i1.get()),
		N2 = cstr::length(i2.get());
	size_t N = N1 > N2 ? N1 : N2;
	return mult(i1, i2, N);
}

