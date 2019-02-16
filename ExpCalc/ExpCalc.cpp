//
// Created by 小白白 on 2019-02-15.
//

#include "ExpCalc.h"


#include "IConstant.h"
#include "Constant.h"

#include "IOperator.h"
#include "UnaryOperator.h"
#include "BinaryOperator.h"

#include "InvalidExpression.h"

namespace detail
{
	template<class...Char>
	constexpr auto FindLastCharIgnoreBrace(const std::string_view &sv, Char...C)
	-> typename std::enable_if<(std::is_convertible<Char, char>::value && ...), size_t>::type
	{
		auto n = std::string_view::npos;
		for(size_t i = 0, b = 0; i < sv.size(); ++i)
		{
			if(sv[i] == '(')
				++b;
			if(sv[i] == ')')
				--b;
			if(b)
				continue;
			if(((sv[i] == C) || ...))
				n = i;
		}
		return n;
	}
}

std::shared_ptr<IExpression> buildExpression(const std::string_view &sv)
{
	if(sv.empty())
		return std::make_shared<TConstant<int>>(0);

	// handle operators
	if(auto n  = detail::FindLastCharIgnoreBrace(sv, '+', '-'); n != std::string_view::npos)
	{
		if(sv[n] == '+')
			return n == 0 ?
				buildExpression(sv.substr(1)):
				std::make_shared<OptPlus>(buildExpression(sv.substr(0, n)), buildExpression(sv.substr(n+1)));
		else if(sv[n] == '-')
			return n == 0 ? (std::shared_ptr<IExpression>)
		            std::make_shared<OptReverseNumber>(buildExpression(sv.substr(1))) :
		            std::make_shared<OptMinus>(buildExpression(sv.substr(0, n)), buildExpression(sv.substr(n+1)));
	}

	if(auto n  = detail::FindLastCharIgnoreBrace(sv, '*', '/'); n != std::string_view::npos)
	{
		if(sv[n] == '*')
			return std::make_shared<OptMultiply>(buildExpression(sv.substr(0, n)), buildExpression(sv.substr(n+1)));
		else if(sv[n] == '/')
			return std::make_shared<OptDivide>(buildExpression(sv.substr(0, n)), buildExpression(sv.substr(n+1)));
	}

	if(sv.front() == '(' && sv.back() == ')')
		return buildExpression(sv.substr(1, sv.size() - 2));

	// handle constants
	if(auto n = sv.find('.'); n != std::string_view::npos)
		try {
			return std::make_shared<TConstant<double>>(std::stod(std::string(sv))); // try
		} catch( const std::exception &e) {}

	try {
		return std::make_shared<TConstant<long long>>(std::stoull(std::string(sv))); // try
	} catch( const std::exception &e) {}


	return std::make_shared<InvalidExpression>();
}