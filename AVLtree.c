#include <stdio.h>
#include <stdlib.h>

struct node 
{
    int data, height;
    struct node *left, *right;
};

struct node* create(int data)
{
    struct node* n = (struct node*)malloc(sizeof(struct node));
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    n->height = 0;
    return n;
}

int height (struct node * n) 
{
    if (!n)
        return -1;
    return n -> height;
}

int max(int a, int b) 
{ 
    return (a > b) ? a : b; 
}

int getBalance(struct node* n)
{
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}

struct node* rightRotation(struct node* temp)
{
    struct node* temp1 = temp->left;  //temp1 is left child of temp
    struct node* temp2 = temp1->right;  //temp2 is right subtree of temp1

    temp1 -> right = temp;
    temp -> left = temp2;

    temp -> height = max(height(temp->left), height(temp->right)) + 1;
    temp1->height = max(height(temp1->left), height(temp1->right)) + 1;

    return temp1;
}
    

struct node* leftRotation(struct node* temp)
{
    struct node* temp1 = temp->right;  //temp
    struct node* temp2 = temp1->left;

    temp1->left = temp;
    temp->right = temp2;

    temp -> height = max(height(temp->left), height(temp->right)) + 1;
    temp1 -> height = max(height(temp1->left), height(temp1->right)) + 1;

    return temp1;
}

struct node* insert(struct node* root, int data)
{
    if (!root)
        return create(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    else
        return root;


    root->height = 1 + max(height(root->left), height(root->right));

    
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && data < root->left->data)
        return rightRotation(root);

    // Right Right Case
    if (balance < -1 && data > root->right->data)
        return leftRotation(root);

    // Left Right Case
    if (balance > 1 && data > root->left->data) {
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }

    // Right Left Case
    if (balance < -1 && data < root->right->data) {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }
    return root;
}

void inorder(struct node* root)
{
    if (root != NULL) 
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main()
{
    struct node* root = NULL;
    int n, val;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter %d values:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        root = insert(root, val);
    }

    printf("Inorder traversal of AVL tree: ");
    inorder(root);
    printf("\n");

    return 0;
}