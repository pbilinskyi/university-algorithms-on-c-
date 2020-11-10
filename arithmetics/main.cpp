//source/repos/"3d Term"/arithmetics
#include <iostream>
#include "stdio.h"
#include "cstring_mng.h"
#include "BigInteger.h"
#include "Karatsuba.h"
#include "ToomCook.h"
#include "PrimalityTest.h"
#include "DivisionAlg.h"

using namespace std;

void printArr(BigInteger* a, size_t N) {
	for (int i = 0; i < N; ++i) {
		cout << cstr::binToDec(a[i].get()) << " ";
	}
}


void testKaratsuba() {
	Karatsuba kara;
	
	//411
	BigInteger i1("1101100110111000110001010100110101");
	//478
	BigInteger i2("011110111");
	//i1 * i2 = 196458 | 10101101111111101 

	cout << cstr::binToDec(i1.get()) << " * " << cstr::binToDec(i2.get()) <<  endl;
	cout << kara.multiply(i1, i2).get() << endl;
}

void testToomCooke(){
	//U == 1234
	//V == 4321
	BigInteger U("01001011001"),
		V("101001001001");
	cout << "U = " << U << endl;
	cout << "V = " << V << endl;
	
	int r = 2, q = 4;
	cout << "Split by " << r + 1 << "parts:" << endl;


	//segmentation - split into r + 1 parts with q bits 
	//order: U_r, U_r-1, ... , U_0
	BigInteger *U_segm = new BigInteger[r + 1],
		*V_segm = new BigInteger[r + 1];

	for (int i = r; i >= 0; --i) {
		U_segm[r - i] = cstr::substrUnlim(U.get(), i*q, q);
		V_segm[r - i] = cstr::substrUnlim(V.get(), i*q, q);
	}

	cout << endl << "U(t) = ";
	printArr(U_segm, r + 1);
	cout << endl << "V(t) = ";
	printArr(V_segm, r + 1);
	cout << endl;

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
	cout << "W(0), W(1), ..., W(" << 2 * r << ") = ";
	printArr(W, deg_W + 1);
	cout << endl;
	// find all a
	j = "1";
	for (size_t i = 1; i <= deg_W; ++i) {
		for (size_t t = deg_W; t >= i; --t) {
			W[t] = (W[t] - W[t - 1]) / j;
		}
		++j;
	}
	cout << "a = ";
	printArr(W, deg_W + 1);
	cout << endl;

	//find all W_j
	--(--j);
	for (size_t i = deg_W - 1; i >= 1; --i) {
		for (size_t t = i; t <= deg_W - 1; ++t) {
			W[t] = W[t] - (W[t + 1] * j);
		}
		--j;
	}
	cout << "W(t) = ";
	printArr(W, deg_W + 1);
	cout << endl;

	//W = U*V, shift and addition of segments
	BigInteger Res("0");
	for (int i = 0; i <= deg_W; ++i) {
		Res = Res + (W[i] >> i * q);
	}

	cout << endl << cstr::binToDec(Res.get()) << endl;
}

int main(){
	// read from left -> to right
	// (10011) = 1 * 2^0 +
	//			 0 * 2^1 + 
	//           0 * 2^2 + 
	//			 1 * 2^3 + 
	//			 1 * 2^4 

	
	//testKaratsuba();
	//testToomCooke();
	BigInteger i1("0101"), i2("011");
	cout << i1 * i2;
	system("pause");
	return 0;
}