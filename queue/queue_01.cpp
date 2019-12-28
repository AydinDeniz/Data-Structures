#include <iostream>
using namespace std;

typedef struct a{
	int x;
	int y;
	char name[10];
}QueueDataType;

struct Node{
	QueueDataType data;
	Node *next;
};

struct Queue{
	Node *front;
	Node *back;
	void create();
	void close();
	bool enqueue(QueueDataType);
	QueueDataType dequeue();
	bool isempty();
};

void Queue::create(){
	front = NULL;
	back = NULL;
}

void Queue::close(){
	Node *p;
	while(front){
		p = front;
		front = front->next;
		delete p;
	}
}

bool Queue::enqueue(QueueDataType newdata){
	Node *newnode = new Node;
	newnode->data = newdata;
	newnode->next = NULL;
	if(isempty()){
		back = newnode;
		front = back;
	}
	else if(!isempty()){
		back->next = newnode;
		back = newnode;
	}
}

QueueDataType Queue::dequeue(){
	Node *topnode;
	QueueDataType temp;
	topnode = front;
	front = front->next;
	temp = topnode->data;
	delete topnode;
	return temp;
}

bool Queue::isempty(){
	return front == NULL;
}

int main(){
	return 0;
}
