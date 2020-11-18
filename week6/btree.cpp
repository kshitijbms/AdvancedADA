//program to perform insertion on B-Tree
#include<bits/stdc++.h> 
using namespace std; 
class Node { 
	int *data;   
	int m;       
	Node **child;  
	int n;      
	bool leaf;  
	public: 
    		Node(int m1, bool leaf1); 
    		void insertionnonfull(int item); 
    		void splitchild(int i, Node *y);  
    		void traverse();  
	friend class btree; 
}; 
class btree { 
    	Node *root;  
    	int m;   
	public: 
    	btree(int m1) {  
    		root = NULL;  
    		m = m1; 
    	} 
  	void traverse() {
  		if(root != NULL) 
  			root->traverse(); 
  	} 
  	void insertion(int item); 
}; 
Node::Node(int m1, bool leaf1) { 
    	m = m1; 
    	leaf = leaf1; 
  	data = new int[2*m-1]; 
    	child = new Node *[2*m]; 
    	n = 0; 
} 
void Node::traverse() { 
        int i; 
    	for(i=0; i<n; i++) { 
        	if(leaf == false) 
            		child[i]->traverse(); 
        	cout<<data[i]<<" "; 
    	} 
  	if(leaf == false) 
        	child[i]->traverse();
} 
void btree::insertion(int item) { 
    	if(root == NULL) { 
        	root = new Node(m, true); 
        	root->data[0] = item; 
        	root->n = 1;  
    	} 
    	else { 
		if(root->n == 2*m-1) { 
			Node *s = new Node(m, false); 
			s->child[0] = root; 
  			s->splitchild(0, root); 
			int i = 0; 
            		if(s->data[0] < item) 
                		i++; 
            		s->child[i]->insertionnonfull(item); 
  			root = s; 
		} 
        	else   
            		root->insertionnonfull(item); 
    	} 
} 
void Node::insertionnonfull(int item) 
{
	int i = n-1; 
	if(leaf == true)
    { 
                while(i >= 0 && data[i] > item)
                { 
            		data[i+1] = data[i]; 
            		i--; 
             	} 
		data[i+1] = item; 
       	n = n+1; 
    } 
    else 
    { 
        while(i >= 0 && data[i] > item) 
            i--; 
            if (child[i+1]->n == 2*m-1) 
            { 
                splitchild(i+1, child[i+1]); 
                if(data[i+1] < item) 
                    i++; 
            } 
        child[i+1]->insertionnonfull(item); 
    } 
} 
void Node::splitchild(int i, Node *y) { 
	Node *z = new Node(y->m, y->leaf); 
    	z->n = m-1; 
	for(int j=0; j<m-1; j++) 
		z->data[j] = y->data[j+m]; 
	if(y->leaf == false) 
    { 
		for(int j=0; j<m; j++) 
            		z->child[j] = y->child[j+m]; 
    } 
	y->n = m-1; 
	for(int j=n; j >= i+1; j--) 
		child[j+1] = child[j]; 
	child[i+1] = z; 
	for(int j=n-1; j >= i; j--) 
        	data[j+1] = data[j]; 
	data[i] = y->data[m-1]; 
	n = n+1; 
} 
int main() 
{
	int n,t,item;
	cout<<"Enter the Degree 't' for the B-tree"<<endl;
	cin>>t;
	btree b(t);
	cout<<"Enter the No. of elements to be inserted into the B-tree"<<endl;
	cin>>n;
	cout<<"Enter the elements"<<endl;
	for(int i=0; i<n; i++) 
    {
		cin>>item;
		b.insertion(item);
	}
	cout<<"\nThe Inorder traversal of the B-tree is as follows:\n\n";
	b.traverse();
	cout<<"\n\n";
	return 0;
}