#include<iostream>
#include"fstream"
#include<string>
#include<string.h>
#include<cstring>
#include<cstdlib>
#include<sstream>
#include<time.h>

#pragma warning(disable : 4996)

using namespace std;

class StudentBST;
//template <class T>

class BSTNode {
	friend class StudentBST;
private:


	int ID;
	int length;
	string URL[300];
	string keywords;
	BSTNode *left;
	BSTNode *right;
	int height;

public:
	BSTNode()
	{

		this->left = NULL;
		this->right = NULL;

	}

	int getHeight()
	{
		return height;
	}

	void setHeight(int h)
	{
		height = h;
	}


	int getID()
	{
		return ID;
	}
	
	void setID(int r)
	{
		ID = r;
	}

	void getURL()
	{
		cout << length << " result(s) found: " << endl;
		for (int i = 0; i < length; i++)
		{

			cout << i + 1 << ") " << URL[i];
			cout << endl;

		}
	}
	
	void setURL(string r)
	{
		bool a = true;

		for (int i = 0; i < length && (a); i++)
		{
			if (URL[i] == r)
			{
				a = false;
			}
		}

		if (a)
		{
			URL[length] = r;
			length++;
		}

	}

	string getKeywords()
	{
		return keywords;
	}
	
	void setKeyword(string r)
	{
		keywords = r;
	}

	BSTNode* getLeft()
	{
		return left;
	}

	void setLeft(BSTNode* left)
	{
		this->left = left;
	}

	BSTNode* getRight()
	{
		return right;
	}

	void setRight(BSTNode* right)
	{
		this->right = right;
	}

	int isLeaf()
	{
		if (this->left == NULL && this->right == NULL)
		{
			return 1;
		}
		return 0;
	}
};


class StudentBST {

private:
	BSTNode*root;

	void inorder(BSTNode*s, string rn)
	{
		if (s != NULL)
		{
			inorder(s->getLeft(), rn);


			search(rn, s);
			inorder(s->getRight(), rn);
		}
	}

public:

	StudentBST()
	{
		this->root = NULL;

	}


	bool checkequal(string s1, string s2)
	{
		int x = s1.compare(s2);
		if (x != 0)
		{
			return false;
		}
		else { return true; }

	}
	
