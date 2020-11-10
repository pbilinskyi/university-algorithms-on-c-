#include "DivisionAlg.h"
#include "cstring_mng.h"
#include <iostream>

std::pair<BigInteger, BigInteger> DivisionAlg::div(const BigInteger &D, const BigInteger &d) const
{
	BigInteger k("0"), temp_D = D;
	while (temp_D >= d) {
		temp_D = temp_D - d;
		++k;
	}
	return { k, temp_D };
}

/*std::pair<BigInteger, BigInteger> DivisionAlg::divColumn(const BigInteger& D, const BigInteger& d) const {


	if (D < d) return { BigInteger("0"), D };

	size_t N1 = cstr::length(D.get()),
		N2 = cstr::length(d.get());

	int pos = N1 - N2;
	BigInteger res = "";
	BigInteger term_D = (D << pos);
	while (pos > 0) {

		while ((term_D < d) && (pos > 0)) {
			term_D.concatFront(D[--pos]);
			res.concatFront('0');
		}

		if (pos > 0) {
			term_D = term_D - d;
			res.concatFront('1');
			if (std::strcmp(term_D.get(), "0") == 0) {
				term_D = "";
				while (pos > 0 && D[pos - 1] == '0'){
					res.concatFront('0');
					--pos;
				}
			}
			if (pos > 0) term_D.concatFront(D[--pos]);

			
		}
	}
	if (term_D >= d) {
		term_D = term_D - d;
		res.concatFront('1');
	}
	else res.concatFront('0');
	if (std::strcmp(term_D.get(), "") == 0) term_D = "0";

	return { res , term_D };
}
*/