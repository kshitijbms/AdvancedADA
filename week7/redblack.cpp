//program to perform insertion on REDBLACKTree
#include<bits/stdc++.h> 
using namespace std; 
enum Color {RED, BLACK}; 
struct Node 
{ 
	int data; 
	bool color; 
	Node *left, *right, *parent; 
	Node(int data) 
    { 
		this->data = data; 
	        left = NULL;
	        right = NULL;
	        parent = NULL; 
	        this->color = RED; 
	} 
}; 
class Redblack 
{ 
	private: 
    		Node *root; 
	protected: 
    		void rotateleft(Node *&, Node *&); 
    		void rotateright(Node *&, Node *&); 
    		void fixviolation(Node *&, Node *&); 
	public:
    		Redblack() 
            { 
    			root = NULL; 
    		} 
    		void insertion(const int &n); 
    		void inorder(); 
    		void levelorder(); 
}; 
void inorderhelper(Node *root) 
{ 
    	if (root == NULL) 
        	return; 
      	inorderhelper(root->left); 
    	cout<<root->data<<": "; 
	if(root->color == 1)
		cout<<"Black | ";
	else
		cout<<"Red | ";
    	inorderhelper(root->right);  
} 
Node* insertionBST(Node* root, Node *pt) 
{ 
    	if(root == NULL) 
        	return pt; 
    	if(pt->data < root->data) 
        { 
        	root->left  = insertionBST(root->left, pt); 
        	root->left->parent = root; 
    	} 
    	else if(pt->data > root->data) 
        { 
        	root->right = insertionBST(root->right, pt); 
        	root->right->parent = root; 
    	} 
    	return root; 
} 
void levelorderhelper(Node *root) 
{ 
	if(root == NULL) 
        	return; 
      	std::queue<Node *> q; 
    	q.push(root); 
      	while(!q.empty()) 
        { 
        	Node *temp = q.front(); 
        	cout<<temp->data<<": "; 
            if(temp->color == 1)
                cout<<"Black | ";
            else
                cout<<"Red | ";
            q.pop(); 
            if (temp->left != NULL) 
                    q.push(temp->left); 
            if (temp->right != NULL) 
                    q.push(temp->right); 
    	} 
	cout<<endl;
}
void Redblack::rotateleft(Node *&root, Node *&pt) 
{ 
    	Node *ptr = pt->right;   
    	pt->right = ptr->left; 
	if(pt->right != NULL) 
        	pt->right->parent = pt; 
	ptr->parent = pt->parent; 
  	if(pt->parent == NULL) 
        	root = ptr; 
  	else if(pt == pt->parent->left) 
        	pt->parent->left = ptr; 
	else
        	pt->parent->right = ptr; 
   	ptr->left = pt; 
    	pt->parent = ptr; 
} 
void Redblack::rotateright(Node *&root, Node *&pt) 
{ 
    	Node *ptl = pt->left; 
      	pt->left = ptl->right; 
	if(pt->left != NULL) 
        	pt->left->parent = pt; 
	ptl->parent = pt->parent; 
	if(pt->parent == NULL) 
        	root = ptl; 
	else if(pt == pt->parent->left) 
        	pt->parent->left = ptl; 
  	else
        	pt->parent->right = ptl; 
	ptl->right = pt; 
   	pt->parent = ptl; 
} 
void Redblack::fixviolation(Node *&root, Node *&pt) 
{ 
    	Node *parentpt = NULL; 
    	Node *gparentpt = NULL; 
  	while((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) { 
	        parentpt = pt->parent; 
	        gparentpt = pt->parent->parent; 
	        if(parentpt == gparentpt->left) { 
			Node *unclept = gparentpt->right; 
            		if(unclept != NULL && unclept->color == RED) { 
                		gparentpt->color = RED; 
                		parentpt->color = BLACK; 
                		unclept->color = BLACK; 
                		pt = gparentpt; 
            		} 
 		        else { 
                 		if(pt == parentpt->right) { 
                    			rotateleft(root, parentpt); 
                    			pt = parentpt; 
                    			parentpt = pt->parent; 
                		} 
                		rotateright(root, gparentpt); 
                		swap(parentpt->color, gparentpt->color); 
                		pt = parentpt; 
            		} 
        	} 
        	else { 
            		Node *unclept = gparentpt->left; 
            		if((unclept != NULL) && (unclept->color == RED)) { 
                		gparentpt->color = RED; 
                		parentpt->color = BLACK; 
                		unclept->color = BLACK; 
                		pt = gparentpt; 
            		} 
            		else { 
             			if(pt == parentpt->left) 
                		{ 
                    			rotateright(root, parentpt); 
                    			pt = parentpt; 
                    			parentpt = pt->parent; 
                		} 
                		rotateleft(root, gparentpt); 
                		swap(parentpt->color, gparentpt->color); 
                		pt = parentpt; 
            		} 
        	} 
    	} 
  	root->color = BLACK; 
} 
void Redblack::insertion(const int &n) 
{ 
    	Node *pt = new Node(n); 
    	root = insertionBST(root, pt); 
    	fixviolation(root, pt); 
} 
void Redblack::inorder() 
{  
	inorderhelper(root);
	cout<<endl;
} 
void Redblack::levelorder() 
{ 
	if(root)
		levelorderhelper(root); 
} 
int main() 
{
	Redblack rb;
	int n, item;
	cout<<"Enter the No. of elements to be inserted : ";
	cin>>n;
	cout<<"\nEnter the elements"<<endl;
	for(int i=0;i<n;i++)
    	{
    		cout<<"Enter element "<<i+1<<": ";
        	cin>>item;
        	rb.insertion(item);
        	cout<<"Level order traversal after inserting "<<item<<" : "<<endl; 
    		rb.levelorder();
    		cout<<endl;
    	}
    	cout<<"\nInorder traversal of the tree is\n";
    		rb.inorder();
	return 0;
}