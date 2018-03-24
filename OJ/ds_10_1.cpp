#include<iostream>
using namespace std;

#define max(a,b) (a>b?a:b)
#define fabs(a) (a>0?a:-a)

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
int height_of_tree(node *head);
//返回树的高度
bool is_AVL(node *head);
//判断一棵二叉搜索树是否是AVL树
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

		//Creat tree
		node *head = NULL;
		for (int i = 0; i < size_of_array; i++)
		{
			head = insert_node_into_tree(arr[i], head);
		}

		delete[]arr;

		//Judge AVL
		if (is_AVL(head))
			cout << "True" << endl;
		else
			cout << "False" << endl;
			

		//Remove tree
		remove_tree(head);
	}
	return 0;
}

//Func
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
int height_of_tree(node *head)
{
	if (head == NULL)
		return 0;
	else
	{
		int height_of_leftchild = height_of_tree(head->lc);
		int height_of_rightchild = height_of_tree(head->rc);
		return max(height_of_leftchild, height_of_rightchild) + 1;
	}
}
bool is_AVL(node *head)
{
	if (head == NULL)							//CASE ONE
	{
		return true;								
	}
	else 
	{
		int height_of_lc = height_of_tree(head->lc);
		int height_of_rc = height_of_tree(head->rc);
		if ((fabs(height_of_lc - height_of_rc) < 2) &&
			is_AVL(head->lc) &&
			is_AVL(head->rc))					//CASE TWO
		{
			return true;
		}
		else
			return false;
	}
}
void remove_tree(node *head)
{
	if (head == NULL)
		return;

	remove_tree(head->lc);
	remove_tree(head->rc);

	delete head;
}