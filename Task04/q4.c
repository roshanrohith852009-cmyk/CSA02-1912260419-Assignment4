#include <stdio.h>

struct account {
    int number;
    float balance;
};

void addInterest(struct account *a, float rate) {
    printf("Function address: %p\n", (void *)a);
    a->balance += a->balance * rate / 100.0f;
}

int main(void) {
    struct account list[3] = {
        {101, 5000}, {102, 12000}, {103, 800}
    };

    struct account *p = list;

    for (int i = 0; i < 3; i++) {
        printf("Main address: %p\n", (void *)&list[i]);
        addInterest(&list[i], 4);
    }

    printf("\nUpdated account balances:\n");
    for (int i = 0; i < 3; i++)
        printf("%d %.2f\n", p[i].number, p[i].balance);

    return 0;
}
