#include<iostream>
#include<string>
using namespace std;
int len_of_str(string x)
{
	int i = 0;
	while (x[i] != '\0')
		i++;
	return i;
}
int main()
{
	string temp;
	while (cin >> temp)
	{
		int loc = 0;
		int type = -1;//0 is abba,1 is yyxyy
		int max_len = 0;
		int len = len_of_str(temp);

		//type 0
		for (int i = 0; i < len-1; i++)
		{
			if (temp[i] == temp[i + 1])//type 0
			{
				int j = i-1,k=i+2,temp_len=2;
				while (j >= 0 && k < len && (temp[j] == temp[k]))
				{
					temp_len += 2;
					j--;
					k++;
				}
				if (temp_len > max_len)
				{
					loc = i;
					max_len = temp_len;
					type = 0;
				}
			}
			//type 1
			int a = i - 1;
			int b = i + 1;
			int temp_len2 = 1;
			while (a >= 0 && b < len && (temp[a] == temp[b]))
			{
				a--;
				b++;
				temp_len2 += 2;
			}
			if (temp_len2 > max_len)
			{
				loc = i;
				max_len = temp_len2;
				type = 1;
			}


		}

		if (type == 0)
		{
			int begin = loc-(max_len/2)+1;
			for (int i = begin; i < begin + max_len; i++)
			{
				cout << temp[i];
			}
			cout << endl;
		}
		else if (type == 1)
		{
			int begin = loc - (max_len - 1) / 2;
			for (int i = begin; i < begin + max_len; i++)
				cout << temp[i];
			cout << endl;
		}
		else
		{
			cout << endl;
		}
	}
	return 0;
}