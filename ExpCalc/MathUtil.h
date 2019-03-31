//
// Created by 小白白 on 2019-03-31.
//

#ifndef EXPCALC_MATHUTIL_H
#define EXPCALC_MATHUTIL_H

namespace MathUtil
{
	template<class T>
	constexpr auto gcd(T a, T b) -> typename std::enable_if<std::is_integral<T>::value, T>::type
	{
		return (b > 0) ? gcd(a, a % b) : a;
	}

	template<class T>
	auto gcd(T a, T b) -> decltype(T::gcd(a, b))
	{
		return T::gcd(a, b);
	}
}

#endif //EXPCALC_MATHUTIL_H
