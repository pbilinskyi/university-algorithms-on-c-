#pragma once
#include "iostream"

namespace metaprog {
	//static idintificator requires initialization at compile time
	//initialization of result requires instantiating ctime_power<X, Y-1> each time
	//when recursion reaches the end, copliler matches partial specialized template ctime_power<X, 0> below 
	template <int X, int Y>
	struct ctime_power {
		static const int result = X * ctime_power<X, Y - 1>::result;
	};

	//partial specialization
	template <int X>
	struct ctime_power<X, 0> {
		static const int result = 1;
	};

	const int d = ctime_power<2, 5>::result;
//=======================================================
template<int N>
struct factorial {
	static const int result = N * factorial<N-1>::result;
};

template <> 
struct factorial <1>{
	static const int result = 1;
};

//======================================================

template <bool B>
struct If {};

template<> 
struct If<true> {
	static inline void f() {
		std::cout << "TRUE" << std::endl;
	}
};

template<>
struct If<false> {
	static inline void f() {
		std::cout << "False" << std::endl;
	}
};

//==============================================

void f() {
	std::cout << "f called" << std::endl;
}

template <int I>
struct Iteration{
private:
	enum { go = (I - 1) != 0 };
public:
	static inline void perform() {
		f();
		Iteration <go : I-1 ? 0>::perform();
	}
};

template<> 
struct Iteration<0> {
	static inline void f() {

	}
};



}

