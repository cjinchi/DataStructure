#include<iostream>
using namespace std;
struct node
{
	int n;
	node *next;
};
void output(node *p);    //Êä³öÁ´±í
void del_list(node *p);  //É¾³ýÁ´±í
int main()
{
	int n;
	while (cin >> n)
	{
		node *head = NULL, *tail = NULL;
		for (int i = 0; i < n; i++)
		{
			node *p = new node;
			cin >> (p->n);
			p->next = NULL;
			if (head == NULL)
				head = tail = p;
			else
			{
				tail->next = p;
				tail = p;
			}
		}
		//complete getting list

		node *temp = head;
		node *oh = NULL, *ot = NULL;//odd
		node *eh = NULL, *et = NULL;//even
		
		//for (int i = 1; temp != NULL; i++)
		while(temp!=NULL)
		{
			node *p = new node;
			p->n = temp->n;
			p->next = NULL;
			if ((p->n) % 2 == 1)
			{
				if (oh == NULL)
					oh = ot = p;
				else
				{
					ot->next = p;
					ot = p;
				}
			}
			else
			{
				if (eh == NULL)
					eh = et = p;
				else
				{
					et->next = p;
					et = p;
				}
			}
			temp = temp->next;
		}

		output(head);
		output(oh);
		output(eh);
		del_list(head);
		del_list(oh);
		del_list(eh);

	}
	return 0;
}
void output(node *p)
{
	while (p->next != NULL)
	{
		cout << p->n << " ";
		p = p->next;
	}
	cout << p->n << endl;
}
void del_list(node *p)
{
	while (p != NULL)
	{
		node *h = p;
		p = p->next;
		delete h;
	}
}