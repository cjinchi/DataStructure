#include<iostream>
using namespace std;
#define INT_MAX 2147483647
struct node
{
	node *prior;
	node *next;
	int data;
	int freq;
};
void exchange(node *p)
{
	node *prior_prior = p->prior->prior;//1
	node *prior = p->prior;//2
	//p is 3
	node *next_next = p->next;//4
	prior_prior->next = p;
	p->next = prior;
	prior->next = next_next;
	if (next_next != NULL)
		next_next->prior = prior;
	prior->prior = p;
	p->prior = prior_prior;
}
void locate(int temp, node *head, node *tail)
{
	if (head->next == NULL)
		return;
	node *pt = head->next;
	while (pt->data != temp)
		pt = pt->next;
	(pt->freq)++;
	while ((pt->freq) > (pt->prior->freq))
		exchange(pt);
}
void output(node *p)
{
	p = p->next;
	while (p != NULL&&p->next != NULL)
	{
		//if (p->next==NULL)
		//break;
		cout << "<" << p->data << "," << p->freq << ">,";
		p = p->next;
	}
	cout << "<" << p->data << "," << p->freq << ">" << endl;


}
void del_node(node *head)
{
	while (head != NULL)
	{
		node *temp = head;
		head = head->next;
		delete temp;
	}
}
int main()
{
	int node_num;
	while (cin >> node_num)
	{
		int visit_num;
		cin >> visit_num;
		node *head = new node;
		node *tail = head;
		head->data = -1;
		head->freq = INT_MAX;
		head->next = NULL;
		head->prior = NULL;
		for (int i = 0; i < node_num; i++)
		{
			node *p = new node;
			cin >> (p->data);
			p->freq = 0;
			p->prior = tail;
			p->next = NULL;
			tail->next = p;
			tail = p;
		}
		for (int i = 0; i < visit_num; i++)
		{
			int temp;
			cin >> temp;
			locate(temp, head, tail);
		}
		output(head);
		del_node(head);
	}
	return 0;
}