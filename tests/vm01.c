#include <stdio.h>
#include "../src/common.h"
#include "../src/chunk.h"
#include "../src/debug.h"
#include "../src/vm.h"

int main() {
    initVM();

    Chunk chunk;
    initChunk(&chunk);

    int constant = addConstant(&chunk, NUMBER_VAL(1.2));
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);
    writeChunk(&chunk, OP_RETURN, 123);

    InterpretResult result = interpret(&chunk);

    freeChunk(&chunk);
    freeVM();

    if (result == INTERPRET_OK) {
        printf("-> yes...\n");
        return 0;
    } else {
        printf("--> no...\n");
        return 1;
    }
}