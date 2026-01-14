#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../src/memory.h"
#include "../src/common.h"

void test_basic_allocation() {
    

    int* ptr = ALLOCATE(int, 1);
    

    assert(ptr != NULL);
    

    *ptr = 42;
    assert(*ptr == 42);
    

    FREE(int, ptr);
    printf("    -> yes...\n");
}

void test_array_growth() {
    
    int* array = NULL;
    int capacity = 0;
    int count = 0;

    int oldCapacity = capacity;
    capacity = GROW_CAPACITY(oldCapacity); 
    assert(capacity == 8);
    
    array = GROW_ARRAY(int, array, oldCapacity, capacity);
    assert(array != NULL);

    for (int i = 0; i < 8; i++) {
        array[i] = i * 10;
        count++;
    }

    oldCapacity = capacity;
    capacity = GROW_CAPACITY(oldCapacity);
    assert(capacity == 16);
    
    array = GROW_ARRAY(int, array, oldCapacity, capacity);
    
    for (int i = 0; i < 8; i++) {
        assert(array[i] == i * 10);
    }

    FREE_ARRAY(int, array, capacity);
    printf("    -> yes...\n");
}

int main() {
    printf("01 - \n");
    
    test_basic_allocation();
    test_array_growth();
    
    return 0;
}