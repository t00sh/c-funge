#include <stdlib.h>
#include "funge.h"


FG_stack* FG_stack_new(void)
{
   FG_stack *stack;

   if((stack = malloc(sizeof(*stack))) == NULL)
   {
      goto stack_error;
   }

   if((stack->data = malloc(BASE_STACK_SIZE*sizeof(int32_t))) == NULL)
   {
      goto data_error;
   }

   stack->top = 0;
   stack->size = BASE_STACK_SIZE;

   return stack;

  data_error:
   free(stack);

  stack_error:
   return NULL;   
}

FG_error FG_stack_realloc(FG_stack **stack, int32_t new_size)
{
   int32_t *tmp;

   if((tmp = realloc((*stack)->data, new_size*sizeof(int32_t))) == NULL)
      goto error;

   (*stack)->data = tmp;
   (*stack)->size = new_size;

   return FG_ERR_OK;

  error:
   return FG_ERR_NOMEMORY;
}

int32_t FG_stack_pop(FG_stack *stack, FG_error *error)
{
   int32_t ret;
   FG_error tmp_err;

   if(stack == NULL || stack->data == NULL)
   {
      tmp_err = FG_ERR_NULLPTR;
      goto error;
   }
   if(stack->top == 0)
   {
      tmp_err = FG_ERR_STACKEMPTY;
      goto error;
   }

   stack->top--;
   ret = stack->data[stack->top];

   if(error != NULL)
      *error = FG_ERR_OK;
   return ret;
  
  error:
   if(error != NULL)
      *error = tmp_err;;
   return 0;
}

FG_error FG_stack_push(FG_stack **stack, int32_t value)
{
   FG_error err;

   if(*stack == NULL || (*stack)->data == NULL)
   {
      err = FG_ERR_NULLPTR;
      goto error;
   }

   if((*stack)->top >= (*stack)->size)
   {
      if((err = FG_stack_realloc(stack, (*stack)->size*2)) != FG_ERR_OK)
         goto error;
   }

   (*stack)->data[(*stack)->top] = value;
   (*stack)->top++;
      
   return FG_ERR_OK;

  error:
   return err;
}



void FG_stack_del(FG_stack *stack)
{
   if(stack != NULL)
   {
      if(stack->data != NULL)
      {
         free(stack->data);
         stack->data = NULL;
      }
      free(stack);
   }
}
