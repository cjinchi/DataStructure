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
//��ӽڵ㵽�����������У�����ʼ״̬Ϊ�գ�����ֵ�����n֮��ָ��������ָ�룬���������head��ͬ
void preorder_output_tree(node *head, bool &is_first_item);
//ǰ�������ͬʱ�ͷſռ䣻bool���������ж��Ƿ�����������еĵ�һ������ȷ���Ƿ���� �ո�
node *delete_item(node *head, int item);
//ɾ���ڵ�item
int first_inorder_item(node *head);
//���������µĵ�һ���ڵ㣬����Ϊ���򷵻�-1
void remove_tree(node *head);
//�ͷ����Ŀռ�

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
		//�������Ѵ��ڵ����
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