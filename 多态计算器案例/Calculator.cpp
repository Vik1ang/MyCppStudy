#include "Calculator.h"

void AbstracCalculator::set_v1(const int val)
{
	val1 = val;
}

void AbstracCalculator::set_v2(const int val)
{
	val2 = val;
}

int PlusCalculator::get_result()
{
	return get_v1() + get_v2();
}

int MinusCalculator::get_result()
{
	return get_v1() - get_v2();
}