#ifndef __MV__
#define __MV__

#include <stddef.h>

#include "/home/daniel/git/ds/stack/api_stack.h" 

typedef struct Mstack mvstack_t; 

mvstack_t *MVcreat(size_t capacity);
void MVDestroy(mvstack_t *stack);
void MVPush(mvstack_t *stack, void *data);
void MVPop(mvstack_t *stack);
void *MVPeek(mvstack_t *stack);
void *MVGetMinVal(mvstack_t *stack);

#endif   /*__MV__*/
