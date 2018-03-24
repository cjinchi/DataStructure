#include<iostream>
#include<string>
using namespace std;
struct item
{
	int utype;
	union
	{
		int ref;
		int value;
		item *hlink;
	};
	item *tlink;
};

item *get_list(string temp);				//A func to get list from str
void output_reverse(item *head,bool cout_endl);//A func to print result,bool is to "cout<<endl"

int main()
{
	string temp;
	while (cin >> temp)
	{
		temp.erase(temp.begin());	//remove '('
		temp.erase(temp.end()-1);		//remove ')'
		item *head=get_list(temp);
		output_reverse(head,true);
	}
	return 0;
}
item *get_list(string temp)
{
	int len = temp.length();
	if (len == 0)
		return NULL;

	item *head = new item;
	head->utype = 0;
	head->ref = 0;
	head->tlink = NULL;

	item *current = head;     //point to current node
	int i = 0;
	while(i<len)
	{
		if (temp[i] == '(')
		{

			item *sublist = new item;
			sublist->utype = 2;
			sublist->tlink = NULL;
			current->tlink = sublist;
			current = sublist;

			int left = 0;
			int right = 0;
			string node_list = "";
			while (1)
			{
				node_list += temp[i];
				if (temp[i] == '(')
					left++;
				if (temp[i] == ')')
					right++;
				i++;
				if (left == right)
					break;		
			}

			node_list.erase(node_list.begin());//remove '('
			node_list.erase(node_list.end() - 1);
			sublist->hlink = get_list(node_list);
		}
		else if (temp[i] == ',')
		{
			i++;
		}
		else
		{
			item *node = new item;
			node->utype = 1;
			node->value = int(temp[i]);
			node->tlink = NULL;
			current->tlink = node;
			current = node;
			i++;
		}

	}
	return head;
}

void output_reverse(item *head, bool cout_endl)
{
	if (head == NULL)
		return;

	output_reverse(head->tlink,false);

	if (head->utype == 0)
	{
		if (cout_endl)
			cout << endl;
		return;
	}
		
	else if (head->utype == 1)
	{
		cout << char(head->value);
	}
	else
	{
		if (head->hlink == NULL)
			cout << "@";
		else
			output_reverse(head->hlink,false);
	}
	if (cout_endl)
		cout << endl;
}
