#include<iostream>
#include<string>
using namespace std;
struct node
{
	char n;
	node *lc;
	node *rc;
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
	return item;
}
void output_pre_order_tree(node *head)
{
	if (head == NULL)
	{
		cout << '@';
		return;
	}
	cout << head->n;
	output_pre_order_tree(head->lc);
	output_pre_order_tree(head->rc);
	delete head;
}
int number_of_leaves(node *head)
{
	if (head == NULL)
		return 0;

	int num = 0;
	num += number_of_leaves(head->lc);
	num += number_of_leaves(head->rc);
	if (num == 0)    //head doesn't have child,so it is a leaf
		return 1;
	else             //head is not a leaf
		return num;
}
void exchange_lc_rc(node *head)
{
	if (head == NULL)
		return;

	exchange_lc_rc(head->lc);
	exchange_lc_rc(head->rc);

	node *temp = head->lc;
	head->lc = head->rc;
	head->rc = temp;
}
int main()
{
	string temp;
	while (cin >> temp)
	{
		int i = 0;
		node *head = pre_order_creat_tree(temp, i);
		cout << number_of_leaves(head) << endl;
		exchange_lc_rc(head);
		output_pre_order_tree(head);		//delete here
		cout << endl;
	}
	return 0;
}