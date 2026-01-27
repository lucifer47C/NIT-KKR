#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct BinomialNode
{
    int data, degree;
    struct BinomialNode *parent;
    struct BinomialNode *child;
    struct BinomialNode *sibling;
};

struct BinomialNode *create(int data)
{
    struct BinomialNode *node = (struct BinomialNode *)malloc(sizeof(struct BinomialNode));
    node->data = data;
    node->degree = 0;
    node->parent = NULL;
    node->child = NULL;
    node->sibling = NULL;
    return node;
}

struct BinomialNode *linkTrees(struct BinomialNode *y, struct BinomialNode *z)
{
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++;
    return z;
}

struct BinomialNode *mergeRootLists(struct BinomialNode *head1, struct BinomialNode *head2)
{
    if (!head1)
        return head2;
    if (!head2)
        return head1;

    struct BinomialNode *head = NULL, *tail = NULL;

    while (head1 && head2)
    {
        struct BinomialNode *min;
        if (head1->degree <= head2->degree)
        {
            min = head1;
            head1 = head1->sibling;
        }
        else
        {
            min = head2;
            head2 = head2->sibling;
        }

        if (!head)
        {
            head = tail = min;
        }
        else
        {
            tail->sibling = min;
            tail = min;
        }
    }

    if (head1)
        tail->sibling = head1;
    else
        tail->sibling = head2;

    return head;
}

struct BinomialNode *unionHeaps(struct BinomialNode *head1, struct BinomialNode *head2)
{
    struct BinomialNode *newHead = mergeRootLists(head1, head2);
    if (!newHead)
        return NULL;

    struct BinomialNode *prev = NULL, *curr = newHead, *next = curr->sibling;

    while (next)
    {
        if ((curr->degree != next->degree) || (next->sibling && next->sibling->degree == curr->degree))
        {
            prev = curr;
            curr = next;
        }
        else if (curr->data <= next->data)
        {
            curr->sibling = next->sibling;
            linkTrees(next, curr);
        }
        else
        {
            if (prev)
                prev->sibling = next;
            else
                newHead = next;
            linkTrees(curr, next);
            curr = next;
        }
        next = curr->sibling;
    }

    return newHead;
}

struct BinomialNode *insert(struct BinomialNode *head, int data)
{
    struct BinomialNode *node = create(data);
    head = unionHeaps(head, node);
    return head;
}

struct BinomialNode *findMin(struct BinomialNode *head)
{
    if (!head)
        return NULL;

    struct BinomialNode *minNode = head;
    struct BinomialNode *curr = head->sibling;

    while (curr)
    {
        if (curr->data < minNode->data)
            minNode = curr;
        curr = curr->sibling;
    }

    return minNode;
}


struct BinomialNode *reverseList(struct BinomialNode *node)
{
    struct BinomialNode *prev = NULL, *next;
    while (node)
    {
        next = node->sibling;
        node->sibling = prev;
        node->parent = NULL;
        prev = node;
        node = next;
    }
    return prev;
}

struct BinomialNode *extractMin(struct BinomialNode *head)
{
    if (!head)
    {
        printf("Heap is empty.\n");
        return head;
    }

    struct BinomialNode *prevMin = NULL, *minNode = head, *prev = NULL, *curr = head;
    int minKey = minNode->data;

    while (curr)
    {
        if (curr->data < minKey)
        {
            minKey = curr->data;
            prevMin = prev;
            minNode = curr;
        }
        prev = curr;
        curr = curr->sibling;
    }

    if (prevMin)
        prevMin->sibling = minNode->sibling;
    else
        head = minNode->sibling;

    struct BinomialNode *childHeap = reverseList(minNode->child);
    head = unionHeaps(head, childHeap);

    printf("Extracted min: %d\n", minNode->data);
    free(minNode);
    return head;
}

void decreaseKey(struct BinomialNode *head, int oldData, int newData)
{
    if (newData > oldData)
    {
        printf("New key is greater than old key.\n");
        return;
    }

    if (!head)
        return;

    struct BinomialNode *curr = head;
    while (curr)
    {
        if (curr->data == oldData)
            break;

        if (curr->child)
            decreaseKey(curr->child, oldData, newData);

        curr = curr->sibling;
    }

    if (!curr)
        return;

    curr->data = newData;
    struct BinomialNode *parent = curr->parent;

    while (parent && curr->data < parent->data)
    {
        int temp = curr->data;
        curr->data = parent->data;
        parent->data = temp;

        curr = parent;
        parent = curr->parent;
    }
}

struct BinomialNode *deleteKey(struct BinomialNode *head, int key)
{
    decreaseKey(head, key, INT_MIN);
    head = extractMin(head);
    return head;
}

void displayTree(struct BinomialNode *node)
{
    while (node)
    {
        printf("%d ", node->data);
        if (node->child)
        {
            printf("< ");
            displayTree(node->child);
            printf("> ");
        }
        node = node->sibling;
    }
}

void displayHeap(struct BinomialNode *head)
{
    if (!head)
    {
        printf("Heap is empty.\n");
        return;
    }

    printf("Binomial Heap: ");
    displayTree(head);
    printf("\n");
}

int main()
{
    struct BinomialNode *head = NULL;
    int choice, data, newData;

    while (1)
    {
        printf("\n\n--- Binomial Heap ---\n");
        printf("1. Insert\n");
        printf("2. Find Min\n");
        printf("3. Extract Min\n");
        printf("4. Decrease Key\n");
        printf("5. Delete Key\n");
        printf("6. Display Heap\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter key to insert: ");
            scanf("%d", &data);
            head = insert(head, data);
            break;

        case 2:
        {
            struct BinomialNode *minNode = findMin(head);
            if (minNode)
                printf("Minimum key = %d\n", minNode->data);
            else
                printf("Heap is empty.\n");
            break;
        }

        case 3:
            head = extractMin(head);
            break;

        case 4:
            printf("Enter old key and new key: ");
            scanf("%d %d", &data, &newData);
            decreaseKey(head, data, newData);
            break;

        case 5:
            printf("Enter key to delete: ");
            scanf("%d", &data);
            head = deleteKey(head, data);
            break;

        case 6:
            displayHeap(head);
            break;

        case 7:
            printf("Exiting program.\n");
            exit(0);

        default:
            printf("Invalid choice.\n");
        }
    }

    return 0;
}