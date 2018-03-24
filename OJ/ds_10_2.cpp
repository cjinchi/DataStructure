#include<iostream>
using namespace std;
struct node
{
	int n;
	int bf;
	node *lc;
	node *rc;
	node *parent;
	node(int data, node *p) { n = data; bf = 0; lc = NULL; rc = NULL; parent = p; }
};

/*主体流程*/
node *insert_node_into_tree(int n, node *head, node *parent,node *&the_new_node);
//添加节点到树中，树初始状态为空；返回值是添加n之后指向树根的指针，可能与参数head不同
void set_bf(node *head);
//根据以head为根节点的树的当前状态，重设所有节点的bf
void preorder_output_tree(node *head, bool &is_first_item);
//前序遍历，同时释放空间；bool参数用于判断是否是输出队列中的第一个，以确定是否输出 空格
void remove_tree(node *head);
//释放结点空间



/*四种平衡化旋转*/
void RotateL(node *&head);
void RotateR(node *&head);
void RotateLR(node *&head);
void RotateRL(node *&head);

int main()
{
	int size_of_array;
	while (cin >> size_of_array)
	{
		//Get data
		int *arr = new int[size_of_array];
		for (int i = 0; i < size_of_array; i++)
			cin >> arr[i];

		//Creat AVL tree
		node *head = NULL;
		for (int i = 0; i < size_of_array; i++)
		{
			//添加新节点，并用the_new_node指针指向新节点
			node *the_new_node = NULL;
			head = insert_node_into_tree(arr[i], head,NULL,the_new_node);

			//重新设置bf
			set_bf(head);
			
			//从新节点向上循环，判断是否需要平衡化旋转
			node *current = the_new_node->parent;
			while (current != NULL)
			{
				if (current->bf == 0)
					break;
				else if (current->bf == 1 || current->bf == -1)
					current = current->parent;
				else
				{
					if (current->bf == 2)
					{
						if (current->rc->bf == 1)
						{
							//record用于暂存parent，在旋转结束后将子树新的根节点parent域指向record
							node *record = current->parent;
							if (record == NULL)
							{
								RotateL(head);
								head->parent = NULL;
							}
							else if (record->lc == current)
							{
								RotateL(record->lc);
								record->lc->parent = record;
							}
							else
							{
								RotateL(record->rc);
								record->rc->parent = record;
							}


							
						}
						else
						{
							node *record = current->parent;
							if (record == NULL)
							{
								RotateRL(head);
								head->parent = NULL;
							}
							else if (record->lc == current)
							{
								RotateRL(record->lc);
								record->lc->parent = record;
							}
							else
							{
								RotateRL(record->rc);
								record->rc->parent = record;
							}
						}
					}
					else
					{
						if (current->lc->bf == -1)
						{
							node *record = current->parent;
							if (record == NULL)
							{
								RotateR(head);
								head->parent = NULL;
							}
							else if (record->lc == current)
							{
								RotateR(record->lc);
								record->lc->parent = record;
							}
							else
							{
								RotateR(record->rc);
								record->rc->parent = record;
							}
						}
						else
						{
							node *record = current->parent;
							if (record == NULL)
							{
								RotateLR(head);
								head->parent = NULL;
							}
							else if (record->lc == current)
							{
								RotateLR(record->lc);
								record->lc->parent = record;
							}
							else
							{
								RotateLR(record->rc);
								record->rc->parent = record;
							}
						}
					}
					break;
				}
			}

		}

		delete[]arr;

		//Print tree
		bool temp = true;
		preorder_output_tree(head, temp);
		cout << endl;

		//Remove tree
		remove_tree(head);
	}
	return 0;
}

node *insert_node_into_tree(int n, node *head,node *parent, node *&the_new_node)
{
	if (head == NULL)
	{
		head = new node(n,parent);
		the_new_node = head;
	}
	else
	{
		//不考虑已存在的情况
		if (n > (head->n))
			head->rc = insert_node_into_tree(n, head->rc,head, the_new_node);
		else
			head->lc = insert_node_into_tree(n, head->lc,head, the_new_node);
	}
	return head;
}

