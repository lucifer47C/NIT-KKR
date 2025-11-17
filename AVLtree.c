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
    n -> data = data;
    n -> left = NULL;
    n -> right = NULL;
    n -> height = 0;
    return n;
}

int height(struct node* n)
{
    if (n == NULL)
        return -1;
    return n -> height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int balance(struct node* n)
{
    if(n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}

struct node* rightRotation(struct node* parent)
{
    struct node* child = parent->left;
    struct node* crightsubtree  = child->right;
    
    child->right = parent;
    parent->left = crightsubtree;

    parent -> height = max(height(parent->left), height(parent->right)) + 1;
    child->height = max(height(child->left), height(child->right)) + 1;

    return child;
}

struct node* leftRotation(struct node* parent)
{
    struct node* child = parent->right;
    struct node* cleftsubtree  = child->left;
    
    child->left = parent;
    parent->right = cleftsubtree;

    parent -> height = max(height(parent->left), height(parent->right)) + 1;
    child->height = max(height(child->left), height(child->right)) + 1;

    return child;
}

struct node* insert(struct node* root, int data)
{
    if(root == NULL)
        return create(data);

    if(data <= root->data)
    {
        root->left = insert(root->left, data);
    }
    else 
    {
        root->right = insert(root->right, data);
    }

    root->height = max(height(root->left), height(root->right)) + 1;
    int bal = balance(root);

    //LL
    if(bal > 1 && data <= root->left->data)
        return rightRotation(root);
    
    //RR
    if(bal < -1 && data > root->right->data)
        return leftRotation(root);

    //LR
    if(bal > 1 && data > root->left->data)
    {
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }

    //RL
    if(bal < -1 && data <= root->right->data)
    {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }
    return root;
}

struct node* deletenode(struct node* root, int data) 
{
    if(root == NULL) 
        return root;
    if(data < root->data)
    {
        root->left = deletenode(root->left, data);
    }
    else if(data > root->data)
    {
        root->right = deletenode(root->right, data);
    }
    else
    {
        //Leaf
        if(root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        //One Child
        else if(root->left && !root->right) //left child
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
        else if(!root->left && root->right) //right child
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        //Two Children
        else
        {
            //Right Subtree smallest element
            struct node *temp1 = root->right;
            while(temp1->left != NULL)
                temp1 = temp1->left;
            
            root->data = temp1->data;
            root->right = deletenode(root->right, temp1->data);
            
        }

    }

    root->height = 1 + max(height(root->left), height(root->right));
    int bal = balance(root);

    if(bal > 1)
    {
        if(balance(root->left) >= 0)//LL
        {
            return rightRotation(root);
        }
        else//LR
        {
            root->left = leftRotation(root->left);
            return rightRotation(root);
        }
    }
    else if(bal < -1)
    {
        if(balance(root->right) <= 0)//RR
        {
            return leftRotation(root);
        }
        else//RL
        {
            root->right = rightRotation(root->right);
            return leftRotation(root);
        }
    }
    else
        return root;

}

int search(struct node* root, int data)
{
    if (root == NULL)
        return 0;
    if (data == root->data)
        return 1;
    else if (data < root->data)
        return search(root->left, data);
    else
        return search(root->right, data);
}

void inorder(struct node* root)
{
    if(root != NULL)
    {
        inorder(root->left);
        printf("%d  ", root->data);
        inorder(root->right);
    }
}

int main()
{
    struct node* root = NULL;
    int choice, val;

    while (1) {
        printf("\n\n--- AVL Tree ---\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Inorder Traversal\n");
        printf("5. Height of Tree\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                root = insert(root, val);
                break;

            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &val);
                root = deletenode(root, val);
                break;

            case 3:
                printf("Enter value to search: ");
                scanf("%d", &val);
                if (search(root, val))
                    printf("Found\n");
                else
                    printf("Not Found\n");
                break;

            case 4:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;

            case 5:
                printf("Height of Tree: %d\n", height(root));
                break;

            case 6:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }
}