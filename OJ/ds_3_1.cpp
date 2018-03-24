#include<iostream>
#include<string>
using namespace std;
struct node
{
	int n;
	node *next;
};
int main()
{
		string temp;
		while (getline(cin, temp))
		{
			node *head = NULL, *tail = NULL;
			int i = 0;
			bool is_num = false;
			int s = 1;
			while (temp[i] != '\0')
			{
				if (temp[i] == ' ')
				{
					if (tail != NULL)
						(tail->n) *= s;
					is_num = false;
					s = 1;
				}

				else if (temp[i] == '-')
					s = -1;
				else
				{
					if (is_num)
						tail->n = (tail->n) * 10 + temp[i] - '0';
					else
					{
						node *p = new node;
						p->n = temp[i] - '0';
						p->next = NULL;
						if (head == NULL)
							head = tail = p;
						else
						{
							tail->next = p;
							tail = p;
						}
					}
					is_num = true;
				}
				i++;

			}
			if (tail != NULL)
				(tail->n) *= s;
			tail->next = head;
			if (head->next != head)
			{
				node *x = head, *y = x->next;
				while (y != tail)
				{
					node *z = y->next;
					y->next = x;
					x = y;
					y = z;
				}
				y->next = x;
				head->next = NULL;
			}
			//output(tail);
			//del_list(tail);
		}
		return 0;
}