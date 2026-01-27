#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct SegmentTree
{
    int *arr;     
    int *sumTree;  
    int *maxTree;   
    int *minTree;   
    int n;         
};

struct SegmentTree *create(int n)
{
    struct SegmentTree *seg = (struct SegmentTree *)malloc(sizeof(struct SegmentTree));
    seg->n = n;
    seg->arr = (int *)malloc(n * sizeof(int));
    seg->sumTree = (int *)malloc(4 * n * sizeof(int));
    seg->maxTree = (int *)malloc(4 * n * sizeof(int));
    seg->minTree = (int *)malloc(4 * n * sizeof(int));

    for (int i = 0; i < n; i++)
        seg->arr[i] = 0;

    return seg;
}

void insert(struct SegmentTree *seg, int index, int start, int end)
{
    if (start == end)
    {
        seg->sumTree[index] = seg->arr[start];
        seg->maxTree[index] = seg->arr[start];
        seg->minTree[index] = seg->arr[start];
        return;
    }

    int mid = (start + end) / 2;
    insert(seg, 2 * index, start, mid);
    insert(seg, 2 * index + 1, mid + 1, end);

    seg->sumTree[index] = seg->sumTree[2 * index] + seg->sumTree[2 * index + 1];
    seg->maxTree[index] = (seg->maxTree[2 * index] > seg->maxTree[2 * index + 1]) ? seg->maxTree[2 * index] : seg->maxTree[2 * index + 1];
    seg->minTree[index] = (seg->minTree[2 * index] < seg->minTree[2 * index + 1]) ? seg->minTree[2 * index] : seg->minTree[2 * index + 1];
}

int querySum(struct SegmentTree *seg, int index, int start, int end, int L, int R)
{
    if (R < start || L > end)
        return 0;

    if (L <= start && end <= R)
        return seg->sumTree[index];

    int mid = (start + end) / 2;
    int leftSum = querySum(seg, 2 * index, start, mid, L, R);
    int rightSum = querySum(seg, 2 * index + 1, mid + 1, end, L, R);
    return leftSum + rightSum;
}

int queryMax(struct SegmentTree *seg, int index, int start, int end, int L, int R)
{
    if (R < start || L > end)
        return INT_MIN;

    if (L <= start && end <= R)
        return seg->maxTree[index];

    int mid = (start + end) / 2;
    int leftMax = queryMax(seg, 2 * index, start, mid, L, R);
    int rightMax = queryMax(seg, 2 * index + 1, mid + 1, end, L, R);
    return (leftMax > rightMax) ? leftMax : rightMax;
}

int queryMin(struct SegmentTree *seg, int index, int start, int end, int L, int R)
{
    if (R < start || L > end)
        return INT_MAX;

    if (L <= start && end <= R)
        return seg->minTree[index];

    int mid = (start + end) / 2;
    int leftMin = queryMin(seg, 2 * index, start, mid, L, R);
    int rightMin = queryMin(seg, 2 * index + 1, mid + 1, end, L, R);
    return (leftMin < rightMin) ? leftMin : rightMin;
}

void displayArray(struct SegmentTree *seg)
{
    printf("Array elements are: ");
    for (int i = 0; i < seg->n; i++)
        printf("%d ", seg->arr[i]);
    printf("\n");
}

int main()
{
    int n, choice;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    struct SegmentTree *seg = create(n);

    printf("Enter elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &seg->arr[i]);

    insert(seg, 1, 0, n - 1);

    while (1)
    {
        printf("\n\n--- Segment Tree Menu ---\n");
        printf("1. Range Sum Query\n");
        printf("2. Range Max Query\n");
        printf("3. Range Min Query\n");
        printf("4. Display Array\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
            {
                int L, R;
                printf("Enter range [L R]: ");
                scanf("%d %d", &L, &R);
                if (L < 0 || R >= seg->n || L > R)
                {
                    printf("Invalid range.\n");
                    break;
                }
                int result = querySum(seg, 1, 0, seg->n - 1, L, R);
                printf("Sum in range [%d, %d] = %d\n", L, R, result);
                break;
            }

            case 2:
            {
                int L, R;
                printf("Enter range [L R]: ");
                scanf("%d %d", &L, &R);
                if (L < 0 || R >= seg->n || L > R)
                {
                    printf("Invalid range.\n");
                    break;
                }
                int result = queryMax(seg, 1, 0, seg->n - 1, L, R);
                printf("Max in range [%d, %d] = %d\n", L, R, result);
                break;
            }

            case 3:
            {
                int L, R;
                printf("Enter range [L R]: ");
                scanf("%d %d", &L, &R);
                if (L < 0 || R >= seg->n || L > R)
                {
                    printf("Invalid range.\n");
                    break;
                }
                int result = queryMin(seg, 1, 0, seg->n - 1, L, R);
                printf("Min in range [%d, %d] = %d\n", L, R, result);
                break;
            }

            case 4:
                displayArray(seg);
                break;

            case 5:
                printf("Exiting program.\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

