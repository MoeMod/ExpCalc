//
// Created by 小白白 on 2019-02-15.
//

#ifndef EXPCALC_UNARYOPERATOR_H
#define EXPCALC_UNARYOPERATOR_H

#include "IOperator.h"

class UnaryOperator : public IUnaryOperator
{
public:
	explicit UnaryOperator(std::shared_ptr<IExpression> a) noexcept : _1(std::move(a)) {}

public:
	std::shared_ptr<IExpression> getBoundArgPtr() const override { return _1; }
	std::shared_ptr<IExpression> simplify() override;

public:
	const std::shared_ptr<IExpression> _1;
};

namespace detail
{
	template<char Name>
	class TForwardUnaryOperator : public UnaryOperator
	{
	public:
		using UnaryOperator::UnaryOperator;
		std::string toString() const override
		{
			return std::string{'(', Name} + _1->toString() + ')';
		}
	};
	template<char Name>
	class TBackwardUnaryOperator : public UnaryOperator
	{
	public:
		using UnaryOperator::UnaryOperator;
		std::string toString() const override
		{
			return '(' + _1->toString() + std::string{ Name, ')' };
		}
	};
}

class OptReverseNumber : public detail::TForwardUnaryOperator<'-'>
{
public:
	using TForwardUnaryOperator::TForwardUnaryOperator;
	std::shared_ptr<IExpression> simplify() override;
	std::shared_ptr<IUnaryOperator> clone(std::shared_ptr<IExpression> a) const override
	{
		return std::make_shared<OptReverseNumber>(std::move(a));
	}
};

class OptSqrt : public UnaryOperator
{
public:
	using UnaryOperator::UnaryOperator;
	std::shared_ptr<IExpression> simplify() override;
	std::string toString() const override
	{
		return "sqrt(" + _1->toString() + ')';
	}
	std::shared_ptr<IUnaryOperator> clone(std::shared_ptr<IExpression> a) const override
	{
		return std::make_shared<OptSqrt>(std::move(a));
	}
};

#endif //EXPCALC_UNARYOPERATOR_H
