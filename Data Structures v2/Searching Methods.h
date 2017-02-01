#include<iostream>
#include <math.h>

using namespace std;

int comparisons;
/*************** Linear Search ***************/

int LinearSearch(vector<Hotel*> myHotel, int cond)
{
	bool found = false;

	for (int i = 0; i < myHotel.size(); i++)
	{
		comparisons++;
		if (myHotel[i]->id == cond)
		{
			found = true;
			return i;
		}
	}
	comparisons++;
	if (found == false)
		return -1;
}



/*************** Binary Search ***************/

int BinarySearch(vector<Hotel*> myHotel, int cond, int left, int right)
{
	comparisons++;
	if (left > right)
		return -1;
	else
	{
		int mid = (left + right) / 2;
		comparisons++;
		if (myHotel[mid]->id > cond)
			return BinarySearch(myHotel, cond, left, mid - 1);
		else if (myHotel[mid]->id < cond)
			return BinarySearch(myHotel, cond, mid + 1, right);
		else
			return mid;
	}
}



/*************** Interpolation Search ***************/

int InterpolationSearch(vector<Hotel*> myHotel, int cond)
{
	int left, right, mid;

	comparisons++;
	if ((cond >= myHotel[0]->id) && (cond <= myHotel[myHotel.size() - 1]->id))	
	{
		left = 0;
		right = myHotel.size() - 1;

		while ((myHotel[left]->id <= cond) && (myHotel[right]->id >= cond))
		{
			mid = left + ((cond - myHotel[left]->id) * (right - left)) / (myHotel[right]->id - myHotel[left]->id);
			comparisons++;
			//cout << mid << endl;
			if (myHotel[mid]->id < cond)
				left = mid + 1;
			else if (myHotel[mid]->id > cond)
				left = mid - 1;
			else
				return mid;
		}
		comparisons++;
		if (myHotel[left]->id == cond)
			return left;
		else
			return -1;
	}
	else
		return -1;
}



/*************** Digital Tree Search (TRIE) ***************/

int characterToIndex(char c)
{
	return (int)c - (int)'a';
}
int capitalToIndex(char c)
{
	return (int)c - (int)'A';
}

class TrieNode
{
public:
	vector<Reservation*> reserv;
	TrieNode* children[26];

	TrieNode()
	{
		for (int i = 0; i < 26; i++)
			children[i] = 0;
	}
};

class Trie
{
public:
	TrieNode *root;
	Trie()
	{
		root = new TrieNode();
	}

	~Trie()
	{}
	
	void insert(Reservation* myReserv, string key) 
	{
		int numberOfLetters = key.size();
		int level;
		int index;
		TrieNode *Inserted = this->root;
		for (level = 0; level < numberOfLetters; level++)
		{
			comparisons++;
			if (level == 0)
				index = capitalToIndex(key[level]);
			else
				index = characterToIndex(key[level]);

			comparisons++;
			if (!Inserted->children[index])
			{
				TrieNode *tmp = new TrieNode();
				Inserted->children[index] = tmp;
			}
			Inserted = Inserted->children[index];
		}
		Inserted->reserv.push_back(new Reservation());
		Inserted->reserv[Inserted->reserv.size() - 1] = myReserv;
	}


	bool search(string key)
	{
		bool found = false;
		int level;
		int numberOfLetters = key.size();
		int index;
		TrieNode* cond = this->root;
		for (level = 0; level < numberOfLetters; level++)
		{
			comparisons++;
			if (level == 0)
				index = capitalToIndex(key[level]);
			else
				index = characterToIndex(key[level]);

			comparisons++;
			if (!cond->children[index])
				return false;

			cond = cond->children[index];
		}
		
		for (int i = 0; i < cond->reserv.size(); i++)
		{
			//cout << cond->reserv[i]->name << " ";
			//cout << cond->reserv[i]->checkinDate << " ";
			//cout << cond->reserv[i]->stayDurationDays << endl;
			found = true;
		}
		return found;
	}
};



/*************** RED-BLACK Tree Search ***************/

struct node
{
	Hotel* hotelRB = new Hotel();
	node *parent;
	char color;
	node *left;
	node *right;
};

