#include<iostream>
using namespace std;

struct node
{
	int n;
	node *lc;
	node *rc;

	node(int data, node *init_lc = NULL, node *init_rc = NULL)
	{
		n = data;
		lc = init_lc;
		rc = init_rc;
	}
};

node *insert_node_into_tree(int n,node *head);		
//添加节点到二叉搜索树中，树初始状态为空；返回值是添加n之后指向树根的指针，可能与参数head不同	
void output_tree(node *head,bool &is_first_item);						
//右-根-左的形式遍历，同时释放空；bool参数用于判断是否是输出队列中的第一个，以确定是否输出 空格

int main()
{
	int size_of_array;
	while (cin >> size_of_array)
	{
		int *arr = new int[size_of_array];
		for (int i = 0; i < size_of_array; i++)
			cin >> arr[i];

		node *head = NULL;
		for (int i = 0; i < size_of_array; i++)
		{
			head = insert_node_into_tree(arr[i],head);
		}

		delete[]arr;

		bool temp = true;
		output_tree(head,temp);
		cout << endl;
	}
	return 0;
}

node *insert_node_into_tree(int n, node *head)
{
	if (head == NULL)
	{
		head = new node(n);
	}
	else
	{
		//不考虑已存在的情况
		if (n > (head->n))
			head->rc = insert_node_into_tree(n, head->rc);
		else
			head->lc = insert_node_into_tree(n, head->lc);
	}
	return head;
}
void output_tree(node *head, bool &is_first_item)
{
	if (head == NULL)
		return;

	output_tree(head->rc, is_first_item);

	if (is_first_item)
		is_first_item = false;
	else
		cout << " ";
	cout << head->n;

	output_tree(head->lc, is_first_item);
	delete head;
}