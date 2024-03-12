#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
#include<string>
#include<conio.h>

using namespace std;

template<typename K, typename V>
class Node
{
public:

	K key;
	V value;
	Node * leftChild;
	Node * rightChild;




	Node()
	{
		this->leftChild = this->rightChild = nullptr;
	}

	Node(K key, V value)
	{
		this->key = key;
		this->value = value;
		this->leftChild = this->rightChild = nullptr;
	}

	bool isLeaf()
	{
		return !this->leftChild && !this->rightChild;
	}

};

template<typename K, typename V>
class SpecialBST
{
public:

	Node<K, V> * root;
	vector<V> traverse;

	vector<V> *InOrderPrint()
	{
		traverse.clear();
		InOrder(root);
		return &traverse;
	}

	vector<V> *LevelWisePrint()
	{
		traverse.clear();
		LevelOrder(root);
		return &traverse;
	}

	void InOrder(Node<K, V> * root)
	{
		if (root == nullptr)
		{
			return;
		}

		InOrder(root->leftChild);
		traverse.push_back(root->key);
		InOrder(root->rightChild);
	}

	void LevelOrder(Node<K, V> * root)
	{
		if (root == nullptr)
		{
			return;
		}
		queue<Node<K, V>*> Q;
		Q.push(root);
		while (!Q.empty())
		{
			Node<K, V> * front = Q.front();
			Q.pop();
			traverse.push_back(front->key);

			if (front->leftChild != nullptr)
				Q.push(front->leftChild);

			if (front->rightChild != nullptr)
				Q.push(front->rightChild);
		}
	}

	SpecialBST()
	{
		this->root = nullptr;
	}

	void insert(K key, V value, Node<K, V>*&  ptr)
	{
		if (ptr == nullptr)
		{
			ptr = new Node<K, V>(key, value);
		}
		else if (key < ptr->key)
		{
			insert(key, value, ptr->leftChild);
		}
		else if (key > ptr->key)
		{
			insert(key, value, ptr->rightChild);
		}
	}


	void PreOrderPrintKeys(Node<K, V>* ptr)
	{
		if (ptr)
		{
			cout << ptr->key << endl;
			PreOrderPrintKeys(ptr->leftChild);
			PreOrderPrintKeys(ptr->rightChild);
		}
	}





	void insert(K key, V value)
	{
		insert(key, value, this->root);
		this->root = search(root, key);
	}



	Node<K, V> * rightRotate(Node<K, V>  * x)
	{
		Node<K, V> * y = x->leftChild;
		x->leftChild = y->rightChild;
		y->rightChild = x;
		return y;
	}

	Node<K, V>*leftRotate(Node<K, V>*x)
	{
		Node<K, V>*y = x->rightChild;
		x->rightChild = y->leftChild;
		y->leftChild = x;
		return y;
	}

	Node <K, V>* MakeRoot(Node<K, V> * root, K key)
	{
		if (root == nullptr || root->key == key)
		{
			return root;
		}

		if (root->key > key)
		{
			if (root->leftChild == nullptr)
			{
				return root;
			}

			if (root->leftChild->key > key)
			{
				root->leftChild->leftChild = MakeRoot(root->leftChild->leftChild, key);
				root = rightRotate(root);
			}

			else if (root->leftChild->key < key)
			{
				root->leftChild->rightChild = MakeRoot(root->leftChild->rightChild, key);

				if (root->leftChild->rightChild != nullptr)
				{
					root->leftChild = leftRotate(root->leftChild);
				}
			}
			return (root->leftChild == nullptr) ? root : rightRotate(root);
		}
		else
		{
			if (root->rightChild == nullptr)
			{
				return root;
			}

			if (root->rightChild->key > key)
			{
				root->rightChild->leftChild = MakeRoot(root->rightChild->leftChild, key);

				if (root->rightChild->leftChild != nullptr)
					root->rightChild = rightRotate(root->rightChild);
			}

			else if (root->rightChild->key < key)
			{
				root->rightChild->rightChild = MakeRoot(root->rightChild->rightChild, key);
				root = leftRotate(root);
			}

			return (root->rightChild == nullptr) ? root : leftRotate(root);
		}
	}

	Node<K, V> * search(Node <K, V> * root, K key)
	{
		return MakeRoot(root, key);
	}




	void PreOrderPrintKeys()
	{
		PreOrderPrintKeys(this->root);
	}



	void delete_(K key, Node<K, V>* &ptr)
	{
		if (ptr == nullptr)
			return;
		else if (key < ptr->key)
		{
			delete_(key, ptr->leftChild);
		}
		else if (key > ptr->key)
		{
			delete_(key, ptr->rightChild);
		}
		else
		{
			//case 0: leaf node
			if (ptr->isLeaf())
			{
				delete ptr;
				ptr = nullptr;
			}
			//case 1.1: only left child exists
			else if (ptr->leftChild && !ptr->rightChild)
			{
				Node<K, V>* delNode = ptr;
				ptr = ptr->leftChild;
				delete delNode;
			}
			//case 1.2: only right child exists
			else if (!ptr->leftChild && ptr->rightChild)
			{
				Node<K, V>* delNode = ptr;
				ptr = ptr->rightChild;
				delete delNode;
			}
			//case 2: both children exits
			else
			{
				Node<K, V>* successor = ptr->rightChild;
				while (successor->leftChild)
					successor = successor->leftChild;

				ptr->key = successor->key;
				ptr->value = successor->value;
				delete_(successor->key, ptr->rightChild);
			}
		}
	}