class RBtree
{
	node *root;
	node *q;
public:
	RBtree()
	{
		q = NULL;
		root = NULL;
	}
	void insert(Hotel* inVec)
	{
		node *p, *q;
		p = root;
		q = NULL;
		node *x = new node;
		x->hotelRB->id = inVec->id;
		x->hotelRB->name = inVec->name;
		x->left = NULL;
		x->right = NULL;
		x->color = 'r';

		comparisons++;
		if (root == NULL)
		{
			root = x;
			x->parent = NULL;
		}
		else
		{
			while (p != NULL)
			{
				q = p;
				comparisons++;
				if (p->hotelRB->id < x->hotelRB->id)
					p = p->right;
				else
					p = p->left;
			}
			x->parent = q;
			comparisons++;
			if (q->hotelRB->id < x->hotelRB->id)
				q->right = x;
			else
				q->left = x;
		}
		insertfix(x);
	}

	void insertfix(node *x)
	{
		comparisons++;
		if (x->parent != NULL && x->parent->parent != NULL)
		{
			while (x != NULL && x->parent != NULL && x->parent->parent != NULL && !x->parent->color == 'b') // ass long as color is not black, thus red
			{
				comparisons++;
				if (x->parent == x->parent->parent->left)
				{
					node *tmp = x->parent->parent->right;
					comparisons++;
					if (tmp != NULL && tmp->color == 'r')
					{
						x->parent->color = 'b';
						tmp->color = 'b';
						x->parent->parent->color = 'r';
						x = x->parent->parent;
					}
					else if (x == x->parent->right)
					{
						x = x->parent;
						leftrotate(x);
					}
					x->parent->color = 'b';
					x->parent->parent->color = 'r';
					rightrotate(x->parent->parent);
				}
				else
				{
					node *tmp = x->parent->parent->left; 
					comparisons++;
					if (tmp != NULL && tmp->color == 'r') 
					{
						x->parent->color = 'b'; 
						tmp->color = 'b';
						x->parent->parent->color = 'r'; 
						x = x->parent->parent;
					}
					else
					{
						comparisons++;
						if (x == x->parent->left) 
						{
							x = x->parent;
							rightrotate(x);
						}
						x->parent->color = 'b'; 
						x->parent->parent->color = 'r'; 
						leftrotate(x->parent->parent);
					}
				}
			}
		}
	}

	void leftrotate(node *p)
	{
		comparisons++;
		if (p->right == NULL)
			return;
		else
		{
			node *tmp = p->right;
			comparisons++;
			if (tmp->left != NULL)
			{
				p->right = tmp->left;
				tmp->left->parent = p;
			}
			else
				p->right = NULL;
			comparisons++;
			if (p->parent != NULL)
				tmp->parent = p->parent;
			comparisons++;
			if (p->parent == NULL)
				root = tmp;
			else
			{
				comparisons++;
				if (p == p->parent->left)
					p->parent->left = tmp;
				else
					p->parent->right = tmp;
			}
			tmp->left = p;
			p->parent = tmp;
		}
	}

	void rightrotate(node *p)
	{
		comparisons++;
		if (p->left == NULL)
			return;
		else
		{
			node *tmp = p->left;
			comparisons++;
			if (tmp->right != NULL)
			{
				p->left = tmp->right;
				tmp->right->parent = p;
			}
			else
				p->left = NULL;
			comparisons++;
			if (p->parent != NULL)
				tmp->parent = p->parent;
			comparisons++;
			if (p->parent == NULL)
				root = tmp;
			else
			{
				comparisons++;
				if (p == p->parent->left)
					p->parent->left = tmp;
				else
					p->parent->right = tmp;
			}
			tmp->right = p;
			p->parent = tmp;
		}
	}

	void search(int x)
	{
		comparisons++;
		if (root == NULL)
		{
			cout << "Empty Tree\n";
			return;
		}
		node *tmp = root;
		bool found = false;
		while (tmp != NULL && found == false)
		{
			comparisons++;
			if (tmp->hotelRB->id == x)
				found = true;
			comparisons++;
			if (found == false)
			{
				comparisons++;
				if (tmp->hotelRB->id < x)
					tmp = tmp->right;
				else
					tmp = tmp->left;
			}
		}
		comparisons++;
		if (found == false)
			cout << "ID didn't found\n";
		else
			cout << tmp->hotelRB->name << endl;
	}
};

