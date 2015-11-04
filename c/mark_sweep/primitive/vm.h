#ifndef INCLUDE_VM_H

#include "object.h"

#define HEAP_SIZE 1024
#define STACK_SIZE 1024

typedef struct heap_ {
  void* head;
  void* next;
  struct heap_* nextHeap;
} heap;

typedef struct {
  object* stack[STACK_SIZE];
  int stack_size;

  /* for assertion */
  object* roots[STACK_SIZE];
  int root_size;

  heap* heap;
  /* void* next; */
  /* void* freeList; */
} vm;

vm* new_vm();
void free_vm(vm* vm);

void assert_live(vm* vm, int expected_count);

void push(vm* vm, object* obj);
void push_int(vm* vm, int value);
object* pop(vm* vm);

#define INCLUDE_VM_H
#endif
