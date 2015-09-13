#include "Element.h"
#include "Operator.h"

Compound::Compound(const Element* inLHS, const Operator* inOperator, const Element* inRHS)
	: mLHS(inLHS)
	, mRHS(inRHS)
	, mOperator(inOperator)
	, mResult((*inOperator)(mLHS->Value(), mRHS->Value()))
{
}

std::string Compound::ToString() const
{
	std::string str = "(";
	str += mLHS->ToString();
	str += " ";
	str += mOperator->mString;
	str += " ";
	str += mRHS->ToString();
	str += ")";
	return str;
}
