//
// Created by 小白白 on 2019-02-15.
//

#ifndef EXPCALC_UNARYOPERATOR_H
#define EXPCALC_UNARYOPERATOR_H

#include "IOperator.h"

namespace detail
{
	template<char Name>
	class TForwardUnaryOperator : public IUnaryOperator
	{
	public:
		using IUnaryOperator::IUnaryOperator;
		std::string toString() const override
		{
			return std::string{'(', Name} + _1->toString() + ')';
		}
	};
	template<char Name>
	class TBackwardUnaryOperator : public IUnaryOperator
	{
	public:
		using IUnaryOperator::IUnaryOperator;
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

#endif //EXPCALC_UNARYOPERATOR_H
