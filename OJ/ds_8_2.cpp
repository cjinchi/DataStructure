#include<iostream>
using namespace std;
#define SIZE_OF_LIST 21
#define next(x) ((x+1)%SIZE_OF_LIST)

int insert_item(int item,int arr[], bool occupied[]);

int main()
{
	int n;
	while (cin >> n)
	{
		int arr[SIZE_OF_LIST] = { 0 };
		bool occupied[SIZE_OF_LIST] = { false };

		int temp;
		for (int i = 0; i < n; i++)
		{
			cin >> temp;
			insert_item(temp, arr, occupied);
		}

		cin >> temp;
		cout << insert_item(temp, arr, occupied)<<endl;
	}
	return 0;

}

int insert_item(int item, int arr[], bool occupied[])
{
	int ptr = item % 17;
	if (!occupied[ptr])
	{
		arr[ptr] = item;
		occupied[ptr] = true;	
		return ptr;
	}
	else
	{
		int sptr = next(ptr);
		while(sptr!=ptr)
		{
			if (!occupied[sptr])
			{
				arr[sptr] = item;
				occupied[sptr] = true;
				return sptr;
			}
			sptr = next(sptr);
		}
		if (sptr == ptr)	//fail
			return -1;
	}
}