#include<iostream>
#include<string>
using namespace std;
struct node
{
	char n;
	node *lc;
	node *rc;
	node *pa;
};

node *pre_order_creat_tree(string temp, int& p)   //read from temp[p]
{
	if (temp[p] == '@')
	{
		p++;
		return NULL;
	}
	node *item = new node;
	item->n = temp[p];
	p++;
	item->lc = pre_order_creat_tree(temp, p);
	item->rc = pre_order_creat_tree(temp, p);
	if (item->lc != NULL)
		item->lc->pa = item;
	if (item->rc != NULL)
		item->rc->pa = item;
	return item;
}
void output_route(node *head)
{
	if (head == NULL)
		return;

	if (head->lc == NULL&&head->rc == NULL)	//head is a leaf
	{
		node *temp = head;
		while (head != NULL)
		{
			cout << head->n;
			head = head->pa;
		}
		cout << endl;
	}
	else
	{
		if (head->lc != NULL)
			output_route(head->lc);
		if (head->rc != NULL)
			output_route(head->rc);
	}
}
void delete_node(node *head)
{
	if (head == NULL)
		return;
	delete_node(head->lc);
	delete_node(head->rc);
	delete head;

}
int main()
{
	string temp;
	while (cin >> temp)
	{
		int i = 0;
		node *head = pre_order_creat_tree(temp, i);
		if (head != NULL)
			head->pa = NULL;
		output_route(head);
		delete_node(head);
	}
	return 0;
}