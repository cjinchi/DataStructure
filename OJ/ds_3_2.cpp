#include<iostream>
using namespace std;
void init(bool arr[][8])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			arr[i][j] = false;
		}
	}
}
bool judge(int i, int j, bool arr[][8])
{
	int a, b;

	a = i+1;
	b = j+1;
	while (a < 8 && b < 8)
	{
		if (arr[a][b] == true)
			return false;
		a++;
		b++;
	}

	a = i - 1; 
	b = j - 1;
	while (a >= 0 && b >= 0)
	{
		if (arr[a][b] == true)
			return false;
		a--;
		b--;
	}

	a = i + 1;
	b = j - 1;
	while (a <8 && b >= 0)
	{
		if (arr[a][b] == true)
			return false;
		a++;
		b--;
	}

	a = i - 1;
	b = j + 1;
	while (a >= 0 && b <8)
	{
		if (arr[a][b] == true)
			return false;
		a--;
		b++;
	}

	a = i - 1;
	b = j;
	while (a >= 0)
	{
		if (arr[a][b] == true)
			return false;
		a--;
	}

	a = i + 1;
	b = j;
	while (a <8)
	{
		if (arr[a][b] == true)
			return false;
		a++;
	}

	a = i;
	b = j - 1;
	while (b >= 0)
	{
		if (arr[a][b] == true)
			return false;
		b--;
	}

	a = i;
	b = j+1;
	while (b<8)
	{
		if (arr[a][b] == true)
			return false;
		b++;
	}

	return true;
}
void output(bool arr[][8])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (arr[i][j] == true)
			{
				cout << j + 1;
			}
		}
	}
	cout << endl;
}
void f(bool arr[][8], int n)
{
	for (int j = 0; j < 8; j++)
	{
		arr[n][j] = true;
		if (judge(n, j, arr))
		{
			if (n == 7)
				output(arr);
			else
				f(arr, n + 1);
		}
		arr[n][j] = false;
	}
}

int main()
{
	bool arr[8][8];
	int num;
	while (cin >> num)
	{
		num--;
		init(arr);
		arr[0][num] = true;
		f(arr, 1);
	}
	return 0;
}