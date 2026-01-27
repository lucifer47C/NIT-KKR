#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct TrieNode 
{
    char data;
    struct TrieNode *children[26];
    bool isEnd;
};

struct TrieNode *create(char ch) 
{
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    node->data = ch;
    node->isEnd = false;
    for (int i = 0; i < 26; i++)
        node->children[i] = NULL;
    return node;
}

void insert(struct TrieNode *root, char *datastr) 
{
    struct TrieNode *temp = root;
    for (int i = 0; i < strlen(datastr); i++) 
    {
        int index = datastr[i] - 'a';
        if (index < 0 || index > 25) 
        {
            printf("Invalid character in string: %c\n", datastr[i]);
            return;
        }

        if (temp->children[index] == NULL)
            temp->children[index] = create(datastr[i]);

        temp = temp->children[index];
    }
    temp->isEnd = true;
    printf("Inserted word: %s\n", datastr);
}

bool search(struct TrieNode *root, char *datastr) 
{
    struct TrieNode *temp = root;
    for (int i = 0; i < strlen(datastr); i++) 
    {
        int index = datastr[i] - 'a';
        if (index < 0 || index > 25)
        {
            printf("Invalid character in string: %c\n", datastr[i]);
            return false;
        }

        if (temp->children[index] == NULL)
            return false;

        temp = temp->children[index];
    }

    return (temp != NULL && temp->isEnd);
}

void printWords(struct TrieNode *root, char *buffer, int depth)
{
    if (root == NULL)
        return;

    if (root->isEnd) 
    {
        buffer[depth] = '\0';
        printf("%s\n", buffer);
    }

    for (int i = 0; i < 26; i++) 
    {
        if (root->children[i] != NULL) 
        {
            buffer[depth] = root->children[i]->data;
            printWords(root->children[i], buffer, depth + 1);
        }
    }
}

void maxPrefix(struct TrieNode *root) 
{
    char prefix[100];
    int length = 0;
    struct TrieNode *temp = root;

    while (1) 
    {
        int childCount = 0;
        int childIndex = -1;

        for (int i = 0; i < 26; i++) 
        {
            if (temp->children[i] != NULL) 
            {
                childCount++;
                childIndex = i;
            }
        }

        if (childCount != 1 || temp->isEnd)
            break;

        temp = temp->children[childIndex];
        prefix[length++] = temp->data;
    }

    prefix[length] = '\0';

    if (length > 0)
        printf("Longest Common Prefix: %s\n", prefix);
    else
        printf("No common prefix found.\n");
}

int main() 
{
    struct TrieNode *root = create('\0');
    int choice;
    char word[100];
    char buffer[100];

    while (1) 
    {
        printf("\n\n--- Trie Menu ---\n");
        printf("1. Insert Word\n");
        printf("2. Search Word\n");
        printf("3. Display All Words\n");
        printf("4. Find Longest Common Prefix\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                printf("Enter word to insert: ");
                scanf("%s", word);
                insert(root, word);
                break;

            case 2:
                printf("Enter word to search: ");
                scanf("%s", word);
                if (search(root, word))
                    printf("String '%s' is present.\n", word);
                else
                    printf("String '%s' is not present.\n", word);
                break;

            case 3:
                printf("Words stored in Trie:\n");
                printWords(root, buffer, 0);
                break;

            case 4:
                maxPrefix(root);
                break;

            case 5:
                printf("Exiting program.\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}