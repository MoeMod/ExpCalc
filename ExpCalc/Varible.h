//
// Created by 小白白 on 2019-04-22.
//

#ifndef EXPCALC_VARIBLE_H
#define EXPCALC_VARIBLE_H

#include "IExpression.h"

class Varible : public IExpression
{
public:
	explicit Varible(char name) : C(name) {}
	std::string toString() const override { return std::string{ C }; }
	std::shared_ptr<IExpression> simplify() override { return shared_from_this(); }

	JudgeResult equalsTo(std::shared_ptr<IExpression> other) override
	{
		auto p = std::dynamic_pointer_cast<Varible>(other);
		return p ? (C==p->C ? JR_YES:JR_NO):JR_UNKNOWN;
	}

public:
	const char C;
};

#endif //EXPCALC_VARIBLE_H
