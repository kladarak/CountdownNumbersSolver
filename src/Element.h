#pragma once

#include <string>

struct Operator;

class Element
{
public:
	virtual ~Element() { }
	virtual int			Value() const = 0;
	virtual std::string ToString() const = 0;

};

class Number : public Element
{
public:
	Number(int inValue) : mValue(inValue) { }

	virtual int			Value()	const		{ return mValue; }
	virtual std::string ToString() const	{ return std::to_string(mValue); }

private:
	int mValue;
};

class Compound : public Element
{
public:
	Compound(const Element* inLHS, const Operator* inOperator, const Element* inRHS);
	
	virtual int			Value()	const		{ return mResult; }
	virtual std::string ToString() const;

private:
	const Element* mLHS;
	const Element* mRHS;
	const Operator* mOperator;
	int mResult;
};
