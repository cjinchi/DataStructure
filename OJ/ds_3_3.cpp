#include<iostream>
using namespace std;
struct node
{
	int n;
	int get;
};
int main()
{
	int m, n;
	while (cin >> m)
	{
		cin >> n;
		node **p = new node *[m];			//set p[m][n]
		for (int i = 0; i < m; i++)
			p[i] = new node[n];
		
		for (int i = 0; i < m; i++)		//get data of p[m][n]
		{
			for (int j = 0; j < n; j++)
			{
				p[i][j].get = 0;
				cin >> (p[i][j].n);
			}
		}

		for (int i = 0;i < m; i++)
		{
			int min = 0;
			for (int j = 1; j < n; j++)
			{
				if (p[i][j].n < p[i][min].n)
					min = j;
			}
			for (int j = 0; j < n; j++)
			{
				if (p[i][j].n == p[i][min].n)
					p[i][j].get++;
			}
		}

		for (int j = 0; j < n; j++)
		{
			int max = 0;
			for (int i = 1; i < m; i++)
			{
				if (p[i][j].n > p[max][j].n)
					max = i;
			}
			for (int i = 0; i < m; i++)
			{
				if (p[i][j].n ==p[max][j].n)
					p[i][j].get++;
			}
		}

		bool has_output = false;
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (p[i][j].get == 2)
				{
					if (has_output)
						cout << "," << i + 1 << " " << j + 1;
					else
					{
						cout << i + 1 << " " << j + 1;
						has_output = true;
					}
				}
			}
		}
		cout << endl;

		for (int i = 0; i < m; i++)
		{
			delete[]p[i];
			p[i] = NULL;
		}
		delete[]p;
		p = NULL;

	}
	return 0;
}
