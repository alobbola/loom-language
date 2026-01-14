#include <stdio.h>
#include <stdlib.h>
#include "../src/chunk.h"
#include "../src/common.h"
#include "../src/value.h"

int main() {
    Chunk chunk;
    initChunk(&chunk);

    int constant = addConstant(&chunk, NUMBER_VAL(1.2));
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);
    writeChunk(&chunk, OP_RETURN, 123);

    if (chunk.count != 3) {
        printf("--> no...\n");
        return 1;
    }

    if (chunk.code[0] != OP_CONSTANT) {
        printf("--> no...\n");
        return 1;
    }

    if (chunk.code[1] != constant) {
        printf("--> no...\n");
        return 1;
    }

    if (chunk.code[2] != OP_RETURN) {
        printf("--> no...\n");
        return 1;
    }

    if (AS_NUMBER(chunk.constants.values[constant]) != 1.2) {
        printf("--> no...\n");
        return 1;
    }

    freeChunk(&chunk);
    printf("-> yes...\n");

    return 0;
}