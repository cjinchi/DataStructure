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
//��ӽڵ㵽�����������У�����ʼ״̬Ϊ�գ�����ֵ�����n֮��ָ��������ָ�룬���������head��ͬ	
void output_tree(node *head,bool &is_first_item);						
//��-��-�����ʽ������ͬʱ�ͷſգ�bool���������ж��Ƿ�����������еĵ�һ������ȷ���Ƿ���� �ո�

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
		//�������Ѵ��ڵ����
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