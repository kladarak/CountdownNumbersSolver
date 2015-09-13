#pragma once

#include <string>
#include <functional>

struct Operator
{
	typedef std::function<bool (int, int)> OperandCheck;
	typedef std::function<int (int, int)> Operation;

	OperandCheck	mOperandCheck;
	Operation		mOperation;
	std::string		mString;

	bool CanOperate(int inLHS, int inRHS) const { return mOperandCheck(inLHS, inRHS); }
	int operator()(int inLHS, int inRHS) const { return mOperation(inLHS, inRHS); }
};
