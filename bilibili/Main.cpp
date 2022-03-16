#include <iostream>

template<class T>
void my_swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

template<class T>
void my_sort(T arr[], int len)
{
	for (int i = 0; i < len; ++i)
	{
		int max = i;
		for (int j = i + 1; j < len; ++j)
		{
			if (arr[max] < arr[j])
			{
				max = j;
			}
		}
		if (max != i)
		{
			my_swap(arr[max], arr[i]);
		}
	}
}

template<class T>
void print(T arr[], int len)
{
	for (int i = 0; i < len; ++i)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

void test1()
{
	char arr[] = "helloworld";
	my_sort(arr, sizeof(arr) / sizeof(char));
	print(arr, sizeof(arr) / sizeof(char));
}

int main(int argc, char* argv[])
{
	test1();
	return EXIT_SUCCESS;
}