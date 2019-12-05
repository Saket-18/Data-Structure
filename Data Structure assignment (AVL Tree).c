/*Code By Saket Kumar Sahu RollNo:17086*/
// AVL Tree implimentation in C
 
struct Node 
{ 
	int key; 
	struct Node *left; 
	struct Node *right; 
	int height; 
}; 
#define NULL 0
struct Node *tmp;

//Function to search for given data
void search(struct Node* tstd, int trank)
{
	if(tstd)
	{
		printf("\nsearching at %p where key is %d",tstd,tstd->key);
	if(tstd->key == trank)
		tmp = tstd;
	else if(tstd->key > trank)
		search(tstd->left, trank);
	else if(tstd->key < trank)
		search(tstd->right, trank);
	else
		tmp=NULL;
	}
}

// A function to get maximum of two integers which is used in calculating height
int max(int a, int b); 

// A function to get the height of the tree 
int height(struct Node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return N->height; 
} 
// A function to get maximum of two integers 
int max(int a, int b) 
{ 
	return (a > b)? a : b; 
} 

/* function that allocates a new node with the given key and 
	NULL left and right pointers. */
struct Node* newNode(int key) 
{ 
	struct Node* node = (struct Node*)malloc(sizeof(struct Node)); 
	node->key = key; 
	node->left = NULL; 
	node->right = NULL; 
	node->height = 1; 
	return(node); 
} 

// A function to right rotate subtree with root y 
 
struct Node *rightRotate(struct Node *y) 
{ 
	struct Node *x = y->left; 
	struct Node *T2 = x->right; 

	// Perform rotation 
	x->right = y; 
	y->left = T2; 

	// Update heights 
	y->height = max(height(y->left), height(y->right))+1; 
	x->height = max(height(x->left), height(x->right))+1; 

	// Return new root 
	return x; 
} 

// A function to left rotate subtree with root x 
 
struct Node *leftRotate(struct Node *x) 
{ 
	struct Node *y = x->right; 
	struct Node *T2 = y->left; 

	// Perform rotation 
	y->left = x; 
	x->right = T2; 

	// Update heights 
	x->height = max(height(x->left), height(x->right))+1; 
	y->height = max(height(y->left), height(y->right))+1; 

	// Return new root 
	return y; 
} 

// Get Balance factor of node N 
int getBalance(struct Node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return height(N->left) - height(N->right); 
} 

// Recursive function to insert a key in the subtree rooted with node and returns the new root of the subtree. 
struct Node* insert(struct Node* node, int key) 
{ 
	/* 1. Perform the normal BST insertion */
	if (node == NULL) 
        return(newNode(key));

	if (key < node->key) 
		node->left = insert(node->left, key); 
	else if (key > node->key) 
		node->right = insert(node->right, key); 
	else 
		{
			printf("\n%d already exists\n",node->key);
			return node; 
		}
	/* 2. Update height of this ancestor node */
	node->height = 1 + max(height(node->left), 
						height(node->right)); 

	/* 3. Get the balance factor of this ancestor 
		node to check whether this node became 
		unbalanced */
	int balance = getBalance(node); 

	// If this node becomes unbalanced, then 
	// there are 4 cases 

	// Left Left Case 
	if (balance > 1 && key < node->left->key)
	{
		printf("\nAs the balance factor becomes %d and %d is less than %d we perform right rotation around %d to maintain the AVL tree properties\n",balance,key,node->left->key,node->left->key); 
		return rightRotate(node); 
	}
		
	// Right Right Case 
	if (balance < -1 && key > node->right->key) 
	{
		printf("\nAs the balance factor becomes %d and %d is greater than %d we perform left rotation around %d to maintain the AVL tree properties\n",balance,key,node->right->key,node->right->key);
		return leftRotate(node);
	}
		 

	// Left Right Case 
	if (balance > 1 && key > node->left->key) 
	{ 
		printf("\nAs the balance factor becomes %d and %d is greater than %d we perform first left rotation around %d and then right rotation around %d to maintain the AVL tree properties\n",balance,key,node->left->key,node->left->key,node->key);
		node->left = leftRotate(node->left); 
		return rightRotate(node); 
	} 

	// Right Left Case 
	if (balance < -1 && key < node->right->key) 
	{ 
		printf("\nAs the balance factor becomes %d and %d is less than %d we perform first right rotation around %d and then left rotation around %d to maintain the AVL tree properties\n",balance,key,node->right->key,node->right->key,node->key);
		node->right = rightRotate(node->right); 
		return leftRotate(node); 
	} 

	/* return the node pointer if it is unchanged*/
	
	return node; 
} 
/* Given a non-empty binary search tree, return the node with minimum key value found in that tree. 
   Note that the entire tree does not need to be searched. */
struct Node * minValueNode(struct Node* node) 
{ 
    struct Node* current = node; 
  
    /* loop down to find the leftmost leaf */
    while (current->left != NULL) 
        current = current->left; 
  
    return current; 
} 
  
// Recursive function to delete a node with given key 
// from subtree with given root. It returns root of 
// the modified subtree. 
struct Node* deleteNode(struct Node* root, int key) 
{ 
    // STEP 1: PERFORM STANDARD BST DELETE 
  
