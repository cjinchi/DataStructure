#include<iostream>
using namespace std;
struct node
{
	int n;
	bool get;
};
bool judge(int s, int n, node *p)
{
	bool temp=false;
	for (int i = 0; i < n; i++)
	{
		if (p[i].get == false)
		{
			p[i].get = true;
			s -= p[i].n;
			
			if (s == 0)
			{
				temp = true;
				break;
			}
			if (s > 0 && judge(s, n, p))
			{
				temp = true; 
				break;
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

		cout <<(judge(s,n,p)? "true":"false" )<< endl;
		delete[]p;
	}
	return 0;
}