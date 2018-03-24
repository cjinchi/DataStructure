#include<iostream>
using namespace std;

void binary_search(int left, int right, int num,int p[],int key);

int main()
{
	int length = -1, key = -1;
	while (cin >> length)
	{
		cin >> key;
		int *p = new int[length];
		for (int i = 0; i < length; i++)
			cin >> p[i];
		binary_search(0, length - 1, 1,p,key);
		delete[]p;
	}
	return 0;
}
void binary_search(int left, int right, int num, int p[],int key)
{
	if (left > right)
		cout << 0 << " " << num - 1 << endl;					
	else
	{
		int half = (left + right) / 2;
		if (key > p[half])
			binary_search(half + 1, right, num + 1, p, key);
		else if (key < p[half])
			binary_search(left, half - 1, num + 1, p, key);
		else
			cout << 1 << " "<<num << endl;
	}
}