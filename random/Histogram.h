#pragma once

class Histogram{
public:
	Histogram();
	void reset() noexcept;
	void add(double d) noexcept;
	void show() const noexcept;
private:
	static const size_t SECTORS = 10;
	size_t numbers = 0;
	int arr[SECTORS];
};