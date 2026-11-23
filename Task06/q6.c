#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 20
#define MAX_COMBO 3

enum item_type { PACKAGED, COOKED, COMBO };

struct date {
    int day, month, year;
};

struct packaged {
    float price;
    struct date expiry;
    int stock;
};

struct cooked {
    float price;
    int stock;
    int hour, minute;
};

struct combo {
    int item_ids[MAX_COMBO];
    int quantity[MAX_COMBO];
    int count;
};

struct item {
    int id;
    char name[40];
    enum item_type type;
    union {
        struct packaged pack;
        struct cooked cook;
        struct combo meal;
    } details;
};

struct sale {
    int item_id;
    int quantity;
    float revenue;
};

struct item items[MAX_ITEMS];
struct sale sales[MAX_ITEMS];
int item_count = 0, sale_count = 0;

float price_of(const struct item *p) {
    if (p->type == PACKAGED) return p->details.pack.price;
    if (p->type == COOKED) return p->details.cook.price;
    return 0.0f;
}

int stock_of(const struct item *p) {
    if (p->type == PACKAGED) return p->details.pack.stock;
    if (p->type == COOKED) return p->details.cook.stock;
    return 0;
}

int update_stock(struct item *p, int quantity) {
    if (p->type == PACKAGED) {
        if (p->details.pack.stock < quantity) return 0;
        p->details.pack.stock -= quantity;
        return 1;
    }
    if (p->type == COOKED) {
        if (p->details.cook.stock < quantity) return 0;
        p->details.cook.stock -= quantity;
        return 1;
    }
    return 0;
}

int record_sale(int id, int quantity) {
    for (int i = 0; i < item_count; i++) {
        if (items[i].id == id) {
            if (quantity <= 0 || !update_stock(&items[i], quantity))
                return 0;

            float revenue = price_of(&items[i]) * quantity;
            sales[sale_count++] = (struct sale){id, quantity, revenue};
            printf("Sale recorded: %s, Rs. %.2f\n",
                   items[i].name, revenue);
            return 1;
        }
    }
    return 0;
}

void expiry_warning(struct item *p, struct date today) {
    if (p->type != PACKAGED) return;

    struct date d = p->details.pack.expiry;
    int days = (d.year - today.year) * 365 +
               (d.month - today.month) * 30 +
               d.day - today.day;

    if (days >= 0 && days <= 2)
        printf("EXPIRY WARNING: %s expires soon\n", p->name);
}

void sort_sales(void) {
    for (int i = 0; i < sale_count - 1; i++)
        for (int j = 0; j < sale_count - i - 1; j++)
            if (sales[j].revenue < sales[j+1].revenue) {
                struct sale t = sales[j];
                sales[j] = sales[j+1];
                sales[j+1] = t;
            }
}

int main(void) {
    items[0].id = 1;
    strcpy(items[0].name, "Milk");
    items[0].type = PACKAGED;
    items[0].details.pack = (struct packaged){30, {25,11,2026}, 10};

    items[1].id = 2;
    strcpy(items[1].name, "Sandwich");
    items[1].type = COOKED;
    items[1].details.cook = (struct cooked){50, 5, 10, 30};

    item_count = 2;

    struct date today = {23,11,2026};

    expiry_warning(&items[0], today);

    record_sale(1, 2);
    record_sale(2, 2);

    if (!record_sale(2, 20))
        printf("Sale rejected: insufficient stock\n");

    sort_sales();

    printf("\nDAY BILL SUMMARY\n");
    for (int i = 0; i < sale_count; i++)
        printf("Item %d Quantity %d Revenue Rs. %.2f\n",
            sales[i].item_id, sales[i].quantity, sales[i].revenue);

    return 0;
}
