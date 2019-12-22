/* @Author

Student Name : Deniz Aydýn

Student ID : 150180036

Date : 22.10.2019 */

#include <iostream>
#include <fstream>
using namespace std;

struct node {
    int size;
    int quant;
    node *next = NULL;
};

struct stock {
    node *head = NULL;
    void create() {
		this->head = new node;
	}
    void add_stock(int);
    void sell(int);
    void current_stock();
    void clear();
};

void stock::add_stock(int s){
    if(!(this->head)) { 
                this->create(); 
                this->head->size = s;
                this->head->quant = 1;
				this->head->next  = NULL;
            }
    else if(this->head->size > s) {
		node* temp = new node;
		temp->size = s;
		temp->quant = 1;
		temp->next = this->head;
		this->head = temp;
	}
    else { 
        node* nodeptr = this->head;
        int counter=0;
        while(nodeptr->size < s){
            nodeptr = nodeptr->next;
            ++counter;
            if(nodeptr==NULL)
				break;
        }
        
        if(nodeptr==NULL) {
			nodeptr = this->head;
            for(int i = counter;i>1;--i) {
				nodeptr = nodeptr->next;
			}
			nodeptr->next = new node;
			nodeptr->next->size = s;
			nodeptr->next->quant = 1;
			nodeptr->next->next = NULL;
		}
            
        else if(nodeptr->size == s) {
			nodeptr->quant += 1;
		}
            
        else {
            nodeptr = this->head;
            for(int i =counter;i>1;i--) {
				nodeptr = nodeptr->next;
			}
			node* temp = new node;
			temp->size = s;
			temp->quant = 1;
			temp->next = nodeptr->next;
			nodeptr->next = temp;
        }
    }
}

void stock::sell(int s) {
    node* nodeptr = this->head;
    int counter = 0; 
    while(1) { 
		if(nodeptr==NULL){
			break;
		}
        if(nodeptr->size==s){
            nodeptr->quant--;
            if(nodeptr->quant==0){
				node* temp = this->head;
				if(counter==0){
					this->head = temp->next;
					delete nodeptr;
				}
				else {
					for(int i=counter;i>1;--i) {
						temp = temp->next;
					}
					temp->next = nodeptr->next;
					delete nodeptr;
				}
			}
            break;
        }
        ++counter;
        nodeptr = nodeptr->next;
    }
    if(nodeptr==NULL){ 
        printf("NO_STOCK\n");
    }
}

void stock::current_stock(){
    node* nodeptr = this->head;
    while(1){ 
		if(nodeptr==NULL){
			break;
		}
		printf("%d:%d\n", nodeptr->size , nodeptr->quant);
        nodeptr = nodeptr->next;
    }
}

void stock::clear() {
    node* nodeptr;
    while(1) { 
		if(this->head == NULL){
			break;
		}
        nodeptr = this->head; 
        this->head = nodeptr->next; 
        delete nodeptr; 
    }
}
int main(int argc, char**argv) {
    ifstream input(argv[1]);
    struct stock stock1;
    int x;
    while(1) { 
		if(!(input>>x)) {
			break;
		}
        if(x<0) {
			stock1.sell(x*(-1));
		}
        else if(x>0) {
            stock1.add_stock(x);
		}
        else if(x==0) {
            stock1.current_stock();
		}
    }
    stock1.clear();  
    return 0;
}
