#include <iostream>

#include "ExpCalc/ExpCalc.h"

int main() {
	std::transform(
			std::istream_iterator<std::string>(std::cin),
			std::istream_iterator<std::string>(),
			std::ostream_iterator<std::string>(std::cout, "\n"),
			buildExpressionString
	);
	return 0;
}