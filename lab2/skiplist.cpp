//c++ program to implement search effiecient singly linked list known as Skip list
#include <bits/stdc++.h> 
const float P = 0.5;
using namespace std;
class Node
{ 
	public:
		int data;
		Node **forwd;
		Node(int level , int data)
		{
			forwd=new Node*[level+1];
			memset(forwd,0,sizeof(Node*)*(level+1));
			this->data=data;
		}
		~Node()
		{
			delete[] forwd;
		}
};
class Skiplist
{
	public:
		Node *header;
		int level;
		int MAX_LEVEL;
		Skiplist(int MAXL)
		{	
			header = new Node(MAXL,-1); 
			this->MAX_LEVEL=MAXL;
			level=0;
			
		}
		~Skiplist()
		{	
			delete header;
		}
		void display()
		{
			cout<<"Skip List "<<endl;
			for (int i=0;i<=level;i++) 
			    { 
				Node *node = header->forwd[i]; 
				if (node==NULL)
				{
					cout<<"The list is Empty."<<endl;
					return;
				}
				cout << "Level " << i << ": "; 
				while (node != NULL) 
				{ 
				    cout << node->data<<" "; 
				    node = node->forwd[i]; 
				} 
				cout << "\n"; 
			    } 
		}
		int randomlevel()
		{
			float r = (float)rand()/RAND_MAX; 
    			int lvl = 0; 
    			while (r < P && lvl < MAX_LEVEL) 
    			{ 
        			lvl++; 
        			r = (float)rand()/RAND_MAX; 
    			} 
    			return lvl; 
		}
		Node* createNode(int data,int lev)
		{
			Node *n = new Node(lev,data); 
    			return n; 
		}
		
		void insertion(int data)
		{
			Node *current = header; 
  			Node *update[MAX_LEVEL+1]; 
			memset(update, 0, sizeof(Node*)*(MAX_LEVEL+1)); 
			  
			    
			for (int i = level; i >= 0; i--) 
			 { 
				while (current->forwd[i] != NULL && current->forwd[i]->data < data) 
				    current = current->forwd[i]; 
				update[i] = current; 
			 } 
			current = current->forwd[0]; 
			if (current == NULL || current->data != data) 
			{ 
				
				int rlevel = randomlevel(); 
			 	if (rlevel > level) 
				{ 
				    for (int i=level+1;i<rlevel+1;i++) 
					update[i] = header; 
			  	   
				    level = rlevel; 
				} 
			  	
				Node* n = createNode(data, rlevel); 
			  	
				for (int i=0;i<=rlevel;i++) 
				{ 
				    n->forwd[i] = update[i]->forwd[i]; 
				    update[i]->forwd[i] = n; 
				} 
		       
	   	   	    } 
		}
		bool searchlist(int scdata)
		{	Node* x= header;
			for(int i=level;i>=0;i--)
			{
				while(x->forwd[i]!=NULL && x->forwd[i]->data < scdata)
					x=x->forwd[i];
			}
			x=x->forwd[0];
			return x!=NULL && x->data == scdata;
			
		}
		void deletion(int data)
		{
			Node *x = header;	
    			Node *update[MAX_LEVEL + 1];
    			memset(update, 0, sizeof(Node*) * (MAX_LEVEL + 1));
    			for (int i = level;i >= 0;i--)
    			{
    				while (x -> forwd[i] != NULL && x -> forwd[i]->data < data)
    				 {
            				x = x -> forwd[i];
        			 }
        			update[i] = x; 
    			}
    			x = x->forwd[0];
    			if (x->data == data) {
        			for (int i = 0;i <= level;i++) 
        			{
        				if (update[i] -> forwd[i] != x) 
        				break;
            				update[i] -> forwd[i] = x -> forwd[i];
        			}
        			delete x;
        			while (level > 0 && header -> forwd[level] == NULL) 
        			{
            				level--;
        			}
    			}
		}
		
	
};
int main()
{
	Skiplist skp = Skiplist(3);
	int choice,n,ict;
	do
	{	cout<<"------------------------------------------------------"<<endl;
		cout<<"Enter 1 : Insertion\nEnter 2 : Deletion \nEnter 3 : Search \nEnter 4 : Display List \n";
		cout<<"Enter you choice: ";
		cin>>choice;
		switch(choice)
		{
			case 1 : cout<<"Enter the Element: ";
				int b;
				cin>>b;
				skp.insertion(b);
				
				break;
			case 2 : cout<<"Enter the Element: ";
				cin>>n;
				if(skp.searchlist(n))
				{
					skp.deletion(n);
				}
				else
				{
					cout<<"\nElement is  not in the list."<<endl;
				}
				break;
			case 3 :cout<<"Enter the Element to be searched: ";
				cin>>n;
				if(skp.searchlist(n))
				{
					cout<<"\n"<<n<<" is present in the list."<<endl;
				}
				else
				{
					cout<<"\nElement is  not in the list."<<endl;
				}
				
				break;
			case 4 :skp.display();
				break;
				
			default : cout<<"Incorrect Choice.\n"<<endl;
			
				
		};
		cout<<"Do you want to continue :(1/0): ";
		
		cin>>ict;
	}while(ict!=0);
	return 0;
}