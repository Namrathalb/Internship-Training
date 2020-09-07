#include <stdio.h>
int m, n, i, j;
char mat[100][100];
int ans[100][100];

int isvalid(int x, int y) {
    if(x >= 0 && x <= m && y >= 0 && y <= n) return 1;
    return 0;
}

void fun(int x, int y) {
    int a, b;
    for(a = -1; a <= 1; a++) {
        for(b = -1; b <= 1; b++) {
            if(a == 0 && b == 0) continue;
            if(isvalid(x + a, y + b)) ans[x + a][y + b]++;
        }
    }
}

int main() {
    scanf("%d%d", &m, &n);
    for(i = 0; i < m; i++) {
        scanf("%s", mat[i]);
    }
    for(i = 0; i < m; i++) {
        for(j = 0; j < n; j++) {
            ans[i][j] = 0;
        }
    }
    for(i = 0; i < m; i++) {
        for(j = 0; j < n; j++) {
            if(mat[i][j] == '*') fun(i, j);
        }
    }
    for(i = 0; i < m; i++) {
        for(j = 0; j < n; j++) {
            if(mat[i][j] == '*') printf("%c", mat[i][j]);
            else printf("%d", ans[i][j]);
        }
        printf("\n");
    }
    return 0;
}