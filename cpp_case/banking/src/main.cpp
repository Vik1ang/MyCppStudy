#include <iostream>
#include "admin.h"
#include "customer.h"

void boot() {

}

int main() {
	void boot();

	int condition = 0;

	while (condition != 4)
	{
		std::cout << "You want to login as:\t\t\t\t\t\t" << std::endl << std::endl;
		std::cout << "1-Admin" << std::endl;
		std::cout << "2-Staff" << std::endl;
		std::cout << "3-Customer" << std::endl;
		std::cout << "4-Quit" << std::endl;

		// get user input
		std::cin >> condition;

		if (condition == 1) {
			admin();
		}
		else if (condition == 2) {
			// TODO: ûд
		}
		else if (condition == 3) {
			customer();
		}
		else if (condition == 4) {
			std::cout << "Quit!!!" << std::endl;
		}
		else {
			std::cout << "Wrong commands" << std::endl;
		}

	}

	return EXIT_SUCCESS;

}