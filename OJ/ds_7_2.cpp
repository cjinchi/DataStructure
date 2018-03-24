#include<iostream>
#include<string>
#include<sstream>
using namespace std;
struct node
{
	int n;
	node *lc;
	node *rc;
};
	
int *get_array_from_string(string line, int &size);
void sort(node *a[], int size);						//sort,from large to small
node *creat_huffman_tree(node *small, node *large);	//link small and large to a new tree
int wpl(node *head,int depth);						//get wpl

int main()
{
	string line;
	while (getline(cin, line))
	{
		int size = 0;	//size of array
		int *arr = get_array_from_string(line, size);
		node *(*head) = new node*[size];
		for (int i = 0; i < size; i++)
		{
			head[i] = new node;
			head[i]->n = arr[i];
			head[i]->lc = NULL;
			head[i]->rc = NULL;
		}
		delete[]arr;

		while (size > 1)
		{
			sort(head, size);
			head[size - 2] = creat_huffman_tree(head[size - 2], head[size - 1]);
			head[size - 1] = NULL;
			size--;
		}
		cout << wpl(head[0],0) << endl;
		delete[]head;

	}
}

int *get_array_from_string(string line, int &size)
{
	//copy numbers in line to arr
	int len = int(line.length());
	size = 0;
	for (int i = 0; i<len; i++)
	{
		if (line[i] == ' ')
			size++;
	}
	size++;
	int *arr = new int[size];

	//Copy number to arr
	stringstream x;
	x.clear();
	x.str("");

	x << line;
	int aindex = 0;			//index of array

	while (aindex<size)
	{
		x >> arr[aindex];
		aindex++;
	}

	x.clear();
	x.str("");
	return arr;
}

void sort(node *a[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int max = i;
		for (int j = i + 1; j < size; j++)
		{
			if (a[j]->n > a[max]->n)
				max = j;
		}
		if (max != i)
		{
			node *temp = a[max];
			a[max] = a[i];
			a[i] = temp;
		}
	}
}
node *creat_huffman_tree(node *small, node *large)
{
	node *link = new node;
	link->lc = small;
	link->rc = large;
	link->n = small->n + large->n;
	return link;
}
int wpl(node *head,int depth)
{
	if (head->lc == NULL&&head->rc == NULL)
	{
		int result= (head->n)*depth;
		delete head;
		return result;
	}
	int n=0;
	n += wpl(head->lc, depth + 1);
	n += wpl(head->rc, depth + 1);
	delete head;
	return n;
}