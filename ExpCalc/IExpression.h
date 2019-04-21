//
// Created by 小白白 on 2019-02-15.
//

#ifndef EXPCALC_IEXPRESSION_H
#define EXPCALC_IEXPRESSION_H

#include <string>
#include <memory>

enum JudgeResult
{
	JR_UNKNOWN = -1,
	JR_NO = 0,
	JR_YES = 1
};

class IExpression : public std::enable_shared_from_this<IExpression>
{
public:
	virtual ~IExpression() = default;
	virtual std::string toString() const = 0;
	virtual std::shared_ptr<IExpression> simplify() = 0;
	virtual JudgeResult equalsTo(std::shared_ptr<IExpression> other) = 0;
};


#endif //EXPCALC_IEXPRESSION_H
