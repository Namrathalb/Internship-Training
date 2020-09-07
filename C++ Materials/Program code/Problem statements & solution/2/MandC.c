#include <stdio.h>
#include <string.h>
int len, i, ans1, ans2, ans;
char str[100], one[100], two[100];

int main() {
    scanf("%s", str);
    len = strlen(str);
    for(i = 0; i < len; i++) {
        if(i & 1) {
            one[i] = 'R';
            two[i] = 'G';
        } else {
            one[i] = 'G';
            two[i] = 'R';
        }
    }
    one[len] = '\0';
    two[len] = '\0';
    ans1 = 0;
    ans2 = 0;
    for(i = 0; i < len; i++) {
        if(str[i] != one[i]) ans1++;
        if(str[i] != two[i]) ans2++;
    }
    if(ans1 < ans2) ans = ans1;
    else ans = ans2;
    printf("%d\n", ans);
    return 0;
}