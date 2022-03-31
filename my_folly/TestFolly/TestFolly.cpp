#include <iostream>

#include "include/Interface.h"

int main(int argc, char* argv[])
{
	IInterface* IF = IInterface::CreateInterface();

	std::cout << IF->GetName() << std::endl;

	return 0;
}
