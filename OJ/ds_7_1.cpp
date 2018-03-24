#include<iostream>
#include<string>
#include<sstream>
using namespace std;
int *get_array_from_string(string line, int &size);
void make_min_heap(int arr[],int size);
void output_min_heap(int arr[],int size);
void sift_down(int p, int arr[],int size);

int main()
{
	string line;
	while (getline(cin, line))
	{
		int size = 0;	//size of array
		int *arr = get_array_from_string(line,size);
		make_min_heap(arr,size);
		output_min_heap(arr,size);
		delete[]arr;
	}
}
int *get_array_from_string(string line,int &size)
{
	//copy numbers in line to arr
	int len = int(line.length());
	size = 0;
	for (int i = 0; i<len; i++)
	{
		if (line[i] == ' ')
			size++;
	}
	size++;
	int *arr = new int[size];

	//Copy number to arr
	stringstream x;
	x.clear();
	x.str("");

	x << line;
	int aindex = 0;			//index of array

	while (aindex<size)
	{
		x >> arr[aindex];
		aindex++;
	}

	x.clear();
	x.str("");
	return arr;
}
void make_min_heap(int arr[],int size)
{
	int p = (size - 2) / 2;
	while (p >= 0)
	{
		sift_down(p,arr,size);
		p--;
	}
}
void output_min_heap(int arr[], int size)
{
	for (int i = 0; i < size - 1; i++)
		cout << arr[i] << " ";
	cout << arr[size - 1] << endl;
}
void sift_down(int p, int arr[], int size)
{
	int temp = arr[p];		//save root

	while (1)
	{
		//Step 1:get min child
		int min_child = ((2 * p + 2 < size) && (arr[2 * p + 1] > arr[2 * p + 2])) ?
			2 * p + 2 : 2 * p + 1;
		//Step 2:exchange if necessary
		if (min_child < size&&temp > arr[min_child])	//necessary
		{
			arr[p] = arr[min_child];
			p = min_child;
		}
		else											//unnecessary,so p is the place to save temp
		{	
			break;
		}
	}

	arr[p] = temp;
}
