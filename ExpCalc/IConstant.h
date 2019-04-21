//
// Created by 小白白 on 2019-02-15.
//

#ifndef EXPCALC_ICONSTANT_H
#define EXPCALC_ICONSTANT_H

#include "IExpression.h"
#include <tuple>

template<class T>
class TConstant;

class IConstant;

namespace detail
{
	template<class T>
	class IBaseConstantVisitorInterfaceGenerator;
	template<template<class...> class List, class First>
	class IBaseConstantVisitorInterfaceGenerator<List<First>>
	{
	public:
		virtual bool rightEqualsTo(const TConstant<First> &lhs) const = 0;
		virtual std::shared_ptr<IConstant> rightAdd(const TConstant<First> &lhs) const = 0;
		virtual std::shared_ptr<IConstant> rightMultiply(const TConstant<First> &lhs) const = 0;
	};
	template<template<class...> class List, class...TypesToMake>
	class IBaseConstantVisitorInterfaceGenerator<List<TypesToMake...>> : private IBaseConstantVisitorInterfaceGenerator<List<TypesToMake>>...
	{
	public:
		using IBaseConstantVisitorInterfaceGenerator<List<TypesToMake>>::rightEqualsTo...;
		using IBaseConstantVisitorInterfaceGenerator<List<TypesToMake>>::rightAdd...;
		using IBaseConstantVisitorInterfaceGenerator<List<TypesToMake>>::rightMultiply...;
	};
}

using ConstantTypeList = std::tuple<int, long, long long, float, double, long double>;
using IBaseConstantVisitorInterface = detail::IBaseConstantVisitorInterfaceGenerator<ConstantTypeList>;

class IConstant : public IExpression, private IBaseConstantVisitorInterface
{
public:
	virtual bool isZero() const = 0;
	virtual bool isOne() const = 0;

	// double dispatch visitor
	virtual bool equalsTo(const IConstant &rhs) const = 0;
	virtual std::shared_ptr<IConstant> add(const IConstant &rhs) const = 0;
	virtual std::shared_ptr<IConstant> multiply(const IConstant &rhs) const = 0;

	virtual std::shared_ptr<IConstant> invert() const = 0;

	// first * sqrt(second)
	virtual std::pair<std::shared_ptr<IExpression>, std::shared_ptr<IExpression>> sqrt() = 0;

private:
	JudgeResult equalsTo(std::shared_ptr<IExpression> other) override
	{
		auto pCon = std::dynamic_pointer_cast<IConstant>(other);
		return pCon ? (pCon->equalsTo(*this) ? JR_YES : JR_NO) : JR_UNKNOWN;
	}

public:
	// already bound lhs' type
	using IBaseConstantVisitorInterface::rightEqualsTo;
	using IBaseConstantVisitorInterface::rightAdd;
	using IBaseConstantVisitorInterface::rightMultiply;
};


inline bool operator==(const IConstant&lhs, const IConstant &rhs)
{
	return lhs.equalsTo(rhs);
}

#endif //EXPCALC_ICONSTANT_H