	void delete_(K key)
	{
		delete_(key, this->root);
	}

	//friend class StudentList;

};

void VectorPrinting(vector<int> * traverse)
{
	for (int i = 0; i < traverse->size(); i++)
	{
		cout << traverse->at(i) << " ";
	}
	cout << endl;
}


template<typename K, typename V>
class StudentNode 
{
public:

	K FirstName;
	K LastName;
	K department;
	float CGPA;
	V batch;
	V rollNumber;


	StudentNode * next;
	StudentNode * previous;

};

template<typename K,typename V>

class StudentList : public SpecialBST<K,V>
{
	StudentNode <K, V> * head;
	StudentNode <K, V> * tail;
	int totalStudents;

public:

	StudentList()
	{
		this->head = this->tail = nullptr;
		totalStudents = 0;
	}

	bool isEmpty()
	{
		return !this->head;
	}



	void insert(K FirstName, K LastName, K department, float CGPA, V batch, V rollNumber)
	{

		if (isEmpty())
		{
			StudentNode<K,V>* newNode = new StudentNode<K,V>;
			cout << "Enter First Name of Student " << endl;
			cin >> FirstName;
			newNode->FirstName = FirstName;
			
			cout << "Enter Last Name of Student " << endl;
			cin >> LastName;
			newNode->LastName = LastName;
			
			cout << "Enter Student's Department " << endl;
			cin >> department;
			newNode->department = department;

			cout << "Enter Student's CGPA" << endl;
			cin >> CGPA;
			
			if (CGPA > 4 || CGPA < 0)
			{
				cout << "CGPA not acceptable " << endl;
				cin >> CGPA;
			}

			newNode->CGPA = CGPA;

			cout << "Enter Student's Batch " << endl;
			cin >> batch;
			newNode->batch = batch;

			cout << "Enter Student's Roll Number " << endl;
			cin >> rollNumber;
			newNode->rollNumber = rollNumber;
			
			
			newNode->next = nullptr;
			newNode->previous = nullptr;
			this->head = this->tail = newNode;
			totalStudents++;
		}
		else
		{
			StudentNode<K,V>* newNode = new StudentNode<K,V>;
			StudentNode<K, V>* check = head;
			cout << "Enter First Name of Student " << endl;
			cin >> FirstName;
			newNode->FirstName = FirstName;

			cout << "Enter Last Name of Student " << endl;
			cin >> LastName;
			newNode->LastName = LastName;

			cout << "Enter Student's Department " << endl;
			cin >> department;
			newNode->department = department;

			cout << "Enter Student's CGPA" << endl;
			
			cin >> CGPA;
			while (1)
			{
				if (CGPA < 0 || CGPA>4)
				{
					cout << "CGPA not acceptable " << endl;
					cout << "Enter it again " << endl;
					cin >> CGPA;
				}
				else
					break;
			}

			newNode->CGPA = CGPA;

			cout << "Enter Student's Batch " << endl;
			cin >> batch;
			newNode->batch = batch;

			cout << "Enter Student's Roll Number " << endl;
			cin >> rollNumber;
			while (check != nullptr)
			{
				if (check->rollNumber == rollNumber)
				{
					cout << "RollNumber Already Exists " << endl;
					cout << "Enter Roll Number Again " << endl;
					cin >> rollNumber;
					
				}
				check = check->next;
			}

			newNode->rollNumber = rollNumber;
			
			newNode->next = this->head;
			
			newNode->previous = nullptr;
			
			this->head->previous = newNode;
			
			this->head = newNode;
			
			totalStudents++;
		}
	}

	void Search(int RollNumber)
	{
		StudentNode<K, V> * temp = head;
		cout << "Enter Roll Number to Search " << endl;
		cin >> RollNumber;
		while (temp != nullptr)
		{
			if (temp->rollNumber == RollNumber)
			{
				cout << "Student's First name is: " << temp->FirstName << endl;
				cout << "Student's Last name is: " << temp->LastName << endl;
				cout << "Student's Department is: " << temp->department << endl;
				cout << "Student's CGPA is: " << temp->CGPA << endl;
				cout << "Student's batch is: " << temp->batch << endl;
				cout << "Student's Roll number is: " << temp->rollNumber << endl;
				cout << endl << endl;
				break;
			}
			temp = temp->next;
			
		}

		if (temp == nullptr)
		{
			cout << "No record Found " << endl;
		}
	}

