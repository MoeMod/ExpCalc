//
// Created by 小白白 on 2019-02-15.
//

#ifndef EXPCALC_UNARYOPERATOR_H
#define EXPCALC_UNARYOPERATOR_H

namespace detail
{
	template<char Name>
	class TForwardUnaryOperator : public IUnaryOperator
	{
	public:
		using IUnaryOperator::IUnaryOperator;
		std::string toString() const override
		{
			return Name + _1->toString();
		}
	};
	template<char Name>
	class TBackwardUnaryOperator : public IUnaryOperator
	{
	public:
		using IUnaryOperator::IUnaryOperator;
		std::string toString() const override
		{
			return _1->toString() + Name;
		}
	};
}

class OptReverseNumber : public detail::TForwardUnaryOperator<'-'>
{
public:
	using TForwardUnaryOperator::TForwardUnaryOperator;

};

#endif //EXPCALC_UNARYOPERATOR_H
