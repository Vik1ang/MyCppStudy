#pragma once
#include <iostream>

class AbstracCalculator
{
public:
	virtual int get_result() = 0;

	void set_v1(int val);
	void set_v2(int val);

	int get_v1() const
	{
		return val1;
	}

	int get_v2() const
	{
		return val2;
	}

private:
	int val1 = 0;
	int val2 = 0;
};

class PlusCalculator :public AbstracCalculator
{
public:
	int get_result() override;
};

class MinusCalculator : public AbstracCalculator
{
public:
	int get_result() override;
};
