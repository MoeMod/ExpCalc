#include <iostream>
#include <iterator>
#include <algorithm>

#include "ExpCalc/ExpCalc.h"

int main() {
	std::transform(
			std::istream_iterator<std::string>(std::cin),
			std::istream_iterator<std::string>(),
			std::ostream_iterator<std::string>(std::cout, "\n"),
			buildExpressionStringSimplified
	);
	return 0;
}