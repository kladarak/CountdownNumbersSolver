#pragma once

#include <vector>
#include "Element.h"

class Solver
{
public:
	Solver(const std::vector<int>& inNumbers, int inTarget);
	bool Solve();

private:
	std::vector<Number> mNumbers;
	int mTarget;
};
