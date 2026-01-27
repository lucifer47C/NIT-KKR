#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct RBTreeNode 
{
    int data;
    bool colour; // 1 = red, 0 = black
    struct RBTreeNode* left;
    struct RBTreeNode* right;
    struct RBTreeNode* parent;
};

struct RBTreeNode* create(int data) 
{
    struct RBTreeNode* node = (struct RBTreeNode*)malloc(sizeof(struct RBTreeNode));
    node->data = data;
    node->colour = 1; 
    node->left = node->right = node->parent = NULL;
    return node;
}

void leftRotation(struct RBTreeNode** root, struct RBTreeNode* node) 
{
    struct RBTreeNode* rchild = node->right;
    node->right = rchild->left;

    if (rchild->left != NULL) 
    {
        rchild->left->parent = node;
    }

    rchild->parent = node->parent;

    if (node->parent == NULL) 
    {
        *root = rchild;
    } 
    else if (node == node->parent->left) 
    {
        node->parent->left = rchild;
    } 
    else 
    {
        node->parent->right = rchild;
    }

    rchild->left = node;
    node->parent = rchild;
}

void rightRotation(struct RBTreeNode** root, struct RBTreeNode* node) 
{
    struct RBTreeNode* lchild = node->left;
    node->left = lchild->right;

    if (lchild->right != NULL) 
    {
        lchild->right->parent = node;
    }

    lchild->parent = node->parent;

    if (node->parent == NULL) 
    {
        *root = lchild;
    } 
    else if (node == node->parent->right) 
    {
        node->parent->right = lchild;
    } 
    else 
    {
        node->parent->left = lchild;
    }

    lchild->right = node;
    node->parent = lchild;
}

void fixProperty(struct RBTreeNode** root, struct RBTreeNode* node) 
{
    while (node->parent != NULL && node->parent->colour == 1) 
    {
        if (node->parent == node->parent->parent->left) {
            struct RBTreeNode* uncle = node->parent->parent->right;

            if (uncle != NULL && uncle->colour == 1) 
            {
                node->parent->colour = 0;
                uncle->colour = 0;
                node->parent->parent->colour = 1;
                node = node->parent->parent;
            } 
            else 
            {
                if (node == node->parent->right) 
                {
                    node = node->parent;
                    leftRotation(root, node);
                }
                node->parent->colour = 0;
                node->parent->parent->colour = 1;
                rightRotation(root, node->parent->parent);
            }
        } 
        else 
        {
            struct RBTreeNode* uncle = node->parent->parent->left;

            if (uncle != NULL && uncle->colour == 1) 
            {
                node->parent->colour = 0;
                uncle->colour = 0;
                node->parent->parent->colour = 1;
                node = node->parent->parent;
            } 
            else 
            {
                if (node == node->parent->left) 
                {
                    node = node->parent;
                    rightRotation(root, node);
                }
                node->parent->colour = 0;
                node->parent->parent->colour = 1;
                leftRotation(root, node->parent->parent);
            }
        }
    }
    (*root)->colour = 0;
}

void insert(struct RBTreeNode** root, int data) 
{
    struct RBTreeNode* node = create(data);
    struct RBTreeNode* parent = NULL;
    struct RBTreeNode* current = *root;

    while (current != NULL) 
    {
        parent = current;
        if (node->data < current->data)
            current = current->left;
        else if (node->data > current->data)
            current = current->right;
        else
        {
            free(node);
            return; 
        }
    }

    node->parent = parent;
    if (parent == NULL) 
    {
        *root = node;
    } 
    else if (node->data < parent->data) 
    {
        parent->left = node;
    } 
    else 
    {
        parent->right = node;
    }

    fixProperty(root, node);
}

void inorder(struct RBTreeNode* root) 
{
    if (root == NULL) 
        return;
    inorder(root->left);
    printf("%d(%s) ", root->data, root->colour ? "R" : "B");
    inorder(root->right);
}

void preorder(struct RBTreeNode* root) 
{
    if (root == NULL) 
        return;
    printf("%d(%s) ", root->data, root->colour ? "R" : "B");
    preorder(root->left);
    preorder(root->right);
}

int main() 
{
    struct RBTreeNode* root = NULL;
    int choice, value;

    while (1) 
    {
        printf("\n\n==== Red-Black Tree Menu ====\n");
        printf("1. Insert\n");
        printf("2. Inorder Traversal\n");
        printf("3. Preorder Traversal\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insert(&root, value);
                printf("Inserted %d\n", value);
                break;

            case 2:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;

            case 3:
                printf("Preorder Traversal: ");
                preorder(root);
                printf("\n");
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
