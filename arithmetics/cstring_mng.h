//In all of functions in this file we read the number FROM LEFT TO RIGTH:
//for example, binary 1011 stands for decimal 13
//Our left and right shift act the same way.

#pragma once

namespace cstr {

	char* substr(const char* c, size_t pos, size_t length);

	char* substr(const char* c, size_t pos);

	char* substrUnlim(const char* c, size_t pos, size_t length);

	char* merge(const char* c1, const char* c2);

	char* left_shift(const char*, size_t);

	char* right_shift(const char*, size_t);

	//arithmetical operations with binary strings
	char* add(const char* c1, const char* c2);

	char* subtract(const char* c1, const char* c2);
	
	int compare(const char*, const char*, size_t, size_t);
	int compare(const char*, const char*);

	char* trim(const char*);

	char* invert(const char* c);

	int binToDec(const char* c_bin);

	const char* decToBin(int n);

	size_t length(const char* c);
}