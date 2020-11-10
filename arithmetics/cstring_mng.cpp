#include "cstring_mng.h"
#include <stdexcept>
#include <string>
#include <charconv>
#include <cstring>
#include <cmath>

char* cstr::substrUnlim(const char* c, size_t pos, size_t length) {
	size_t N = 0;
	while (c[N]) ++N;

	char* sub = nullptr;


	if (N < pos) {
		sub = new char[2]{'0', '\0'};
	}
	else {
		size_t i = 0;
		sub = new char[(length <= N - pos) ? (length + 1): (N - pos + 1)];
		for (; (i < N - pos)&&(i < length); ++i)	sub[i] = c[pos + i];
		
		sub[i] = '\0';
	}

	return sub;
}

char* cstr::substr(const char* c, size_t pos, size_t length) {
	size_t N = 0;
	while (c[N]) ++N;

	if (N < pos + length) throw std::invalid_argument("substr: index out of array");
	char* sub = new char[length + 1];

	for (size_t i = 0; (i < length); ++i)	sub[i] = c[pos + i];

	sub[length] = '\0';
	return sub;
}

char* cstr::substr(const char* c, size_t pos) {
	size_t N = 0;
	while (c[N]) ++N;

	if (N < pos) throw std::invalid_argument("substr: index out of array");

	size_t length = N - pos;
	char* sub = new char[length];
	for (size_t i = 0; (i < length); ++i)	sub[i] = c[pos + i];

	sub[length] = '\0';
	return sub;
}

char* cstr::merge(const char* c1, const char* c2) {
	size_t N1 = 0, N2 = 0;
	while (c1[++N1]);
	while (c2[++N2]);

	size_t N = N1 + N2;
	char* c = new char[N + 1];
	size_t i = 0;
	for (; i < N1; ++i) c[i] = c1[i];
	for (; i < N; ++i) c[i] = c2[i - N1];

	c[N] = '\0';
	return c;
}

char* cstr::right_shift(const char* c, size_t pos) {
	size_t N = 0;
	while (c[++N]);

	size_t N_new = pos + N;
	char* c_new = new char[N_new + 1];
	size_t i = 0;
	while (i < pos) {
		c_new[i] = '0';
		++i;
	}
	while (i < N_new) {
		c_new[i] = c[i - pos];
		++i;
	}

	c_new[N_new] = '\0';
	return c_new;
}

char* cstr::left_shift(const char* c, size_t pos) {
	size_t N = 0;
	while (c[++N]);

	if (N < pos) {
		char* c_res = new char[1];
		c_res[0] = '\0';
		return c_res;
	}
	else {
		return cstr::substr(c, pos);
	}
}

char* cstr::add(const char* c1, const char* c2) {
	size_t N1 = 0, N2 = 0;
	while (c1[++N1]);
	while (c2[++N2]);

	size_t maxN = N1 > N2 ? N1 : N2;

	//1 for carryover, 1 for '\0' 
	char* c = new char[maxN + 1 + 1];

	bool carry = false;
	size_t i = 0;
	while (*c1 && *c2) {
		if (carry) {
			if ((*c1 == '0') && (*c2 == '0')) {
				c[i] = '1';
				carry = 0;
			}
			else if ((*c1 == '1') && (*c2 == '1')) {
				c[i] = '1';
			}
			else {
				c[i] = '0';
			}
		}
		else {
			if ((*c1 == '0') && (*c2 == '0')) {
				c[i] = '0';
			}
			else if ((*c1 == '1') && (*c2 == '1')) {
				c[i] = '0';
				carry = 1;
			}
			else {
				c[i] = '1';
			}
		}
		++c1;
		++c2;
		++i;
	}

	if (*c1) {
		while (*c1) {
			if (carry) {
				c[i] = (*c1 == '1') ? '0' : '1';
				carry = (*c1 == '1');
			}
			else {
				c[i] = *c1;
			}
			++c1;
			++i;
		}
	}
	if (*c2) {
		while (*c2) {
			if (carry) {
				c[i] = (*c2 == '1') ? '0' : '1';
				carry = (*c2 == '1');
			}
			else {
				c[i] = *c2;
			}
			++c2;
			++i;
		}
	}

	if (carry) c[i++] = '1';

	c[i] = '\0';
	return c;
}

