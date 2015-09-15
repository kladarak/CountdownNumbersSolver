#include "Solver.h"
#include "Operator.h"

#include <algorithm>

static const Operator sOperators[] =
{
	{ 
		(Operator::OperandCheck)	[] (int, int)				{ return true; }, 
		(Operator::Operation)		[] (int inLHS, int inRHS)	{ return inLHS + inRHS; }, 
		"+" 
	},
	{ 
		(Operator::OperandCheck)	[] (int inLHS, int inRHS)	{ return (inLHS - inRHS) > 0; }, 
		(Operator::Operation)		[] (int inLHS, int inRHS)	{ return inLHS - inRHS; }, 
		"-" 
	},
	{ 
		(Operator::OperandCheck)	[] (int, int)				{ return true; }, 
		(Operator::Operation)		[] (int inLHS, int inRHS)	{ return inLHS * inRHS; }, 
		"*"
	},
	{ 
		(Operator::OperandCheck)	[] (int inLHS, int inRHS)	{ return (inRHS != 0) && (inLHS % inRHS == 0); }, 
		(Operator::Operation)		[] (int inLHS, int inRHS)	{ return inLHS / inRHS; }, 
		"/" 
	},
};

Solver::Solver(const std::vector<int>& inNumbers, int inTarget)
	: mTarget(inTarget)
{
	for (int num : inNumbers)
	{
		mNumbers.push_back(Number(num));
	}
}

static void mySort(Element** inStart, int inCount)
{
	std::sort(inStart, inStart + inCount, [] (Element* inLHS, Element* inRHS) { return inLHS->Value() > inRHS->Value(); } );
}

static bool solveRecursion(Element** inStart, int inCount, int inTarget)
{
	if (inCount == 1)
	{
		return false;
	}

	// Alloc once per entry, rather than inside loop which may potentially stack overflow.
	Element** newElems = (Element**) alloca(sizeof(Element*) * (inCount - 1));

	for (int lhsIx = 0; lhsIx < (inCount - 1); ++lhsIx)
	{
		auto lhs = inStart[lhsIx];

		for (int rhsIx = (lhsIx + 1); rhsIx < inCount; ++rhsIx)
		{
			auto rhs = inStart[rhsIx];

			for (size_t i = 0; i < sizeof(sOperators)/sizeof(Operator); ++i)
			{
				const Operator* op = &sOperators[i];
				
				if (!op->CanOperate(lhs->Value(), rhs->Value()))
				{
					continue;
				}

				Compound result(lhs, op, rhs);
				//printf("%s\n", result.ToString().c_str());

				if (result.Value() == inTarget)
				{
					printf("%s = %i\n", result.ToString().c_str(), inTarget);
					return true;
				}
				else
				{
					int count = 0;
					newElems[count++] = &result;

					for (int elemIx = 0; elemIx < inCount; ++elemIx)
					{
						if (elemIx != lhsIx && elemIx != rhsIx)
						{
							newElems[count++] = inStart[elemIx];
						}
					}

					mySort(newElems, count);
						
					if (solveRecursion(newElems, count, inTarget))
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool Solver::Solve()
{
	Element** elems = (Element**) alloca(sizeof(Element*) * mNumbers.size());
	int count = 0;
	for (auto& num : mNumbers)
	{
		elems[count++] = &num;
	}

	mySort(elems, count);

	return solveRecursion(elems, count, mTarget);
}

