//
// Created by 小白白 on 2019-04-22.
//

#ifndef EXPCALC_ZERO_H
#define EXPCALC_ZERO_H

#include "IConstant.h"

namespace detail
{
	template<class T, class Final>
	class CZeroConstantVisitorGenerator;
	template<template<class...> class List, class First, class...TypesToMake, class Final>
	class CZeroConstantVisitorGenerator<List<First, TypesToMake...>, Final> : public CZeroConstantVisitorGenerator<List<TypesToMake...>, Final>
	{
	public:
		// CRTP Generator
		// known *this, unknown rhs
		bool equalsTo(const IConstant &rhs) const override { return rhs.isZero(); }
		std::shared_ptr<IConstant> add(const IConstant &rhs) const override
		{
			return std::const_pointer_cast<IConstant>(std::static_pointer_cast<const IConstant>(rhs.shared_from_this()));
		}
		std::shared_ptr<IConstant> multiply(const IConstant &rhs) const override
		{
			return std::const_pointer_cast<IConstant>(std::static_pointer_cast<const IConstant>(IExpression::shared_from_this()));
		}
		// static dispatch
		bool rightEqualsTo(const TConstant<First> &lhs) const override
		{
			return lhs.isZero();
		}
		std::shared_ptr<IConstant> rightAdd(const TConstant<First> &lhs) const override
		{
			return std::const_pointer_cast<IConstant>(std::static_pointer_cast<const IConstant>(IExpression::shared_from_this()));
		}
		std::shared_ptr<IConstant> rightMultiply(const TConstant<First> &lhs) const override
		{
			return std::const_pointer_cast<IConstant>(std::static_pointer_cast<const IConstant>(IExpression::shared_from_this()));
		}
	};
	template<template<class...> class List, class Final>
	class CZeroConstantVisitorGenerator<List<>, Final> : public IConstant {};
}

class ZeroConstant : public detail::CZeroConstantVisitorGenerator<ConstantTypeList, ZeroConstant>
{
public:
	bool isZero() const override { return true; }
	bool isOne() const override { return false; }

	// double dispatch visitor
	std::string toString() const override { return "0"; }
	std::shared_ptr<IExpression> simplify() override { return IExpression::shared_from_this(); }
	std::shared_ptr<IConstant> invert() const override { return std::const_pointer_cast<IConstant>(std::static_pointer_cast<const IConstant>(IExpression::shared_from_this())); }

	// first * sqrt(second)
	std::pair<std::shared_ptr<IExpression>, std::shared_ptr<IExpression>> sqrt() override
	{
		return std::make_pair<std::shared_ptr<IExpression>, std::shared_ptr<IExpression>>(
				shared_from_this(),
				shared_from_this()
		);
	}

public:
	int get()
	{
		return 0;
	}
};

#endif //EXPCALC_ZERO_H
