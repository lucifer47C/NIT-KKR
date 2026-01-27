#include <stdio.h>
#include <stdlib.h>

struct SplayTreeNode 
{
    int data;
    struct SplayTreeNode *left, *right;
};

struct SplayTreeNode* create(int data) 
{
    struct SplayTreeNode* n = (struct SplayTreeNode*)malloc(sizeof(struct SplayTreeNode));
    n->data = data;
    n->left = n->right = NULL;
    return n;
}

struct SplayTreeNode* rightRotation(struct SplayTreeNode* parent) 
{
    struct SplayTreeNode* child = parent->left;
    parent->left = child->right;
    child->right = parent;
    return child;
}

struct SplayTreeNode* leftRotation(struct SplayTreeNode* parent) 
{
    struct SplayTreeNode* child = parent->right;
    parent->right = child->left;
    child->left = parent;
    return child;
}

struct SplayTreeNode* Splay(struct SplayTreeNode* root, int data) 
{
    if (root == NULL || root->data == data)
        return root;

    /*
    while (root != NULL)
    {
    if (data < root->data) 
    {
        if (root->left == NULL) 
            break;

        if (data < root->left->data) 
        {  // Zig-Zig
            root = rightRotation(root);
            if (root->left == NULL) 
                break;
        } 
        else if (data > root->left->data) 
        {  // Zig-Zag
            root->left = leftRotation(root->left);
        }
        root = rightRotation(root);
    }
    else 
    {
        if (root->right == NULL) 
            break;

        if (data < root->right->data) 
        {  
            // Zag-Zig
            root = rightRotation(root);
            if (root->right == NULL) 
                break;
        } 
        else if (data > root->right->data) 
        {  
            // Zag-Zag
            root->right = rightRotation(root->right);
        }
        root = leftRotation(root);
    }
    */
    
    if (data < root->data) 
    {
        if (root->left == NULL) 
            return root;

        // Zig-Zig (LL)
        if (data < root->left->data) 
        {
            root->left->left = Splay(root->left->left, data);
            root = rightRotation(root);
        }
        // Zig-Zag (LR)
        else if (data > root->left->data) 
        {
            root->left->right = Splay(root->left->right, data);
            if (root->left->right != NULL)
                root->left = leftRotation(root->left);
        }

        if (root->left == NULL) 
        {
            return root; 
        }
        else
        {
            return rightRotation(root);
        }
    } 
    else 
    { 
        if (root->right == NULL) 
            return root;

        // Zag-Zig (RL)
        if (data < root->right->data) {
            root->right->left = Splay(root->right->left, data);
            if (root->right->left != NULL)
                root->right = rightRotation(root->right);
        }
        // Zag-Zag (RR)
        else if (data > root->right->data) 
        {
            root->right->right = Splay(root->right->right, data);
            root = leftRotation(root);
        }

        if (root->right == NULL) 
        {
            return root; 
        }
        else
        {
            return leftRotation(root);
        }
    }
}

struct SplayTreeNode* insert(struct SplayTreeNode* root, int data) 
{
    if (root == NULL) 
        return create(data);

    root = Splay(root, data);

    if (root->data == data) 
        return root; 

    struct SplayTreeNode* newnode = create(data);

    if (data < root->data) 
    {
        newnode->right = root;
        newnode->left = root->left;
        root->left = NULL;
    } 
    else 
    {
        newnode->left = root;
        newnode->right = root->right;
        root->right = NULL;
    }
    return newnode;
}

struct SplayTreeNode* maxpredecessor(struct SplayTreeNode* node) {
    while (node->right != NULL)
        node = node->right;
    return node;
}

struct SplayTreeNode* deletenode(struct SplayTreeNode* root, int data) {
    if (root == NULL)
        return NULL;

    root = Splay(root, data);

    if (root->data != data)
        return root;

    struct SplayTreeNode* temp;

    if (root->left == NULL) 
    {
        temp = root;
        root = root->right;
        free(temp);
    } 
    else 
    {
        temp = root;
        struct SplayTreeNode* lsubtree = root->left;
        struct SplayTreeNode* pred = maxpredecessor(lsubtree);

        lsubtree = Splay(lsubtree, pred->data);
        lsubtree->right = root->right;

        free(temp);
        root = lsubtree;
    }
    return root;
}

int search(struct SplayTreeNode** root, int key) 
{
    *root = Splay(*root, key);
    return (*root != NULL && (*root)->data == key);
}

void preorder(struct SplayTreeNode* root) 
{
    if (root != NULL) 
    {
        printf("%d  ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(struct SplayTreeNode* root) 
{
    if (root != NULL) 
    {
        inorder(root->left);
        printf("%d  ", root->data);
        inorder(root->right);
    }
}

int main() 
{
    struct SplayTreeNode* root = NULL;
    int choice, val;

    while (1) 
    {
        printf("\n\n--- Splay Tree ---\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Preorder Traversal\n");
        printf("5. Inorder Traversal\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
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
                if (search(&root, val))
                    printf("Found (splayed to root)\n");
                else
                    printf("Not Found\n");
                break;

            case 4:
                printf("Preorder: ");
                preorder(root);
                printf("\n");
                break;

            case 5:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;

            case 6:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }
}
