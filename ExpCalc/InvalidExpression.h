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
};

#endif //EXPCALC_INVALIDEXPRESSION_H
