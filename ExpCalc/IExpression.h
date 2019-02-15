//
// Created by 小白白 on 2019-02-15.
//

#ifndef EXPCALC_IEXPRESSION_H
#define EXPCALC_IEXPRESSION_H

#include <string>

class IExpression
{
public:
	virtual ~IExpression() = default;
	virtual std::string toString() const = 0;
};


#endif //EXPCALC_IEXPRESSION_H
