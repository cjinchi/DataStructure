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

node *insert_node_into_tree(int n, node *head);
//添加节点到二叉搜索树中，树初始状态为空；返回值是添加n之后指向树根的指针，可能与参数head不同
void preorder_output_tree(node *head, bool &is_first_item);
//前序遍历，同时释放空间；bool参数用于判断是否是输出队列中的第一个，以确定是否输出 空格
node *delete_item(node *head, int item);
//删掉节点item
int first_inorder_item(node *head);
//返回中序下的第一个节点，若树为空则返回-1
void remove_tree(node *head);
//释放树的空间

int main()
{
	int size_of_array;
	while (cin >> size_of_array)
	{
		//Get data
		int *arr = new int[size_of_array];
		for (int i = 0; i < size_of_array; i++)
			cin >> arr[i];
		int item_to_delete;
		cin >> item_to_delete;

		//Creat tree
		node *head = NULL;
		for (int i = 0; i < size_of_array; i++)
		{
			head = insert_node_into_tree(arr[i], head);
		}

		delete[]arr;

		//Output
		bool temp = true;
		preorder_output_tree(head, temp);
		cout << endl;

		//Delete item in tree
		head = delete_item(head, item_to_delete);

		//Output again
		temp = true;
		preorder_output_tree(head, temp);
		cout << endl;

		//Remove tree
		remove_tree(head);
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
void preorder_output_tree(node *head, bool &is_first_item)
{
	if (head == NULL)
		return;

	if (is_first_item)
		is_first_item = false;
	else
		cout << " ";
	cout << head->n;
	
	preorder_output_tree(head->lc, is_first_item);
	preorder_output_tree(head->rc, is_first_item);


}
node *delete_item(node *head, int item)
{
	if (head == NULL)
		return NULL;
	else if (head->n == item)
	{
		if (head->lc == NULL&&head->rc == NULL)				//a leaf
		{
			delete head;
			return NULL;
		}
		else if (head->lc == NULL)
		{
			node *rigth_child = head->rc;
			delete head;
			return rigth_child;
		}
		else if (head->rc == NULL)
		{
			node *left_child = head->lc;
			delete head;
			return left_child;
		}
		else
		{
			head->n = first_inorder_item(head->rc);
			head->rc=delete_item(head->rc, head->n);
			return head;
		}
	}
	else
	{
		head->lc = delete_item(head->lc, item);
		head->rc = delete_item(head->rc, item);
		return head;
	}
}
int first_inorder_item(node *head)
{
	if (head == NULL)
		return -1;

	if (head->lc == NULL)
		return head->n;
	else
		return first_inorder_item(head->lc);
}
void remove_tree(node *head)
{
	if (head == NULL)
		return;

	remove_tree(head->lc);
	remove_tree(head->rc);
	
	delete head;
}