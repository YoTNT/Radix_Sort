#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class listNode
{
	public:
		int data;
		listNode* next;
		listNode();
		listNode(int);
};

listNode :: listNode()
{
	data = -1;
	next = NULL;
}

listNode :: listNode(int d)
{
	data = d;
	next = NULL;
}


class linkedListStack
{
	public:
		listNode* top;
		linkedListStack();
		void Push(listNode*);
		listNode* Pop();
		bool isEmpty();
		string printStack();
};

linkedListStack :: linkedListStack()
{
	top = NULL;
}

void linkedListStack :: Push(listNode *newNode)
{
	newNode->next = this->top;
	this->top = newNode; 
}

listNode* linkedListStack :: Pop()
{
	listNode* temp = this->top;
	if(temp == NULL)
	{
		cout << "The stack is already empty!" << endl;
		return temp;
	}
	else
	{
		this->top = this->top->next;
		return temp;
	}
}

bool linkedListStack :: isEmpty()
{
	if(this->top == NULL)
		return true;
	else
		return false;
}

string linkedListStack :: printStack()
{
	string line = "Top -> ";
	listNode* ptr = this->top;
	while(ptr != NULL)
	{
		line += "(";
		line += std::to_string(ptr->data);
		line += ", ";
		if(ptr->next == NULL)
			line += "NULL) -> ";
		else
		{
			line += std::to_string(ptr->next->data);
			line += ") -> ";
		}
		ptr = ptr->next;
	}
	line += "NULL\r\n";
	
	return line;
}


class linkedListQueue
{
	public:
		listNode* head;
		listNode* tail;
		linkedListQueue();
		void addTail(linkedListQueue *, listNode *);
		listNode* deleteFront(linkedListQueue *);
		bool isEmpty(linkedListQueue *);
		string printQueue(int);
};

linkedListQueue :: linkedListQueue()
{
	listNode* dummy = new listNode();
	this->head = dummy;
	this->tail = dummy;
}

void linkedListQueue :: addTail(linkedListQueue *Q, listNode *node)
{
	Q->tail->next = node;
	Q->tail = Q->tail->next;
}

listNode* linkedListQueue :: deleteFront(linkedListQueue *Q)
{
	listNode * temp = Q->head->next;	//head always points to a dummy
	if(temp == NULL)
		cout << "The queue is already empty" << endl;
	else
		Q->head->next = Q->head->next->next;
	
	return temp;
}

bool linkedListQueue :: isEmpty(linkedListQueue *Q)
{
	if(Q->head == Q->tail)
		return 1;
	else
		return 0;
}

string linkedListQueue :: printQueue(int index)
{
	string line = "Front(";
	line += std::to_string(index);
	line += ") -> ";
	
	listNode* ptr = this->head->next;
	
	while(ptr != NULL)
	{
		line += "(";
		line += std::to_string(ptr->data);
		line += ", ";
		if(ptr->next == NULL)
			line += "NULL) -> ";
		else
		{
			line += std::to_string(ptr->next->data);
			line += ") -> ";
		}
		ptr = ptr->next;	
	}
	line += "NULL\r\n";

	line += "Tail(";
	line += std::to_string(index);
	line += ") -> ";
	ptr = this->tail;
	if(ptr == NULL)
		line += "NULL\r\n";
	else
	{
		line += "(";
		line += std::to_string(ptr->data);
		line += ", NULL) -> NULL\r\n";
	}

	return line;
}


void print_append(string content, string file_name)
{
	ofstream outFile(file_name, fstream::app);
	outFile << content;
	outFile.close();
}


class RadixSort
{
	public:
		int tableSize;
		linkedListQueue* hashTable[2][10];
		int data;
		int currentTable;
		int previousTable;
		int maxDigits;
		int currentDigit;

		listNode* loadStack(string, string);
		void dumpStack(listNode *, int, int, string);
		// tableIndex()
		int getMaxDigits();
		int getDigit(listNode *, int);
		int hashIndex(int);
		RadixSort();
		string printTable(int);
		void sort();
};

RadixSort :: RadixSort()
{
	tableSize = 10;
	data = -1;
	currentTable = 0;
	previousTable = 1;
	maxDigits = -1;
	currentDigit = 0;

	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 10; j++)
		{
			linkedListQueue* temp = new linkedListQueue();
			hashTable[i][j] = temp;
		}
}

listNode* RadixSort :: loadStack(string in_file_name, string out_file_name)
{
	linkedListStack* s = new linkedListStack();
	int largestNum = 0;

	string word;
	ifstream inFile;
	inFile.open(in_file_name);

	while(inFile >> word)
	{
		this->data = atoi(word.c_str());
		if(data > largestNum)
			largestNum = this->data;

		listNode* newNode = new listNode(data);
		s->Push(newNode);
	}
	string header = "*** Below is the constructed stack ***\r\n";
	print_append(header, out_file_name);
	print_append(s->printStack(), out_file_name);

	inFile.close();

	//Renew the maxDigits
	int d = 0;
	while(largestNum > 0)
	{
		largestNum /= 10;
		d++;
	}
	this->maxDigits = d;
	cout << "maxDigits: " << d << endl;

	return s->top;
}

int RadixSort :: getMaxDigits()
{
	return this->maxDigits;
}

int RadixSort :: getDigit(listNode *node, int currentDigit)
{
	int d = node->data;
	for(int i =0; i < currentDigit; i++)
		d /= 10;
	return d % 10;
}

int RadixSort :: hashIndex(int d)
{
	return d % 10;
}

string RadixSort :: printTable(int tableIndex)
{
	string line = "";

	for(int i = 0; i < this->tableSize; i++)
	{
		if(this->hashTable[tableIndex][i]->isEmpty(this->hashTable[tableIndex][i]))
			continue;
		else
			line += this->hashTable[tableIndex][i]->printQueue(i);
	}

	return line;
}


void RadixSort :: dumpStack(listNode *Top, int curDigit, int curTable, string output_file_name)
{
	listNode* ptr = Top;
	int digit;
	int index;
	while(ptr != NULL)
	{
		digit = this->getDigit(ptr, curDigit);
		index = hashIndex(digit);
		listNode* node = new listNode(ptr->data);
		this->hashTable[curTable][index]
			->addTail(hashTable[curTable][index], node);
		ptr = ptr->next;
	}

	//Print the non-empty queues
	string line = this->printTable(curTable);
	print_append(line, output_file_name);
}

//Sorting the numbers
//Default conditions:
//	currentDigit = 0
//	currentTable = 0
//	previousTable = 1
//	hashTable[0] is sorted by 1st digit
//	hashTable[1] is empty
void RadixSort :: sort()
{
	for(; this->currentDigit < this->maxDigits; this->currentDigit++)
	{
		//Swapping the working hashTable
		int tempTableIndex = this->currentTable;
		this->currentTable = this->previousTable;
		this->previousTable = tempTableIndex;


	}
}




int main(int argc, char ** argv)
{
	string in_file = argv[1];
	string out_file1 = argv[2];
	string out_file2 = argv[3];
	//Cleaning up the content
	ofstream outputFile1(out_file1, ifstream::trunc);
	ofstream outputFile2(out_file2, ifstream::trunc);
	outputFile1.close();
	outputFile2.close();

	RadixSort* R = new RadixSort() ;
	listNode* Top;
	Top = R->loadStack(in_file, out_file2);
	R->dumpStack(Top, R->currentDigit, R->currentTable, out_file2);

	return 0;
}
