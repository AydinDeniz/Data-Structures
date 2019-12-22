/* @Author

Student Name : Deniz Aydýn

Student ID : 150180036

Date : 18.12.2019 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class BS
{
    //Class for base station
    //Every node keeps an array of pointers named 'children'
    //These arrays are dynamically updated after adding each BS
    //Mobile hosts follow the same logic
    public:
        int id;
        int child_count;
        int mh_count;
        BS **children;
        int *mobile_hosts;
        BS(int i)
		{
            this->id = i;
            this->children = NULL;
            this->mobile_hosts = NULL;
            this->child_count = 0;
            this->mh_count = 0;
        }
        void addBS(int,int);
        void addMH(int,int);
        bool message(int,int*);
        
};

class Network
{
    public:
        static int total_BS;
        BS* head;
        void create();
        
};

void Network::create()
{
    this->head = new BS(0);
}

int Network::total_BS = 1;//Total number of base stations in the network

void BS::addBS(int child,int parent)
{
    //Adds a base station to the network
    if(this->id == parent)
	{
        BS* new_BS = new BS(child);
        BS** temp;
        temp = this->children;
        this->children = new BS*[this->child_count + 1];//New array with +1 size
        for(int i=0;i<child_count;i++)//Copying the array
		{
            this->children[i] = temp[i];
        }
        (this->children)[this->child_count] = new_BS;
        ++(this->child_count);
        if(this->child_count != 1) delete[] temp;
        Network::total_BS++;
    }
    else
	{
        for(int i =0;i<child_count;i++)
		{
            (this->children)[i]->addBS(child,parent);
        }
    }
}

void BS::addMH(int mh,int parent)
{
    //Adds mobile host
    if(this->id == parent)
	{
        int* temp = this->mobile_hosts;
        this->mobile_hosts = new int[this->mh_count+1];
        for(int i=0;i<mh_count;i++)
		{
            (this->mobile_hosts)[i] = temp[i];
        }
        (this->mobile_hosts)[this->mh_count] = mh;
        ++(this->mh_count);
        if(this->mh_count != 1) delete[] temp;
    }

    else
	{
        //Calls the function recursively for each child
        for(int i =0;i<child_count;i++)
		{
            (this->children)[i]->addMH(mh,parent);
        }
    }
}

void push(int* array,int push_value,int array_size)
{
    //Helper function
    for(int i=0;i<array_size;i++)
	{
        if(array[i]==-1)
		{
            array[i] = push_value;
            return;
        }

    }
}

bool BS::message(int mh,int* nodes)
{
    //Searches for the mh
    //Fills nodes with the correct path to the base station mobile host is connected to
    push(nodes,this->id,Network::total_BS);
    if(this->id!=0)cout << " ";
    cout << this->id;

    for(int i=0;i<(this->mh_count);i++)
	{
        if((this->mobile_hosts)[i] == mh){
            return true;
        }
    }

    for(int i=0;i < this->child_count;i++)
	{
        //For loop calls the function recursively for each child
        //While filling nodes correctly
        bool flag = (this->children)[i]->message(mh,nodes);
        if(flag) return true;
        bool temp = false;
        for(int x=0;x<Network::total_BS;x++)
		{
            if(nodes[x]==-1)  break;
            if(temp)  nodes[x]=-1;
            if(nodes[x] == this->id) temp = true;
        }
    }
    return false;    
}

int main(int argc, char** argv)
{
    ifstream nfile,mfile;
    nfile.open(argv[1]);
    mfile.open(argv[2]);
    Network my_network;
    my_network.create();
    BS* central_controller = my_network.head;
    int child,parent;
    string op;
    
    while(nfile >> op)
	{
        nfile >> child >> parent;
        if(op == "BS"){
            central_controller->addBS(child,parent);
        }
        else if(op == "MH"){
            central_controller->addMH(child,parent);
        }
    }
    
    string message;
    string rawmessage;
    int mh;
    while(getline(mfile,rawmessage))
	{
        int pos = rawmessage.find_first_of('>');
        if(pos==-1)
            break;
    	message = rawmessage.substr(0, pos);
    	string towhom = rawmessage.substr(pos+1);
    	mh = stoi(towhom);
    
        int nodes[Network::total_BS];
        for(int i=0;i<Network::total_BS;i++)
		{
            nodes[i] = -1;
        }
        cout << "Traversing:";
        bool flag = central_controller->message(mh,nodes);
        if(flag)
		{
            cout << endl << "Message:" << message << " To:";
            for(int i=0;i<Network::total_BS;i++)
			{
                if(nodes[i]==-1)break;
                cout << nodes[i] << " ";
            }
            cout << "mh_" << mh << endl;
        }
        else
		{
            cout << endl << "Can not be reached the mobile host mh_" << mh << " at the moment" << endl;
        }
    }
    
    return 0;
}

