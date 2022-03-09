#define MyAdd(x, y) ((x) + (y))

void test1()
{
	int ret = MyAdd(10, 20);
}

inline int myCompare(int a, int b)
{
	int ret = a < b ? a : b;
	return ret;
}

int main_func()
{
	test1();
	return 0;
}