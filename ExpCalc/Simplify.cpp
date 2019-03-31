//
// Created by 小白白 on 2019-02-16.
//

#include "Constant.h"
#include "UnaryOperator.h"
#include "BinaryOperator.h"
#include <mutex>

#include "MathUtil.h"

std::shared_ptr<IExpression> UnaryOperator::simplify()
{
	if(auto sp = _1->simplify(); sp != _1)
		return clone(sp)->simplify();

	return IOperator::simplify();
}

std::shared_ptr<IExpression> OptReverseNumber::simplify()
{
	// -(-x) = x
	if(auto sp = std::dynamic_pointer_cast<OptReverseNumber>(_1))
		return sp->_1->simplify();

	// -C => C'
	if(auto sp = std::dynamic_pointer_cast<IConstant>(_1))
		return sp->invert();

	// -(a+b) = (-a) + (-b)
	if(auto sp = std::dynamic_pointer_cast<OptPlus>(_1))
		return std::make_shared<OptPlus>(
				std::make_shared<OptReverseNumber>(sp->_1),
				std::make_shared<OptReverseNumber>(sp->_2)
		)->simplify();

	return UnaryOperator::simplify();
}

std::shared_ptr<IExpression> BinaryOperator::simplify()
{
	// A*B => A' * B
	if(auto sp = _1->simplify(); sp != _1)
		return clone(sp, _2)->simplify();

	// A+B => A + B'
	if(auto sp = _2->simplify(); sp != _2)
		return clone(_1, sp)->simplify();

	if(hasCommutativeProperty())
	{
		// A*B => B * A (try)
		if(auto sp = clone(_2, _1))
		{
			// anti infinity loop
			if(static thread_local std::mutex m; m.try_lock())
			{
				std::lock_guard<std::mutex> l(m, std::adopt_lock);
				if(auto sp_simplified = sp->simplify(); sp_simplified != sp)
					return sp_simplified->simplify();
			}
		}
	}

	return IOperator::simplify();
}

std::shared_ptr<IExpression> OptPlus::simplify()
{
	// A+0 = A
	if(auto sp = std::dynamic_pointer_cast<IConstant>(_2); sp && sp->isZero())
		return _1->simplify();

	// C1 + C2 => C3
	if(auto c1 = std::dynamic_pointer_cast<IConstant>(_1), c2  = std::dynamic_pointer_cast<IConstant>(_2); c1 && c2)
		return c1->add(*c2)->simplify();

	// A+(C*A) -> (C+1)*A
	if(auto sp = std::dynamic_pointer_cast<OptMultiply>(_2))
	{
		if(auto c = std::dynamic_pointer_cast<IConstant>(sp->_1))
		{
			// TODO
		}

	}

	return BinaryOperator::simplify();
}

std::shared_ptr<IExpression> OptMinus::simplify()
{
	// (A-B) => A + (-B)
	return std::make_shared<OptPlus>(_1, std::make_shared<OptReverseNumber>(_2))->simplify();
}

std::shared_ptr<IExpression> OptMultiply::simplify()
{
	// A*0 = A
	if(auto sp = std::dynamic_pointer_cast<IConstant>(_2); sp && sp->isZero())
		return sp;

	// A*1 = A
	if(auto sp = std::dynamic_pointer_cast<IConstant>(_2); sp && sp->isOne())
		return _1->simplify();

	// C1 * C2 => C3
	if(auto c1 = std::dynamic_pointer_cast<IConstant>(_1), c2  = std::dynamic_pointer_cast<IConstant>(_2); c1 && c2)
		return c1->multiply(*c2)->simplify();

	// A*(B+C) -> A*B+A*C
	if(auto sp = std::dynamic_pointer_cast<OptPlus>(_2))
		return sp->clone(this->clone(_1, sp->_1), this->clone(_1, sp->_2))->simplify();

	return BinaryOperator::simplify();
}

std::shared_ptr<IExpression> OptSqrt::simplify()
{
	if(auto sp = std::dynamic_pointer_cast<IConstant>(_1))
	{
		// sqrt0=0, sqrt1=1
		if(sp->isZero() || sp->isOne())
			return _1;

		auto [out, in] = sp->sqrt();
		if(in != sp)
		{
			return std::make_shared<OptMultiply>(
					out,
					std::make_shared<OptSqrt>(in)
			)->simplify();
		}
	}

	return UnaryOperator::simplify();
}
