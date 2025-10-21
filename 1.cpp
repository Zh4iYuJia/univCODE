#include<stdio.h>

void m() {
    printf("Hello world");
    m();
}

void main() {
    m();
}

