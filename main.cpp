#include <stdio.h>
#include "chp03/stack/stack.cpp"

int main() {
    printf("IOIIOIOO: %d\n", judge("IOIIOIOO", 8));
    printf("IOOIOIIO: %d\n", judge("IOOIOIIO", 8));
    printf("IIIOIOIO: %d\n", judge("IIIOIOIO", 8));
    printf("IIIOOIOO: %d\n", judge("IIIOOIOO", 8));
    return 0;
}

