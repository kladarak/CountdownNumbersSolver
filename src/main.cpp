#include <cstdio>
#include <cstdlib>
#include <time.h>

#include "Solver.h"

/*
	TODO: Brute forcing it seems to be effective enough, but we can speed things up
	by removing use of stl and doing stack allocations of arrays instead of using std::vector.
*/

static std::vector<int> GenNumbers()
{
	static int sBigNumbers[] = { 25, 50, 75, 100 };
	static int sSmallNumbers[] = { 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10 };
	
	std::vector<int> availableBigNumbers;
	std::vector<int> availableSmallNumbers;

	for (int i = 0; i < sizeof(sBigNumbers)/sizeof(int); ++i)
	{
		availableBigNumbers.push_back(sBigNumbers[i]);
	}

	for (int i = 0; i < sizeof(sSmallNumbers)/sizeof(int); ++i)
	{
		availableSmallNumbers.push_back(sSmallNumbers[i]);
	}

	int bigNumCount		= rand() % 5;
	int smallNumCount	= 6 - bigNumCount;
	std::vector<int> outNumbers;

	for (int i = 0; i < bigNumCount; ++i)
	{
		size_t index = rand() % availableBigNumbers.size();
		int num = availableBigNumbers[index];
		availableBigNumbers.erase(availableBigNumbers.begin() + index, availableBigNumbers.begin() + index + 1);
		outNumbers.push_back(num);
	}

	for (int i = 0; i < smallNumCount; ++i)
	{
		size_t index = rand() % availableSmallNumbers.size();
		int num = availableSmallNumbers[index];
		availableSmallNumbers.erase(availableSmallNumbers.begin() + index, availableSmallNumbers.begin() + index + 1);
		outNumbers.push_back(num);
	}

	return outNumbers;
};

static int GenTarget()
{
	int minTarget = 101;
	int maxTarget = 999;
	int range = maxTarget - minTarget;
	int offset = rand() % range;
	return minTarget + offset;
}

static void ParseArgs(int argc, char* argv[], std::vector<int>& outNumbers, int& outTarget)
{
	for (int i = 1; i < argc; ++i)
	{
		int num = strtol(argv[i], nullptr, 10);
		if (i < (argc - 1))
		{
			outNumbers.push_back(num);
		}
		else
		{
			outTarget = num;
		}
	}
}

int main(int argc, char* argv[])
{
	std::vector<int> numbers;
	int target = 0;

	if (argc < 3)
	{
		printf("Generating Random Numbers and Target.\n");
		srand((unsigned int)time(NULL));
		numbers = GenNumbers();
		target = GenTarget();
	}
	else
	{
		ParseArgs(argc, argv, numbers, target);
	}

	printf("Input: ");
	for (int num : numbers)
	{
		printf("%i ", num);
	}
	printf("Target: %i\n", target);

	if (Solver(numbers, target).Solve())
	{
		printf("Success.\n");
	}
	else
	{
		printf("Failed.\n");
	}

	system("pause");
	return 0;
}