#include <stdio.h>

#define MAXN 100  
#define MAXM 100  
int main() {
    int n, m; // n = universe size, m = number of sets
    int sets[MAXM][MAXN]; // set elements as 0/1 matrix
    int setSize[MAXM];
    int covered[MAXN] = {0};
    int selected[MAXM] = {0};
    int i, j, k;

    printf("Enter number of elements in universe: ");
    scanf("%d", &n);

    printf("Enter number of sets: ");
    scanf("%d", &m);

   
    for (i = 0; i < m; i++) {
        printf("Enter number of elements in set %d: ", i + 1);
        scanf("%d", &setSize[i]);
        printf("Enter elements: ");
        for (j = 0; j < n; j++) sets[i][j] = 0; 

        for (j = 0; j < setSize[i]; j++) {
            int x;
            scanf("%d", &x);
            sets[i][x - 1] = 1; 
        }
    }

    int coveredCount = 0;
    int chosenCount = 0;

    while (coveredCount < n) {
        int bestSet = -1;
        int bestCover = 0;

        for (i = 0; i < m; i++) {
            if (selected[i]) continue;
            int newCover = 0;
            for (j = 0; j < n; j++) {
                if (sets[i][j] && !covered[j]) {
                    newCover++;
                }
            }
            if (newCover > bestCover) {
                bestCover = newCover;
                bestSet = i;
            }
        }

        if (bestSet == -1) {
            printf("Cannot cover all elements!\n");
            return 0;
        }

        selected[bestSet] = 1;
        chosenCount++;

        
        for (j = 0; j < n; j++) {
            if (sets[bestSet][j] && !covered[j]) {
                covered[j] = 1;
                coveredCount++;
            }
        }
    }

    printf("\nSelected sets for minimum cover: ");
    for (i = 0; i < m; i++) {
        if (selected[i]) printf("S%d ", i + 1);
    }
    printf("\n");
    return 0;
}