	bool checkgreater(string s1, string s2)
	{

		int x = s1.compare(s2);



		if (x > 0)
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	bool checklesser(string s1, string s2)
	{

		int x = s1.compare(s2);



		if (x < 0)
		{
			return true;
		}

		else
		{
			return false;
		}
	}


	void insert(string word, string url, int i)
	{
		BSTNode * node = new BSTNode();
		BSTNode *p, *q;
		p = q = root;

		node->setKeyword(word);
		node->setURL(url);
		node->setID(i);

		if (root == NULL)
		{
			root = node;
			root->setLeft(NULL);
			root->setRight(NULL);
			//return true;
		}
		else {

			while (checkequal(word, p->getKeywords()) == false && q != NULL)
			{
				p = q;

				if (checklesser(word, p->getKeywords()))
					q = p->getLeft();
				else
					q = p->getRight();
			}


			if (checkequal(word, p->getKeywords()))
			{
				p->setURL(url);
				delete node;

			}

			else if (checklesser(word, p->getKeywords()))
			{
				p->setLeft(node);
				//return true;
			}
			else
			{
				p->setRight(node);
				//	return true;
			}

		}









	}


	BSTNode* avlInsert(BSTNode* root, string keyword)
	{
		if (keyword > root->getKeywords())
		{
			root->setRight(avlInsert(root->getRight(), keyword));

			int leveldifference = height(root->getRight()) - height(root->getLeft());
			
			if (leveldifference == 2)
			
				if (keyword < root->getRight()->getKeywords())
				
					root = RightLeftRotate(root);
				else
					root = RotateLeft(root);
		}

		else if (keyword < root->getKeywords())

		{
			root->setLeft(avlInsert(root->getLeft(), keyword));
			
			int leveldifference = height(root->getLeft()) - height(root->getRight());
			
			if (leveldifference == 2)
			
				if (keyword > root->getLeft()->getKeywords())
				
					root = LeftRightRotate(root);
				else
					root = RotateRight(root);

		}




		int len = Maximum(height(root->getRight()), height(root->getLeft()));
		root->setHeight(1 + len);
		return root;
	}



	void avlInsert(string keyword, string link)
	{

		root = avlInsert(root, keyword);
	}


	int height(BSTNode*s)
	{
		if (s == NULL)
		{
			return -1;

		}
		else { return s->getHeight(); }
	}


	BSTNode * RotateRight(BSTNode *s)
	{

		if (s != NULL) {
			BSTNode*a = s->getLeft();

			s->setLeft(a->getRight());

			a->setRight(s);

			int len = Maximum(height(s->getRight()), height(s->getLeft()));

			s->setHeight(len + 1);


			int len2 = Maximum(height(a->getRight()), height(a->getLeft()));

			a->setHeight(len2 + 1);


			return a;
		}
		else
		{
			return NULL;
		}


	}


	BSTNode * RotateLeft(BSTNode *s)
	{


		if (s != NULL) {
			BSTNode*a = s->getRight();

			s->setRight(a->getLeft());

			a->setLeft(s);

			int len = Maximum(height(s->getRight()), height(s->getLeft()));

			s->setHeight(len + 1);


			int len2 = Maximum(height(a->getRight()), height(a->getLeft()));

			a->setHeight(len2 + 1);


			return a;
		}


		else
		{
			return NULL;
		}


	}



	BSTNode* LeftRightRotate(BSTNode* x)
	{

		x->setLeft(RotateLeft(x->getLeft()));

		return RotateRight(x);
	}


	BSTNode* RightLeftRotate(BSTNode* x)
	{

		x->setRight(RotateRight(x->getRight()));

		return RotateLeft(x);
	}


	int Maximum(int a, int b)
	{

		if (a > b)
		{
			return a;
		}

		else { return b; }
	}

	bool search(string rn, BSTNode*s)
	{

		if (checkequal(rn, s->getKeywords()))
		{


			s->getURL();
			
		}
		return true;

		



	}


	void inorder(string rn)
	{
		inorder(root, rn);
	}


};





int main()
{

	string file;
	cout << "Please enter filename:" << endl;
	cin >> file;
	cout << endl;
	ifstream filen;
	filen.open(file);

	StudentBST b;





	//filen.open("Assignment_data.txt");

	string id[100];
	string link[100];
	string words[100];
	int Identity = 0;
	int i = 0;
	int j = 0;

	clock_t start, end;

	start = clock();

	while (!filen.eof()) {



		getline(filen, id[i], ' ');

		getline(filen, link[i]);

		getline(filen, words[i]);
		string m = words[i];








		string j[100];
		istringstream iss(m);
		string word;
		int f = 0;
		while (iss >> word) {


			j[f] = word.c_str();
			f++;

		}
		for (int m = 0; m < f; m++)
		{

			b.insert(j[m], link[i], Identity);
			b.avlInsert(j[m], link[i]);
		}






		i++;
	}

	end = clock();

	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	cout << "File loaded into BST successfully.53 URLs loaded. " << "Time taken by program is: " << fixed << time_taken;
	cout << " sec" << endl << endl;
	

	while (1)
	{
		cout << " Search a word or press '0' to quit search engine " << endl;


		string sear;

		
		cin >> sear;
		if (sear == "0")
		{
			break;
		}

		cout << endl;
		clock_t start1, end1;
		start1 = clock();

		b.inorder(sear);

		end1 = clock();
		double TimeTaken = double(end1 - start1) / double(CLOCKS_PER_SEC);
		cout << "Time taken is " << fixed << TimeTaken << " sec " << endl;
	}
	system("PAUSE");
	return 0;
}

