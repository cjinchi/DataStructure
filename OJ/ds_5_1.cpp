#include<iostream>
#include<string>
//#include<cstring>
using namespace std;
struct node
{
	int n;
	node *next;
};

int str_len(string x)
{
	int i = 0;
	while (x[i] != '\0')
		i++;
	return i;
}
bool str_equal(string str, int begin1, int end1, int begin2, int end2)
{
	//return true if str[begin1...end1]==str[begin2...end2] 
	while (str[begin1] == str[begin2])
	{
		if (begin1 == end1&&begin2==end2)
			return true;
		else
		{
			begin1++;
			begin2++;
		}
	}
	return false;

}
int next(int j,string str)//According to definition of func next(j)
{
	if (j == 0)
		return -1;
	
	int k = j - 2;
	while (k >= 0 && !str_equal(str, 0, k, j - k - 1, j - 1))
		k--;

	if (k >= 0)
		return k + 1;
	else
		return 0;
}
int main()
{
	string one_line;//Including str_s and str_w
	while (getline(cin, one_line))
	{
		string s = "";
		string w = "";
		//Step 1: get s and w
		int index = 0;
		while (one_line[index] != ',')
		{
			s += one_line[index];
			index++;
		}
		index++;
		while (one_line[index] != '\0')
		{
			w += one_line[index];
			index++;
		}

		//Step 2:KMP
		int s_len = str_len(s.c_str());
		int w_len = str_len(w.c_str());
		int s_index = 0;
		int w_index = 0;
		node *head = NULL, *tail = NULL;//a list to save output
		
		while (s_index < s_len)
		{
			if (s[s_index] == w[w_index])
			{
				if (w_index == w_len - 1)//Success.
				{
					//begin adding ouput-list
					node *temp=new node;
					temp->n = s_index - w_len + 1;
					temp->next = NULL;
					if (head == NULL)
						head = tail = temp;
					else
					{
						tail->next = temp;
						tail = temp;
					}
					//end adding outout_list
					
					//ERROR HERE in version 1
					s_index++;
					w_index = next(w_index + 1, w);
				}
				else
				{
					s_index++;
					w_index++;
				}
				
			}
			else //(s[s_index] != w[w_index])
			{
				if (w_index == 0)
				{
					s_index++;
					//w_index do nothing(Keep ZERO)
				}
				else
				{
					//s_index do nothing
					w_index = next(w_index,w);
				}
			}
		}
		
		//Step 3:output result
		if (head == NULL)
			cout << "false" << endl;
		else
		{
			node *temp = head;
			while (temp->next != NULL)
			{
				cout << temp->n << " ";
				temp = temp->next;
			}
			cout << temp->n << endl;
		}
		
		//Step 4:delete list
		while (head != NULL)
		{
			node *temp = head;
			head = head->next;
			delete temp;
		}
	}
	return 0;
}