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
};

class OptMinus : public detail::TBinaryOperator<'-', false, false>
{
public:
	using TBinaryOperator::TBinaryOperator;
};

class OptMultiply : public detail::TBinaryOperator<'*', true, true>
{
public:
	using TBinaryOperator::TBinaryOperator;
};

class OptDivide : public detail::TBinaryOperator<'/', false, false>
{
public:
	using TBinaryOperator::TBinaryOperator;
};

#endif //EXPCALC_BINARYOPERATOR_H
