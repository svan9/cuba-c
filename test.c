#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} some;

int main() {
    some* p = malloc(sizeof(some));
    p->a = 10;
    p->b = 12;
    return 0;
}
