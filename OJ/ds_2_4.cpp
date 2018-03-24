#include<iostream>
using namespace std;
struct node
{
	int n;
	bool get;
};
int judge(int s, int n, node *p,int begin)
{
	int temp = 0;
	for (int i = begin; i < n; i++)
	{
		if (p[i].get == false)
		{
			p[i].get = true;
			s -= p[i].n;

			if (s == 0)
			{
				temp++;
			}
			if (s > 0 )
			{
				temp += judge(s, n, p, i+1);
			}

			s += p[i].n;
			p[i].get = false;
		}
	}
	return temp;
}
int main()
{
	int s, n;
	while (cin >> s)
	{
		cin >> n;
		node *p = new node[n];
		for (int i = 0; i < n; i++)
		{
			cin >> (p[i].n);
			p[i].get = false;
		}

		cout << judge(s, n, p,0) << endl;
		delete[]p;
	}
	return 0;
}