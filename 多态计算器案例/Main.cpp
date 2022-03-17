#include "Calculator.h"

void string_study()
{
	AbstracCalculator* abc = new PlusCalculator;
	abc->set_v1(10);
	abc->set_v2(20);
	std::cout << abc->get_result() << std::endl;

	delete abc;

	abc = new MinusCalculator;
	abc->set_v1(10);
	abc->set_v2(20);
	std::cout << abc->get_result() << std::endl;
}

int main(int argc, char* argv[])
{
	string_study();
	return EXIT_SUCCESS;
}