	void UPDATE(int rollnumber)
	{
		StudentNode<K, V> * check = head;
		StudentNode<K, V> * temp = head;
		string FirstName;
		string LastName;
		string department;
		float CGPA = 0;
		int batch = 0;
		int rollNumber = 0;

		cout << "Enter Roll Number to Edit Details" << endl;
		cin >> rollnumber;

		while (temp != nullptr)
		{
			if (temp->rollNumber = rollnumber)
			{
				check = temp;
			}
			temp = temp->next;
		}

		cout << "Edit Student Details " << endl << endl;
		cout<<"First Name " << check->FirstName << endl;
		cout << "Last Name " << check->LastName << endl;
		cout << "Department " << check->department << endl;
		cout << "CGPA " << check->CGPA << endl;
		cout << "Batch " << check->batch << endl;
		cout << "Roll Number" << check->rollNumber << endl;

		cout << "ENTER NEW DETAILS IN THE SAME ORDER " << endl;
		cin >> FirstName;
		check->FirstName = FirstName;
		cin >> LastName;
		check->LastName = LastName;
		cin >> department;
		check->department = department;
		cin >> CGPA;
		check->CGPA = CGPA;
		cin >> batch;
		check->batch = batch;
		cin >> rollNumber;
		check->rollNumber = rollNumber;


	}

	void Print()
	{
		StudentNode<K,V> * temp = head;
		while (temp != nullptr)
		{
			cout << "Student's First name is: " << temp->FirstName << endl;
			cout << "Student's Last name is: " << temp->LastName << endl;
			cout << "Student's Department is: " << temp->department << endl;
			cout << "Student's CGPA is: " << temp->CGPA << endl;
			cout << "Student's batch is: " << temp->batch << endl;
			cout << "Student's Roll number is: " << temp->rollNumber << endl;

			cout << endl << endl;
			temp = temp->next;
		}
	}

	
	void DELETE(int rollNumber)
	{
		cout << "Enter Roll Number of Student to Delete From Record " << endl;
		cin >> rollNumber;

		StudentNode<K, V> * temp = head;
		StudentNode<K, V> * temp1 = head;

		while (temp1 != nullptr)
		{
			if (temp1->rollNumber == rollNumber)
			{
				temp = temp1;
				cout << endl;
				cout << "DETAILS OF STUDENT YOU WANT TO DELETE " << endl;
				cout << "---------------------------------------" << endl << endl;
				cout << "Student's First name is: " << temp->FirstName << endl;
				cout << "Student's Last name is: " << temp->LastName << endl;
				cout << "Student's Department is: " << temp->department << endl;
				cout << "Student's CGPA is: " << temp->CGPA << endl;
				cout << "Student's batch is: " << temp->batch << endl;
				cout << "Student's Roll number is: " << temp->rollNumber << endl;

				cout << endl << endl;
				break;
			}
			temp1 = temp1->next;
		}
		if (temp1 == nullptr)
		{
			cout << "Student not Found " << endl;
		}

		if (temp1 == head)
		{
			head = head->next;
			head->previous = nullptr;
			delete temp1;
		}

		else if (temp1 == tail)
		{
			tail = tail->previous;
			tail->next = nullptr;
			delete temp1;
		}

		else
		{
			StudentNode <K, V> * connection = temp1->next;
			connection->previous = temp1->previous;
			temp1->previous->next = connection;
			delete temp1;
		}

		
		
	}


};



int main()
{

	StudentList<string, int> b;
	
	string FirstName;
	string LastName;
	string department;
	float CGPA=0;
	int batch=0;
	int rollNumber=0;
	

	
	char key='\0';
	while (true)
	{
		cout << "Enter i to insert a new Student"<< endl;
		cout << "Enter d to delete a student " << endl;
		cout << "Enter s to search a student " << endl;
		cout << "Enter u to update a student by roll number" << endl;
		cout << "Enter p to print all students by roll number" << endl;
		cout << "Enter e to exit " << endl;
		
		cin >> key;
		

		if(key=='i')
		{
			b.insert(FirstName, LastName, department, CGPA, batch, rollNumber);
		}

		if (key == 'd')
		{
			b.DELETE(rollNumber);
		}

		if (key == 's')
		{
			b.Search(rollNumber);
		}

		if (key == 'u')
		{
			b.UPDATE(rollNumber);
		}

		if (key == 'p')
		{
			b.Print();
		}

	

		if (key == 'e')
		{
			break;
		}

	}



























	/*SpecialBST <int, int> a;
	a.insert(20, 1);
	a.insert(12, 2);
	a.insert(22, 3);
	a.insert(16, 4);
	a.insert(10, 5);*/

	
	
	/*vector<int> * traverse = a.LevelWisePrint();

	cout << "PRINTING VALUES LEVEL-WISE " << endl;
	
	VectorPrinting(a.LevelWisePrint());

	traverse = a.InOrderPrint();

	cout << "PRINTING VALUES IN-ORDER " << endl;
	VectorPrinting(a.InOrderPrint());
	
	cout << endl;*/

	
	
}

