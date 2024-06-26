#include <stdbool.h>
#include <string.h>

void nora_strrev(char *str) {
    const int length = strlen(str);
    char t;
    for (int i = 0; i < length / 2; i++) {
        t = str[0];
        str[0] = str[length - 1 - i];
        str[length - 1 - i] = t;
    }
}

void strnumber(char *str, int n) {
    bool isNegative = false;
    if (n < 0) {
        n *= -1;
        isNegative = true;
    }

    int i = 0;
    do {
        str[i] = n % 10 + '0';
        n /= 10;
        i++;
    } while (n > 0);

    if (isNegative) {
        str[i] = '-';
        i++;
    }
    str[i] = 0;
    nora_strrev(str);
}
