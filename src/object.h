#ifndef cloom_object_h
#define cloom_object_h

#include "common.h"
#include "value.h"

typedef enum {
    OBJ_STRING,
} ObjType;

struct Obj {
    ObjType type;
    struct Obj* next; 
};

#define OBJ_TYPE(value)   (AS_OBJ(value)->type)

#endif