#include<iostream>
using namespace std;
int gcd(int a, int b)
{

	if (a%b == 0)
		return b;
	else
	{
		return gcd(b, a % b);
	}
}
int main()
{
	int a, b;
	while (cin >> a)
	{
		cin >> b;
		if (a < b)
		{
			int temp = a;
			a = b;
			b = temp;
		}
		cout << gcd(a, b) << endl;
	}
	return 0;
}