#include <iostream>
#include <string.h>
using namespace std;

struct Node{
	int data;
	Node *next;	
};

struct Stack{
	Node *head;
	void create();
	void close();
	void push(int);
	int pop();
	bool isempty();
};

void Stack::create(){
	head = NULL;
}
void Stack::close(){
	Node *p;
	while(head){
		p = head;
		head = head->next;
		delete p;
	}
}
void Stack::push(int newdata){
	Node *newnode = new Node;
	newnode->data = newdata;
	newnode->next = head;
	head = newnode;
}
int Stack::pop(){
	Node* topnode;
	int temp;
	topnode = head;
	head = head->next;
	temp = topnode->data;
	delete topnode;
	return temp;
}
bool Stack::isempty(){
	return head==NULL;
}

int main(){
	Stack s;
	s.create();
	s.push(5);
	s.push(7);
	int c=s.pop();
	cout<<c<<endl;
	c=s.pop();
	s.pop();
	s.close();
	return 0;
}
