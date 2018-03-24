#include<iostream>
using namespace std;
int main()
{
	int m, n;
	while (cin >> m >> n)
	{
		int *pa = new int[m];
		int *pb = new int[n];
		for (int i = 0; i < m; i++)
			cin >> pa[i];
		for (int j = 0; j < n; j++)
			cin >> pb[j];
		
		int *pc = new int[m + n];//Save new list
		int ia = 0, ib = 0, ic = 0;
		while (ia != m&&ib != n)
		{
			pc[ic] = (pa[ia] < pb[ib] ? pa[ia] : pb[ib]);
			pa[ia] < pb[ib] ? ia++ : ib++;
			ic++;
		}
		while (ia != m)
		{
			pc[ic] = pa[ia];
			ia++;
			ic++;
		}
		while (ib != n)
		{
			pc[ic] = pb[ib];
			ib++;
			ic++;
		}
		
		for (int i = 0; i < m + n - 1; i++)
		{
			cout << pc[i] << " ";
		}
		cout << pc[m + n - 1] << endl;
		delete[]pa;
		delete[]pb;
		delete[]pc;
	}
	return 0;
}