#include <am.h>
#include <klib.h>
#include <rtthread.h>

// OldLiu Modify Start
#define STACK_SIZE (4096 * 8)
typedef union {
  uint8_t stack[STACK_SIZE];
  struct { Context *cp; };
} PCB;
static PCB pcb[2], pcb_boot, *current = &pcb_boot;
// OldLiu Modify End

static Context* ev_handler(Event e, Context *c) {
  switch (e.event) {
    default: printf("Unhandled event ID = %d\n", e.event); assert(0);
  }
  return c;
}

void __am_cte_init() {
  cte_init(ev_handler);
}

void rt_hw_context_switch_to(rt_ubase_t to) {
  // OldLiu Modify Start
  assert(0);

  // OldLiu Modify End
}

void rt_hw_context_switch(rt_ubase_t from, rt_ubase_t to) {
  assert(0);
}

void rt_hw_context_switch_interrupt(void *context, rt_ubase_t from, rt_ubase_t to, struct rt_thread *to_thread) {
  assert(0);
}

rt_uint8_t *rt_hw_stack_init(void *tentry, void *parameter, rt_uint8_t *stack_addr, void *texit) {
  // OldLiu Modify Start
  // assert(0);
  assert(current);
  rt_uint8_t *my_stack_addr = (rt_uint8_t *)((uintptr_t)stack_addr & ~(sizeof(uintptr_t) - 1));

  pcb[0].cp = kcontext((Area) { my_stack_addr, my_stack_addr + STACK_SIZE}, tentry, parameter);
  // yield();
  // panic("Should not reach here!");
  return (rt_uint8_t *)pcb[0].cp;
  // OldLiu Modify End
}
