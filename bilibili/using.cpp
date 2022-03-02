#include <iostream>
using namespace std;

namespace wzry
{
	int sun_wu_kong_Id = 10;
}

void test1()
{
	int sun_wu_kong_Id = 20;

	//using wzry::sun_wu_kong_Id;

	cout << wzry::sun_wu_kong_Id << endl;
}

int main_func(int argc, char* argv[])
{
	test1();
	return EXIT_SUCCESS;
}