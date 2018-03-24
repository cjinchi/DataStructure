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

/*��������*/
node *insert_node_into_tree(int n, node *head, node *parent,node *&the_new_node);
//��ӽڵ㵽���У�����ʼ״̬Ϊ�գ�����ֵ�����n֮��ָ��������ָ�룬���������head��ͬ
void set_bf(node *head);
//������headΪ���ڵ�����ĵ�ǰ״̬���������нڵ��bf
void preorder_output_tree(node *head, bool &is_first_item);
//ǰ�������ͬʱ�ͷſռ䣻bool���������ж��Ƿ�����������еĵ�һ������ȷ���Ƿ���� �ո�
void remove_tree(node *head);
//�ͷŽ��ռ�



/*����ƽ�⻯��ת*/
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
			//����½ڵ㣬����the_new_nodeָ��ָ���½ڵ�
			node *the_new_node = NULL;
			head = insert_node_into_tree(arr[i], head,NULL,the_new_node);

			//��������bf
			set_bf(head);
			
			//���½ڵ�����ѭ�����ж��Ƿ���Ҫƽ�⻯��ת
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
							//record�����ݴ�parent������ת�����������µĸ��ڵ�parent��ָ��record
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
		//�������Ѵ��ڵ����
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
			if (num <=( temp->bf))		//temp����һ����Ů�ĽǶȿ����ߣ�ѭ����ֹ
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
	Step_one:���������нڵ��bf��գ�����Ϊ-1��ͨ���ݹ�ʵ�֣�
	Step_two:������Ҷ�ڵ�����ڵ㷽���������߶ȣ��ݴ���bf��
	Step_three:�������£�����ڵ������bf.
	*/
	step_one(head);
	step_two(head);
	step_three(head);
}