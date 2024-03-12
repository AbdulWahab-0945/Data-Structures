#include<iostream>
using namespace std;

template <typename T>
class Node
{
public:
	T data;
	Node<T> * next;
};

template <typename T>
class SortedSet
{
private:
	
	void DeleteAtHead()
	{
		Node<T>* NewNode = new Node<T>;
		NewNode = head;
		head = head->next;
		delete NewNode;
		TotalElements--;
	}

	void DeleteAtTail()
	{
		Node<T>* NewNode = new Node<T>;
		NewNode = head;
		while (NewNode->next != tail)
		{
			NewNode = NewNode->next;
		}
		tail = NewNode;
		NewNode = NewNode->next;
		delete NewNode;
		tail->next = nullptr;
		TotalElements--;
	}

	bool Repetition(T data)
	{
		if (isEmpty() == false)
		{
			Node<T> * temp = head;
			while (temp != nullptr)
			{
				if (temp->data == data)
				{
					cout << "Repetition Not Allowed " << endl;
					return true;

				}
				else
				{
					return false;
				}
				temp = temp->next;
			}


		}

	}

	bool isEmpty()
	{
		if (head == nullptr && tail == nullptr)
		{
			return true;
		}
		else
			return false;
	}

	void InsertAtHead(T data)
	{
		if (isEmpty() == true)
		{

			Node<T>* NewNode = new Node<T>;
			this->head = this->tail = NewNode;
			NewNode->data = data;   // head->data=data;
			NewNode->next = nullptr;
			TotalElements++;
		}

		else
		{
			Node<T>* NewNode = new Node<T>;
			NewNode->data = data;
			NewNode->next = this->head;
			this->head = NewNode;
			TotalElements++;
		}
	}

	void InsertAtTail(T data)
	{
		if (isEmpty() == true)
		{
			InsertAtHead(data);
		}

		else
		{
			Node<T> * NewNode = new Node<T>;
			NewNode->data = data;
			tail->next = NewNode;
			tail = NewNode;
			NewNode->next = nullptr;
			TotalElements++;
		}
	}

public:

	Node<T> * head;
	Node<T> * tail;
	int TotalElements;

	SortedSet()
	{
		this->head = nullptr;
		this->tail = nullptr;
		TotalElements = 0;
	}


	void insert(T data)
	{

		if (isEmpty() == true)
		{
			Node<T> * NewNode = new Node<T>;

			head = tail = NewNode;
			NewNode->data = data;
			NewNode->next = nullptr;
			TotalElements++;
		}
		else
		{
			Node<T> * NewNode = new Node<T>;
			Node<T> * temp = head;
			Node<T>*temp1 = head;

			if (Repetition(data) == false)
			{
				while (temp != nullptr)
				{

					if (temp->data > data && TotalElements == 1)
					{
						InsertAtHead(data);
						//cout << head->data << endl;    //----------------------------
						break;
					}
					temp = temp->next;
				}
				while (temp1->next != nullptr)
				{
					if (temp1->data > data &&  TotalElements == 2 && temp1->next->data > data)
					{

						NewNode->data = data;
						NewNode->next = temp1;
						TotalElements++;
						break;

					}
					else if (temp1->data > data && TotalElements > 1 && temp1->next->data < data)
					{
						NewNode->data = data;
						NewNode->next = temp1;
						TotalElements++;
						break;
					}

					temp1 = temp1->next;

				}



				temp = head;
				while (temp != nullptr)
				{
					if (temp->data < data && temp->next == nullptr)
					{
						NewNode->data = data;
						temp->next = NewNode;
						NewNode->next = nullptr;
						tail = NewNode;
						TotalElements++;
						break;
					}

					else if (temp->data < data && (temp->next->data > data))
					{
						NewNode->data = data;
						NewNode->next = temp->next;
						temp->next = NewNode;
						TotalElements++;
						//cout << "HEAD " << head->data;
						//Print();  //-----------------
					}
					temp = temp->next;
				}

			}
		}

	}

	void Delete(int const index)
	{
		Node<T>* NewNode = new Node<T>;
		Node<T>* DelPointer = new Node<T>;
		NewNode = head;

		if (index == 1)
		{
			DeleteAtHead();
		}

		if (index == TotalElements)
		{
			DeleteAtTail();
		}
		else
		{
			for (int i = 1; i < index - 1; i++)
			{
				NewNode = NewNode->next;
			}

			DelPointer = NewNode->next;
			NewNode->next = DelPointer->next;
			delete DelPointer;
		}

	}

	void Union(SortedSet<T> const & OtherSet)
	{

		Node<T> * temp1 = head;
		SortedSet <T> Set;
		Set.head = head;
		
		Node<T> * temp2 = OtherSet.head;

		while (temp2 != nullptr)
		{
			
				Set.insert(temp2->data);
				temp2 = temp2->next;
		}

		

	}

	void Intersection(SortedSet<T> const & OtherSet)
	{
		Node<T> * temp1 = head;
		SortedSet <T> Set;
		Set.head = head;
		Node<T> * temp2 = OtherSet.head;
		SortedSet<T> a;
		
		while (temp1 != nullptr)
		{
			temp2 = OtherSet.head;
			while (temp2 != nullptr)
			{
				if (temp1->data == temp2->data)
				{
					Node<T> * NewNode = new Node<T>;
					a.insert(temp2->data);
					
				}
				temp2 = temp2->next;
			}
			temp1 = temp1->next;
		}

		Node<T> * temp3 = a.head;

		Set.head = a.head;
		while (temp3 != nullptr)
		{
			cout << temp3->data <<" ";
			temp3 = temp3->next;
		}
		cout << endl;

	}

	void Print()
	{
		Node<T> * temp = new Node<T>;
		temp = head;
		while (temp != nullptr)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;

	}

};








int main()
{
	SortedSet<int> a;

	a.insert(1);
	a.insert(20);
	a.insert(2);
	a.insert(100);
	
	
	
	SortedSet<int> b;
	b.insert(100);
	b.insert(2);
	b.insert(4);
	b.insert(20);

	int input = 0;

	cout << "Press 1 for Union of both lists " << endl;
	cout << "Press 2 for Intersection of both lists" << endl;
	cout << "Press 3 for Printing " << endl;
	cout << "Press 4 for Printing second list" << endl;
	cout << "Press 5 to Delete number from first list" << endl;
	cout << "Press 6 to Delete number from second List" << endl;
	cout << "Press 7 to quit " << endl;

	while (1)
	{

		cin >> input;
		cout << endl;
		if (input == 1)
		{
			a.Union(b);
		}
		else if (input == 2)
		{
			a.Intersection(b);
		}

		else if (input == 3)
		{
			a.Print();
		}

		else if (input == 4)
		{
			b.Print();
		}

		else if (input == 5)
		{
			int index = 0;
			cout << "Enter Index Number " << endl;
			cin >> index;
			a.Delete(index);
		}

		else if (input == 6)
		{
			int index = 0;
			cout << "Enter Index Number " << endl;
			cin >> index;
			b.Delete(index);
		}
		else if (input == 7)
		{
			break;
		}
	}

	return 0;
	
	
	
}