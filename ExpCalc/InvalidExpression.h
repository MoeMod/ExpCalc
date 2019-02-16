//
// Created by 小白白 on 2019-02-16.
//

#ifndef EXPCALC_INVALIDEXPRESSION_H
#define EXPCALC_INVALIDEXPRESSION_H

#include "IExpression.h"

class InvalidExpression : public IExpression
{
public:
	std::string toString() const override { return "[INVALID]"; }
	std::shared_ptr<IExpression> simplify() override { return shared_from_this(); }
};

#endif //EXPCALC_INVALIDEXPRESSION_H
