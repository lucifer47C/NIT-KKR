#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    printf("Enter number of vertices (n) and edges (m): ");
    if (scanf("%d %d", &n, &m) != 2) return 0;

    // store edges
    int (*edges)[2] = malloc(m * sizeof *edges);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        // assume input vertices are 1..n
        edges[i][0] = u - 1;
        edges[i][1] = v - 1;
    }

    int *in_cover = calloc(n, sizeof(int));
    for (int i = 0; i < m; ++i) {
        int u = edges[i][0], v = edges[i][1];
        if (!in_cover[u] && !in_cover[v]) {
            // pick both endpoints
            in_cover[u] = 1;
            in_cover[v] = 1;
        }
    }

    printf("Approximate vertex cover vertices:\n");
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (in_cover[i]) {
            printf("%d ", i + 1);
            ++count;
        }
    }
    if (count == 0) printf("(empty)\n");
    else printf("\nCover size = %d\n", count);

    free(edges);
    free(in_cover);
    return 0;
}
