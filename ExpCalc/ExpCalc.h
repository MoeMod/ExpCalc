//
// Created by 小白白 on 2019-02-15.
//

#ifndef EXPCALC_EXPCALC_H
#define EXPCALC_EXPCALC_H

#include "IExpression.h"


extern std::shared_ptr<IExpression> buildExpression(const std::string_view &sv);

inline std::string buildExpressionString(const std::string_view &sv) { return buildExpression(sv)->toString(); }


#endif //EXPCALC_EXPCALC_H
