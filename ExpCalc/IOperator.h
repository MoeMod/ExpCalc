#include <utility>

//
// Created by 小白白 on 2019-02-15.
//

#ifndef EXPCALC_IOPERATOR_H
#define EXPCALC_IOPERATOR_H

#include "IExpression.h"

#include <memory>

class IOperator : public IExpression
{
public:
	std::shared_ptr<IExpression> simplify() override
	{
		return shared_from_this();
	}
};

class IUnaryOperator : public IOperator
{
public:
	virtual std::shared_ptr<IUnaryOperator> clone(std::shared_ptr<IExpression> a) const = 0;
	virtual std::shared_ptr<IExpression> getBoundArgPtr() const = 0;
};

class IBinaryOperator : public IOperator
{
public:
	virtual bool hasAssociativeProperty() const = 0;
	virtual bool hasCommutativeProperty() const = 0;
	virtual std::shared_ptr<IExpression> getBoundLeftArgPtr() const = 0;
	virtual std::shared_ptr<IExpression> getBoundRightArgPtr() const = 0;
	virtual std::shared_ptr<IBinaryOperator> clone(std::shared_ptr<IExpression> a, std::shared_ptr<IExpression> b) const = 0;
};

#endif //EXPCALC_IOPERATOR_H
