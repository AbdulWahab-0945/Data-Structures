#include<iostream>
#include<fstream>
#include<queue>
#include<string>
#include<unordered_map>
using namespace std;

struct HNode
{

	int freq;
	char character;
	HNode*left, *right;

};



HNode* NodeGetter(char character, int freq, HNode*left, HNode*right)
{
	HNode*NewNode = new HNode();

	NewNode->character = character;  //assigning value to character
	NewNode->freq = freq;      // assigning the frequency to the node
	NewNode->left = left;      // assigning the value of left child to the node
	NewNode = right = right;   // assigning the value of right child to the node
	

	return NewNode;  // Node returned is used for a function later in the code.
}



void coding(HNode* root, string st1, unordered_map<char, string> & HUFFMAN)
{
	if (root == nullptr)   // base case for recursion. If root is null then return.
	{
		return;
	}

	if (!root->left && !root->right)
	{
		HUFFMAN[root->character] = st1;
	}

	coding(root->left, st1 + "0", HUFFMAN);  // if we move to left 0 is added. 
	coding(root->right, st1 + "1", HUFFMAN); // if we move to the right 1 is added.

}


struct compute
{
	bool operator()(HNode*Left, HNode*Right)   // this function checks which child has a higher frequency and returns it.
	{
		if (Left->freq > Right->freq)
		{
			return Left->freq;
		}

		else
			return Right->freq;
	}
};

void HuffmanDecode(HNode*root, int &in, string st1)
{
	if (root == nullptr)  // base case for recursion
	{
		return;
	}

	if (root->left == nullptr && root->right == nullptr)  // if there is no right or left child that mean a leaf node has been reached so there must a letter on that psoition.
	{
		cout << root->character;		// print the letter which is created by traversing till we reach the last node after which there are no children.
		return;
	}

	in++;		// by incrementing the index the value we can traverse the string

	if (st1[in] == '0')   // if there is a 0 in the string we will move to the left.
	{
		HuffmanDecode(root->left, in, st1);
	}
	else
	{
		HuffmanDecode(root->right, in, st1); // Since there is only 0 and 1, if it's not a zero we will move to the right child.
	}
}

void Print(string data)
{
	unordered_map<char, int> freq;
	for (char character : data)  // for loop which will keep running till there is text in the file
	{
		freq[character]++;
	}

	priority_queue<HNode*, vector<HNode*>, compute>PriorityQueue;    //Built in Priority Queue and vectors are used.
	for (auto PR : freq)
	{
		PriorityQueue.push(NodeGetter(PR.first, PR.second, nullptr, nullptr));  // getter fucntion is used which will return the node.
	}

	while (PriorityQueue.size() != 1)     // while loop which will keep running till the size of the queue is greater than 1
	{
		HNode*left = PriorityQueue.top();
		PriorityQueue.pop();  // till the size is greater than the queue will keep popping the top element.
		HNode*right = PriorityQueue.top();  
		PriorityQueue.pop();

		int s = left->freq + right->freq;   // s variable keeps record of the frequency of both the left child and the right child.

		PriorityQueue.push(NodeGetter('\0', s, left, right));
	}

	HNode * root = PriorityQueue.top(); // the root of the tree will be the top of the queue

	unordered_map<char, string> HUFFMAN;  // Builtin hashmap is used to store the values

	coding(root, "", HUFFMAN);  // function to convert data into huffman code is called.

	cout << "THE CODE IS " << endl;

	for (auto PR : HUFFMAN)  //for loop will run till the code ends.
	{
		cout << PR.first << " " << PR.second << endl;
	}

	string st = "";

	for (char character : data)  // for loop keeps running till there is data.
	{
		st += HUFFMAN[character];
	}

	cout << "AFTER ENCODING STRING IS : " << st << endl << endl;;
}


void fileAccess(string &data)
{
	ifstream readData("file.txt");
	getline(readData, data);
}


int main()
{
	string data;
	fileAccess(data);
	Print(data);
	return 0;
}