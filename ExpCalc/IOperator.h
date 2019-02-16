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
	explicit IUnaryOperator(std::shared_ptr<IExpression> a) noexcept : _1(std::move(a)) {}

public:
	const std::shared_ptr<IExpression> &getBoundArgPtr() const { return _1; }

	virtual std::shared_ptr<IUnaryOperator> clone(std::shared_ptr<IExpression> a) const = 0;
	std::shared_ptr<IExpression> simplify() override;

public:
	const std::shared_ptr<IExpression> _1;
};

class IBinaryOperator : public IOperator
{
public:
	IBinaryOperator(std::shared_ptr<IExpression> a, std::shared_ptr<IExpression> b) noexcept : _1(std::move(a)), _2(std::move(b)) {}

public:
	const std::shared_ptr<IExpression> &getBoundLeftArgPtr() const noexcept { return _1; }
	const std::shared_ptr<IExpression> &getBoundRightArgPtr() const noexcept { return _2; }

	virtual bool hasAssociativeProperty() const = 0;
	virtual bool hasCommutativeProperty() const = 0;

	virtual std::shared_ptr<IBinaryOperator> clone(std::shared_ptr<IExpression> a, std::shared_ptr<IExpression> b) const = 0;

	std::shared_ptr<IExpression> simplify() override;

public:
	std::shared_ptr<IExpression> _1;
	std::shared_ptr<IExpression> _2;
};

#endif //EXPCALC_IOPERATOR_H
