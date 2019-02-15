//
// Created by 小白白 on 2019-02-15.
//

#ifndef EXPCALC_ICONSTANT_H
#define EXPCALC_ICONSTANT_H

#include "IExpression.h"
#include <tuple>

template<class T>
class TConstant;

namespace detail
{
	template<class T>
	class IBaseConstantVisitorInterfaceGenerator;
	template<template<class...> class List, class First, class...TypesToMake>
	class IBaseConstantVisitorInterfaceGenerator<List<First, TypesToMake...>> : public IBaseConstantVisitorInterfaceGenerator<List<TypesToMake...>>
	{
	public:
		using IBaseConstantVisitorInterfaceGenerator<List<TypesToMake...>>::rightEqualsTo;
		virtual bool rightEqualsTo(const TConstant<First> &lhs) const = 0;
	};
	template<template<class...> class List, class First>
	class IBaseConstantVisitorInterfaceGenerator<List<First>>
	{
	public:
		virtual bool rightEqualsTo(const TConstant<First> &lhs) const = 0;
	};
}

using ConstantTypeList = std::tuple<int, long, long long, unsigned long, unsigned long long, float, double, long double>;
using IBaseConstantVisitorInterface = detail::IBaseConstantVisitorInterfaceGenerator<ConstantTypeList>;

class IConstant : public IExpression, private IBaseConstantVisitorInterface
{
public:
	virtual bool isZero() const = 0;
	virtual bool isOne() const = 0;

	// double dispatch visitor
	virtual bool equalsTo(const IConstant &rhs) const = 0;

public:
	// already bound lhs' type
	using IBaseConstantVisitorInterface::rightEqualsTo;
//	virtual bool rightEqualsTo(const TConstant<int> &lhs) const = 0;
//	virtual bool rightEqualsTo(const TConstant<long> &lhs) const = 0;
//	virtual bool rightEqualsTo(const TConstant<long long> &lhs) const = 0;
//	virtual bool rightEqualsTo(const TConstant<unsigned long> &lhs) const = 0;
//	virtual bool rightEqualsTo(const TConstant<unsigned long long> &lhs) const = 0;
//	virtual bool rightEqualsTo(const TConstant<float> &lhs) const = 0;
//	virtual bool rightEqualsTo(const TConstant<double> &lhs) const = 0;
//	virtual bool rightEqualsTo(const TConstant<long double> &lhs) const = 0;
};


inline bool operator==(const IConstant&lhs, const IConstant &rhs)
{
	return lhs.equalsTo(rhs);
}

#endif //EXPCALC_ICONSTANT_H
