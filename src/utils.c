#include <nonamedef.h>

int* get_int_array(int first, int second, int third)
{
	int *arr = malloc(sizeof(int) * 4);
	arr[0] = first;
	arr[1] = second;
	arr[2] = third;
	return arr;

}

int cmp_int_arr(const int *first, const int *second)
{
	for (int i = 0;i < 3;i++)
		if (first[i] != second[i])
			return 0;
	return 1;
}
