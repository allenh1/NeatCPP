#include <iostream>
#include <algorithm>
#include <functional>
#include <typeinfo>

auto generic_lambda = [](auto a, auto && b) { return a < b; };

/**
 * That lambda is kinda boring. We can do better! How about
 * arbitrary numbers of parameters?
 */

auto vglambda = [] (auto printer) {
	/**
	 * What's interesting about this line?
	 * It knows how to print ANYTHING. And, 
	 * additionally, it can print ALL THE THINGS.
	 */
	return [=] (auto && ... ts) {
		printer(std::forward<decltype(ts)>(ts) ...);

		//! This is a nullary lambda. nullary lambdas take no
		//! parameters.
		return [=] { printer(ts ...); }; 
	};
};

/**
 * @brief      This is a lambda expression that prints
 *             and calculates fibonacci numbers.
 *
 * @param[in]  number Number of fibonacci numbers to calculate
 *
 * @return     That's a good question, actually...
 */
auto fib_lambda = [] (unsigned int number) {
	auto f1 = 1u;
	auto f2 = 0u;

	auto fib([&f1, &f2] () mutable -> auto {
		//! why are all of these auto? Because auto is a
		//! shorter word than "unsigned int." ... And it's cool.
		auto temp = f1;
		f1 = f2;
		f2 += temp;
		auto p = vglambda([=](auto f) { std::cout << f2 << std::endl; });
		p(f2);
		return f2;
	});
	for (; number--; ) fib();
	return number;
};

int main (int argc, char ** argv) {
	auto p = vglambda([](auto v1, auto v2, auto v3) { std::cout << v1 << std::endl
																<< v2 << std::endl
																<< v3 << std::endl; });
	auto q = p(1, 'a', 3.14);
	auto r = p("\nI literally broke the compiler!", "I'm a string literal.", "");
	q();
	std::cout<<std::endl;
	auto fib = fib_lambda(40);
	return 0;
}