void RotateL(node *&head)
{
	node *temp1 = head;
	head = head->rc;

	temp1->rc = head->lc;
	if(temp1->rc !=NULL)
		temp1->rc->parent = temp1;

	head->lc = temp1;
	if(head->lc!=NULL)
		head->lc->parent = head;
	
	head->bf = 0;
	temp1->bf = 0;

	//head = head->parent;
}
void RotateR(node *&head)
{
	node *temp1 = head;
	head = head->lc;

	temp1->lc = head->rc;
	if(temp1->lc!=NULL)
		temp1->lc->parent = temp1;

	head->rc = temp1;
	if(head->rc!=NULL)
		head->rc->parent = head;

	head->bf = 0;
	temp1->bf = 0;

	//head = head->parent;
}
void RotateLR(node *&head)
{
	node *rt = head;
	node *lt = head->lc;
	
	head = lt->rc;
	lt->rc = head->lc;
	if(lt->rc!=NULL)
		lt->rc->parent = lt;

	head->lc = lt;
	if (head->lc != NULL)
		head->lc->parent = head;

	if (head->bf > 0)
		lt->bf = -1;
	else
		lt->bf = 0;

	rt->lc = head->rc;
	if(rt->lc!=NULL)
		rt->lc->parent = rt;
	head->rc = rt;
	if(head->rc!=NULL)
		head->rc->parent = head;

	if (head->bf == -1)
		rt->bf = 1;
	else
		rt->bf = 0;
	head->bf = 0;

	//head = head->parent;
}
void RotateRL(node *&head)
{
	node *lt = head;
	node *rt = head->rc;

	head = rt->lc;
	rt->lc = head->rc;
	if (rt->lc != NULL)
		rt->lc->parent = rt;

	head->rc = rt;
	if(head->rc!=NULL)
		head->rc->parent = head;

	if (head->bf < 0)
		lt->bf = 1;
	else
		lt->bf = 0;

	lt->rc = head->lc;
	if(lt->rc!=NULL)
		lt->rc->parent = lt;
	head->lc = lt;
	if (head->lc != NULL)
		head->lc->parent = head;

	if (head->bf == 1)
		lt->bf = -1;
	else
		lt->bf = 0;
	head->bf = 0;

	//head = head->parent;
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
void remove_tree(node *head)
{
	if (head == NULL)
		return;

	remove_tree(head->lc);
	remove_tree(head->rc);

	delete head;
}

void step_one(node *head)
{
	if (head == NULL)
		return;
	head->bf = -1;
	step_one(head->lc);
	step_one(head->rc);
}
void step_two(node *head)
{
	if (head == NULL)
		return;
	if (head->lc == NULL&&head->rc == NULL)	//is a leaf
	{
		node *temp = head;
		int num = 1;
		while (temp != NULL)
		{
			if (num <=( temp->bf))		//temp从另一个子女的角度看更高，循环中止
				break;
			temp->bf = num;
			num++;
			temp = temp->parent;
		}
	}
	else
	{
		step_two(head->lc);
		step_two(head->rc);
	}

}
void step_three(node *head)
{
	if (head == NULL)
		return;

	head->bf = (head->rc == NULL ? 0 : head->rc->bf) - (head->lc == NULL ? 0 : head->lc->bf);

	step_three(head->lc);
	step_three(head->rc);
	
}

void set_bf(node *head)
{
	/*
	Step_one:将树中所有节点的bf清空，设置为-1，通过递归实现；
	Step_two:从树的叶节点向根节点方向，逐个求其高度，暂存于bf域；
	Step_three:从上往下，逐个节点求得新bf.
	*/
	step_one(head);
	step_two(head);
	step_three(head);
}