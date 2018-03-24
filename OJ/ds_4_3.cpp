#include<iostream>
#include<string>
using namespace std;
int str_len(string x)
{
	int i = 0;
	while (x[i] != '\0')
		i++;
	return i;
}
int main()
{
	string str1, str2;
	while (cin >> str1)
	{
		cin >> str2;
		int len1 = str_len(str1);
		int len2 = str_len(str2);
		int max_len=0;
		int loc = -1;//the begin of str in str1
		for (int i = 0; i < len1; i++)
		{
			for (int j = 0; j < len2; j++)
			{
				if (str1[i] == str2[j])
				{
					int len = 1;
					int a = i + 1;
					int b = j + 1;
					while (a < len1&&b < len2 && (str1[a] == str2[b]))
					{
						len++;
						a++;
						b++;
					}
					if (len > max_len)
					{
						loc = i;
						max_len = len;
					}
				}
			}
		}
		for (int i = loc; i < loc + max_len; i++)
		{
			cout << str1[i];
		}
		cout << endl;
	}
	return 0;
}

