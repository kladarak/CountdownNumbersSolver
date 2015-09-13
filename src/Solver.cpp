#include "Solver.h"
#include "Operator.h"

static const Operator sOperators[] =
{
	{ 
		(Operator::OperandCheck)	[] (int, int)				{ return true; }, 
		(Operator::Operation)		[] (int inLHS, int inRHS)	{ return inLHS + inRHS; }, 
		"+" 
	},
	{ 
		(Operator::OperandCheck)	[] (int inLHS, int inRHS)	{ return inLHS > inRHS; }, 
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

static bool solveRecursion(const std::vector<Element*>& inElements, int inTarget)
{
	for (auto lhs : inElements)
	{
		for (auto rhs : inElements)
		{
			if (lhs == rhs)
			{
				continue;
			}

			for (size_t i = 0; i < sizeof(sOperators)/sizeof(Operator); ++i)
			{
				const Operator* op = &sOperators[i];
				
				if (op->CanOperate(lhs->Value(), rhs->Value()))
				{
					Compound result(lhs, op, rhs);
					//printf("%s\n", result.ToString().c_str());

					if (result.Value() == inTarget)
					{
						printf("%s = %i\n", result.ToString().c_str(), inTarget);
						return true;
					}
					else if (inElements.size() == 2)
					{
						// Don't recurse further. 
						continue;
					}
					else
					{
						std::vector<Element*> newElems;
						newElems.push_back(&result);

						for (auto elem : inElements)
						{
							if (elem != lhs && elem != rhs)
							{
								newElems.push_back(elem);
							}
						}
						
						if (solveRecursion(newElems, inTarget))
						{
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

bool Solver::Solve()
{
	std::vector<Element*> elements;
	for (auto& num : mNumbers)
	{
		elements.push_back(&num);
	}
	
	return solveRecursion(elements, mTarget);
}

