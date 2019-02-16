//
// Created by 小白白 on 2019-02-15.
//

#ifndef EXPCALC_BINARYOPERATOR_H
#define EXPCALC_BINARYOPERATOR_H

#include "IOperator.h"

namespace detail
{
	template<char Name, bool bAssociativeProperty, bool bCommutativeProperty>
	class TBinaryOperator : public IBinaryOperator
	{
	public:
		using IBinaryOperator::IBinaryOperator;
		std::string toString() const override
		{
			return '(' + _1->toString() + Name + _2->toString() + ')';
		}
		bool hasAssociativeProperty() const override { return bAssociativeProperty; }
		bool hasCommutativeProperty() const override { return bCommutativeProperty; }
	};
}

class OptPlus : public detail::TBinaryOperator<'+', true, true>
{
public:
	using TBinaryOperator::TBinaryOperator;
	std::shared_ptr<IExpression> simplify() override;
	std::shared_ptr<IBinaryOperator> clone(std::shared_ptr<IExpression> a, std::shared_ptr<IExpression> b) const override
	{
		return std::make_shared<OptPlus>(std::move(a), std::move(b));
	}
};

class OptMinus : public detail::TBinaryOperator<'-', false, false>
{
public:
	using TBinaryOperator::TBinaryOperator;
	std::shared_ptr<IExpression> simplify() override;
	std::shared_ptr<IBinaryOperator> clone(std::shared_ptr<IExpression> a, std::shared_ptr<IExpression> b) const override
	{
		return std::make_shared<OptMinus>(std::move(a), std::move(b));
	}
};

class OptMultiply : public detail::TBinaryOperator<'*', true, true>
{
public:
	using TBinaryOperator::TBinaryOperator;
	std::shared_ptr<IExpression> simplify() override;
	std::shared_ptr<IBinaryOperator> clone(std::shared_ptr<IExpression> a, std::shared_ptr<IExpression> b) const override
	{
		return std::make_shared<OptMultiply>(std::move(a), std::move(b));
	}
};

class OptDivide : public detail::TBinaryOperator<'/', false, false>
{
public:
	using TBinaryOperator::TBinaryOperator;
	std::shared_ptr<IExpression> simplify() override
	{
		return IExpression::shared_from_this();
	}
	std::shared_ptr<IBinaryOperator> clone(std::shared_ptr<IExpression> a, std::shared_ptr<IExpression> b) const override
	{
		return std::make_shared<OptDivide>(std::move(a), std::move(b));
	}
};

#endif //EXPCALC_BINARYOPERATOR_H
