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

void linkedListStack :: Push(listNode* newNode)
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
			line += "NULL)";
		else
		{
			line += std::to_string(ptr->next->data);
			line += ")";
		}
		ptr = ptr->next;
	}
	line += " -> NULL";
	
	return line;
}


class linkedListQueue
{
	public:
		listNode* head;
		listNode* tail;
		linkedListQueue();
		void addTail(linkedListQueue*, listNode*);
		listNode* deleteFront(linkedListQueue*);
		bool isEmpty(linkedListQueue*);
		void printQueue(int);
};







int main(int argc, char ** argv)
{
	return 0;
}
