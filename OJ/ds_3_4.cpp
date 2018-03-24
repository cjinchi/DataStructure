#include<iostream>
using namespace std;
int gcd(int a, int b)
{
	if (a < b)
		return gcd(b, a);
	if (a%b == 0)
		return b;
	else
		return gcd(b, a % b);
}
long long c(int n, int k)
{
	if (k < (n / 2))
		return c(n, n - k);
	int *p1 = new int[n - k];//fen zi
	int *p2 = new int[n - k];//fen mu
	for (int i = 0; i < n - k; i++)
	{
		p1[i] = k + 1 + i;
		p2[i] = i + 1;
	}
	for (int i = 0; i < n - k; i++)
	{
		for (int j = 0; j < n - k; j++)
		{
			int temp = gcd(p1[i], p2[j]);
			if ( temp!= 1)
			{
				p1[i] /= temp;
				p2[j] /= temp;
			}
		}
	}
	long long result = 1;
	for (int i = 0; i < n - k; i++)
		result *= p1[i];
	
	delete[]p1;
	delete[]p2;
	return result;
}
int main()
{
	int n, k;
	while (cin >> n)
	{
		cin >> k;
		cout << c(n, k) << endl;
	}
	return 0;
}