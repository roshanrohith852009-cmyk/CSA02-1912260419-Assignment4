#include <stdio.h>

int next_token(void) {
    static int token = 1000;
    return ++token;
}

int auto_token(void) {
    int token = 1000;
    return ++token;
}

int main(void) {
    printf("static: %d %d %d\n",
        next_token(), next_token(), next_token());

    printf("auto : %d %d %d\n",
        auto_token(), auto_token(), auto_token());

    return 0;
}
