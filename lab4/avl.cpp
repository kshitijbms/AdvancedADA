//program to perform insertion and deletion on AVL trees
#include<bits/stdc++.h>
#include<iostream>
#include<algorithm>
using namespace std;

class Node {
	public:
		int data;
		Node *left;
		Node *right;
		int height;
};
int max(int a, int b) 
{
	return (a>b)?a:b;
}
int returnheight(Node *p)
{
	if(p == NULL)
		return 0;
	return p->height;
}
Node* getnode(int data) 
{
	Node *p = new Node();
	p->data = data;
	p->left = NULL;
	p->right = NULL;
	p->height = 1;
	return(p);
}
Node *rotateleft(Node *a) 
{
	Node *b = a->right;
	Node *t = b->left;
	b->left = a;
	a->right = t;
	a->height = max(returnheight(a->right), returnheight(a->left))+1;
	b->height = max(returnheight(b->left), returnheight(b->right))+1;
	return b;
}
Node *rotateright(Node *b) 
{
	Node *a = b->left;
	Node *t = a->right;
	a->right = b;
	b->left = t;
	b->height = max(returnheight(b->left), returnheight(b->right))+1;
	a->height = max(returnheight(a->right), returnheight(a->left))+1;
	return a;
}
int balance(Node *p) 
{
	if(p == NULL)
		return 0;
	return returnheight(p->left)-returnheight(p->right);
}
Node* insertion(Node* p, int data)  
{  
	if(p == NULL)  
		return(getnode(data));  
      	if(data < p->data)  
        	p->left = insertion(p->left, data);  
    	else if(data > p->data)  
        	p->right = insertion(p->right, data);  
    	else  
        	return p;  
    	p->height = 1 + max(returnheight(p->left), returnheight(p->right));  
    	int bl = balance(p);  
    	if (bl > 1 && data < p->left->data)  
        	return rotateright(p);  
    	if (bl < -1 && data > p->right->data)  
        	return rotateleft(p);  
    	if (bl > 1 && data > p->left->data) 
    	{  
        	p->left = rotateleft(p->left);  
        	return rotateright(p);  
    	}  
    	if (bl < -1 && data < p->right->data) 
    	{  
        	p->right = rotateright(p->right);  
        	return rotateleft(p);  
    	}  
    	return p;  
}  
Node* minvalue(Node* root) 
{
	Node* curr = root;
	while(curr->left != NULL)
		curr = curr->left;
	return curr;
}
Node* deletion(Node* root, int item)  
{  
	if(root == NULL)  
        	return root;  
     	if(item < root->data)  
        	root->left = deletion(root->left, item);  
    	else if(item > root->data)  
        	root->right = deletion(root->right, item);  
    	else
    	{  
        	if((root->left == NULL) || (root->right == NULL))  
        	{  
            		Node *t = root->left?root->left:root->right;  
            		if (t == NULL)  
            		{  
            	    		t = root;  
                		root = NULL;  
            		}  
            		else 
            			*root = *t; 
            		free(t);  
        	}  
        	else
        	{  
            		Node* t = minvalue(root->right); 
            		root->data = t->data;  
            		root->right = deletion(root->right, t->data);  
        	}  
    	}  
     	if (root == NULL)  
    		return root;  
     	root->height = 1 + max(returnheight(root->left), returnheight(root->right));  
     	int bl = balance(root);  
     	if(bl > 1 && balance(root->left) >= 0)  
        	return rotateright(root);  
     	if(bl > 1 && balance(root->left) < 0)  
    	{  
        	root->left = rotateleft(root->left);  
        	return rotateright(root);  
    	}  
    	if (bl < -1 && balance(root->right) <= 0)  
        	return rotateleft(root);  
    	if (bl < -1 && balance(root->right) > 0)  
    	{  
        	root->right = rotateright(root->right);  
        	return rotateleft(root);  
    	}  
      	return root;  
}  
void preOrder(Node *root) 
{
	if(root != NULL) 
	{
		cout<<root->data<<" ";
		preOrder(root->left);
		preOrder(root->right);
	}
}
// Driver Code 
int main()  
{  
    
   
	int item,n;
	Node *root = NULL;
	cout<<"Enter the number of elements to be inserted\n";
	cin>>n;
	cout<<"Enter the elements\n";
	for(int i = 0; i < n; i++) 
	{
		cin>>item;
		root = insertion(root, item);
	}
	cout<<"\nElements have been inserted.\n";
	cout<<"\nThe Preorder traversal of the tree is as follows: \n";
	preOrder(root);
	cout<<endl;
	cout<<"\nEnter the element to be deleted : ";
	cin>>item;
	root = deletion(root, item);
	cout<<"\nElement has been deleted.\n";
	cout<<"\nThe Preorder traversal of the tree after deletion is as follows: \n";
	preOrder(root);
	cout<<endl;
	return 0;

}  