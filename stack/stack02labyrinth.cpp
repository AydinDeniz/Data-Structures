#include <iostream>
using namespace std;

#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4

typedef struct d{
	int x;
	int y;
	int right;
	int left;
	int down;
	int up;
	int camefrom;
}StackDataType,position;

struct Node{
	StackDataType data;
	Node *next;
};

struct Stack{
	Node *head;
	void create();
	void close();
	void push(StackDataType);
	StackDataType pop();
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
void Stack::push(StackDataType newdata){
	Node *newnode = new Node;
	newnode->data = newdata;
	newnode->next = head;
	head = newnode;
}
StackDataType Stack::pop(){
	Node* topnode;
	StackDataType temp;
	topnode = head;
	head = head->next;
	temp = topnode->data;
	delete topnode;
	return temp;
}
bool Stack::isempty(){
	return head==NULL;
}

void printlab(char l[8][8]) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++){
			cout<<l[i][j];
		}
		cout<<endl;
	}
	cout<<endl;
}

int main(){
	char lab[8][8]={{'x','x','x','x','x','x','x','x'},
					{' ',' ','x','x','x',' ',' ',' '},
					{'x',' ','x','x','x',' ','x','x'},
					{'x',' ',' ',' ',' ',' ',' ','x'},
					{'x',' ','x',' ','x','x',' ','x'},
					{'x',' ','x','x',' ','x',' ','x'},
					{'x',' ',' ','x',' ',' ',' ','x'},
					{'x','x','x','x','x','x','x','x'}};	
	Stack s;
	s.create();
	position entrance={0,1,0,0,0,0,0};
	position exit={7,1,0,0,0,0,0};
	position p = entrance;
	p.camefrom=LEFT;
	printlab(lab);
	bool goback=false;
	
	while(p.x != exit.x || p.y != exit.y){
		lab[p.y][p.x] = 'o';
		printlab(lab);
		if(!goback){
			p.right = 0;
			p.left = 0;
			p.down = 0;
			p.up = 0;
			if(p.x < 7 && lab[p.y][p.x+1]!='x')
				p.right = 1;
			if(p.x > 0 && lab[p.y][p.x-1]!='x')
				p.left = 1;
			if(p.y < 7 && lab[p.y+1][p.x]!='x')
				p.down = 1;
			if(p.y > 0 && lab[p.y-1][p.x]!='x')
				p.up = 1;
		}
		else{
			goback = false;
		}

		
		bool moved = true;
		position past=p;
		if(p.right && p.camefrom != RIGHT)
			{p.x++;p.camefrom=LEFT;past.right=0;}
		else if(p.down && p.camefrom != DOWN)
			{p.y++;p.camefrom=UP;past.down=0;}
		else if(p.up && p.camefrom != UP)
			{p.y--;p.camefrom=DOWN;past.up=0;}
		else if (p.left && p.camefrom != LEFT)
			{p.x--;p.camefrom=RIGHT;past.left=0;}
		else moved = false;
		
		if(p.x!=exit.x|| p.y!=exit.y){
			if((p.down+p.up+p.right+p.left)>2){
				s.push(past);
			}
			if(!moved){
				if(!s.isempty()){
					p =s.pop();
					goback =true;
				}
			}
		}	
	}
	lab[p.y][p.x]='o';
	printlab(lab);
	cout<<"end"<<endl;
	s.close();
	
	return 0;
}