    if (root == NULL) 
        return root; 
  
    // If the key to be deleted is smaller than the 
	// root's key, then it lies in left subtree 
    if ( key < root->key ) 
        root->left = deleteNode(root->left, key); 
  
    // If the key to be deleted is greater than the 
    // root's key, then it lies in right subtree 
    else if( key > root->key ) 
        root->right = deleteNode(root->right, key); 
  
    // if key is same as root's key, then This is 
    // the node to be deleted 
    else
    { 
        // node with only one child or no child 
        if( (root->left == NULL) || (root->right == NULL) ) 
        { 
            struct Node *temp = root->left ? root->left : 
                                             root->right; 
  
            // No child case 
            if (temp == NULL) 
            { 
                temp = root; 
                root = NULL; 
            } 
            else // One child case 
             *root = *temp; // Copy the contents of 
                            // the non-empty child 
            free(temp); 
        } 
        else
        { 
            // node with two children: Get the  
            //smallest element in the right subtree 
            struct Node* temp = minValueNode(root->right); 
  
            // Copy the smallest element in right subtree's data to this node 
            root->key = temp->key; 
  
            // Delete the smallest in the right subtree 
            root->right = deleteNode(root->right, temp->key); 
        }
	}
	if(root==NULL)
	{
		return root;
	}
        /* 2. Update height of this ancestor node */
	root->height = 1 + max(height(root->left), 
						height(root->right)); 

	/* 3. Get the balance factor of this ancestor 
		node to check whether this node became 
		unbalanced */
	int balance = getBalance(root); 

	// If this node becomes unbalanced, then 
	// there are 4 cases 

	// Left Left Case 
	if (balance > 1 && key < root->left->key)
	{
		printf("\nAs the balance factor becomes %d and %d is less than %d we perform right rotation around %d to maintain the AVL tree properties\n",balance,key,root->left->key,root->left->key); 
		return rightRotate(root); 
	}
		
	// Right Right Case 
	if (balance < -1 && key > root->right->key) 
	{
		printf("\nAs the balance factor becomes %d and %d is greater than %d we perform left rotation around %d to maintain the AVL tree properties\n",balance,key,root->right->key,root->right->key);
		return leftRotate(root);
	}
		 

	// Left Right Case 
	if (balance > 1 && key > root->left->key) 
	{ 
		printf("\nAs the balance factor becomes %d and %d is greater than %d we perform first left rotation around %d and then right rotation around %d to maintain the AVL tree properties\n",balance,key,root->left->key,root->left->key,root->key);
		root->left = leftRotate(root->left); 
		return rightRotate(root); 
	} 

	// Right Left Case 
	if (balance < -1 && key < root->right->key) 
	{ 
		printf("\nAs the balance factor becomes %d and %d is less than %d we perform first right rotation around %d and then left rotation around %d to maintain the AVL tree properties\n",balance,key,root->right->key,root->right->key,root->key);
		root->right = rightRotate(root->right); 
		return leftRotate(root); 
	} 

	/* return the node pointer if it is unchanged*/
	
	return root;
	}

// The function prints the AVL tree in descending order
void preOrder(struct Node *root) 
{ 
	if(root != NULL) 
	{ 
		
		preOrder(root->right); 
		 
		printf("%d ", root->key);
		
		preOrder(root->left); 
		 
	 
	} 
} 

/* Main function*/
int main() 
{ 
struct Node *root = NULL; 
int opt;
int sval=0;


while(1)
{
printf("\n\n\n\n1. Add");
printf("\n2. delete_");
printf("\n3. Display Tree ");
printf("\n4. Search\n");
printf("\n5. Exit\n");
printf("\n Choose your option from above list:  ");
if(scanf("%d",&opt)!=1)
	break;
switch(opt)
	{
	case 1:
			do
			{
				
			printf("\n Add a new key ");
			scanf("%d",&sval);
			if(sval>0)
				{
					root=insert(root,sval);
				}
			else
				printf("invalid key");
			}while(sval>0);
			
			break;
	case 2:	printf("\n Enter the key value to delete ");
			scanf("%d",&sval);
			search(root,sval);
			if(tmp)
			{
				
				root=deleteNode(root,sval);
				printf("\n%d key value found at position %p has been deleted \n",sval,tmp);
			}
			else
				printf("\n key %d is not found",sval);
			
						
			break;
		
	case 3:	
			if(root==NULL)
			{
				printf("\nNothing to display from tree\n");	
			}
			printf("\nThe AVL tree in Descending order that is rightmost first is given by \n"); 
			preOrder(root); 
			break;
	case 4: printf("\n Search for what? ");
			scanf("%d",&sval);
			tmp=NULL;
			search(root,sval);
			if(tmp)
				printf("\n%d found @ %p", sval, tmp);
			else
				printf("\n %d is found nowhere in tree", sval);
			break;
	
	case 5: printf("\n ************Exit************\n");
			exit(0);

	default: printf("\n Invalid input");
			  break;




 return 0; 
 } 
}
}

