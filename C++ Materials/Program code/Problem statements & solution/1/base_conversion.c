#include <stdio.h>
#include <string.h>

char number[100];
int counter = 0;

char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

void convert(int n, int x) {
    if(n == 0) {
        number[counter] = '\0';
        printf("The number in base %d is %s\n", x, strrev(number));
        return;
    }
    int rem = n % x;
    number[counter++] = (char)('0' + rem);
    convert(n / x, x);
}

int main() {
    convert(10, 3);
    return 0;
}