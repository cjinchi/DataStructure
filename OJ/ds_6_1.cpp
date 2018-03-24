#include<iostream>
#include<string>
using namespace std;
struct node
{
	char n;
	node *lc;
	node *rc;
};
node *pre_order_creat_tree(string temp,int& p)   //read from temp[p]
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
	return item;
}
void output_post_order_tree(node *head)
{
	if (head == NULL)
		return;
	output_post_order_tree(head->lc);
	output_post_order_tree(head->rc);
	cout << head->n;
	delete head;
}
int main()
{
	string temp;
	while (cin >> temp)
	{
		int i = 0;
		node *head = pre_order_creat_tree(temp, i);
		output_post_order_tree(head);
		cout << endl;
	}
	return 0;
}