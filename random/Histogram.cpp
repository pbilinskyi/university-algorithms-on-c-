#include "Histogram.h"
#include <cmath>
#include <iostream>
#include <iomanip>

Histogram::Histogram() {
	reset();
}

void Histogram::add(double d) noexcept{
	if (d == 1) ++arr[9];
	else ++arr[static_cast<int>(floor(d * 10))];
	++numbers;
}

void Histogram::reset() noexcept{
	for (size_t i = 0; i < SECTORS; ++i) arr[i] = 0;
	numbers = 0;
}

void Histogram::show() const noexcept{
	std::cout << std::fixed;
	double low_bound = 0;
	for (size_t i = 0; i < SECTORS; ++i) {
		std::cout << std::setprecision(1) << "[" << low_bound << ", " << low_bound + 0.1 << "]\t";
		std::cout << std::setprecision(2) << static_cast<double>(arr[i])/numbers << std::endl;
		low_bound = low_bound + 0.1;
	}
}