//returns abs(c1 - c2)
char * cstr::subtract(const char * c1, const char * c2)
{
	size_t N1 = 0, N2 = 0;
	while (c1[++N1]);
	while (c2[++N2]);

	int comp = compare(c1, c2, N1, N2);
	if (comp == 0) return new char[2]{ '0', 0 };
	if (comp < 0) {
		const char* t = c2;
		c2 = c1;
		c1 = t;
	}

	//1 for carryover, 1 for '\0' 
	char* c = new char[N1 + 1];

	bool carry = false;
	size_t i = 0;
	while (*c1 && *c2) {
		if (carry) {
			if ((*c1 == '1') && (*c2 == '0')) {
				c[i] = '0';
				carry = 0;
			}
			else if ((*c1 == '0') && (*c2 == '1')) {
				c[i] = '0';
			}
			else  {
				c[i] = '1';
			}
		}
		else {
			if ((*c1 == '1') && (*c2 == '0')) {
				c[i] = '1';
			}
			else  if ((*c1 == '0') && (*c2 == '1') ){
				c[i] = '1';
				carry = 1;
			}
			else {
				c[i] = '0';
			}
		}
		++c1;
		++c2;
		++i;
	}

	while (*c1) {
		if (carry) {
			c[i] = (*c1 == '1') ? '0' : '1';
			carry = (*c1 == '0');
		}
		else {
			c[i] = *c1;
		}
		++c1;
		++i;
	}

	c[i] = '\0';
	return trim(c);
}


int cstr::compare(const char* s1, const char* s2, size_t N1, size_t N2) {

	if (N1 != N2) return N1 > N2 ? 1 : -1;

	int res = 0;

	for (int i = N1 - 1; !res && (i >= 0); --i) {
		if (s1[i] > s2[i]) res = 1;
		else if (s2[i] > s1[i]) res = -1;
	}

	return res;
}

int cstr::compare(const char* s1, const char* s2) {
	size_t N1 = cstr::length(s1), N2 = cstr::length(s2);

	if (N1 != N2) return N1 > N2 ? 1 : -1;

	int res = 0;

	for (int i = N1 - 1; !res && (i >= 0); --i) {
		if (s1[i] > s2[i]) res = 1;
		else if (s2[i] > s1[i]) res = -1;
	}

	return res;
}

char * cstr::trim(const char* s) {
	const char* c = strrchr(s, '1');
	//001101000
	//N_s == 9,  N_c = 4

	if (c) {
		size_t N = length(s) - length(c) + 1;
		return substr(s, 0, N);
	}
	else return new char[2]{'0', 0};
}

char* cstr::invert(const char* c) {
	size_t N = 0;
	while (c[N]) ++N;

	char* c_inv = new char[N + 1];
	for (size_t i = 0; i < N; ++i) {
		c_inv[i] = c[N - i - 1];
	}
	c_inv[N] = '\0';
	return c_inv;
}

int cstr::binToDec(const char* s_bin) {
	size_t N = length(s_bin);
	int sum = 0;
	for (int i = 0; i < N; ++i) {
		if (s_bin[i] == '1') sum += static_cast<int>(pow(2, i));
	}
	return sum;
}
//pre: do not pass negative n
const char * cstr::decToBin(int n)
{
	size_t length = static_cast<int>(floor(log2(n))) + 1;
	char* a = new char[length + 1];
	for (int i = 0; i < length; ++i) {
		a[i] = (n % 2 == 0) ? '0' : '1';
		n /= 2;
	}
	a[length] = '\0';
	return a;
}

size_t cstr::length(const char* c) {
	size_t N = 0;
	while (c[N]) ++N;
	return N;
}