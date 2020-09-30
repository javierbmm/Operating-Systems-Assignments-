#include <stdio.h>

struct primer {
    long a;
    char b;
    int c;
    char d;
};
struct segon {
    char a;
    char b;
    long c;
    int d;
};
struct tercer {
    long a;
    long b;
    char c;
    char d;
};
struct quart {
    char c[5];
    int a;
    long b;
};
struct cinque {
    char a;
    char b;
    char c;
};

int main(void) {
    printf("long=%d bytes\nint=%d bytes\nchar=%d bytes\n",sizeof(long),sizeof(int),sizeof(char));
    printf("Struct1=%d bytes\n", sizeof(struct primer));
    printf("Struct2=%d bytes\n",sizeof(struct segon));
    printf("Struct3=%d bytes\n", sizeof(struct tercer));
    printf("Struct4=%d bytes\n", sizeof(struct quart));
    printf("Struct5=%d bytes\n", sizeof(struct cinque));

    return 0;
}
