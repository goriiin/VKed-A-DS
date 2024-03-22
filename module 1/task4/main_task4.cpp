#include <iostream>
#include "../DataStr/heap/heap.h"

bool cmp(int a, int b){
    return a < b;
}

int main() {
    heap<int> h(cmp);
    h.out();
}