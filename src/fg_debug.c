#include <stdio.h>
#include "funge.h"

void FG_matrix_print(FG_matrix *matrix)
{
   int32_t x, y;

   printf("######################\n");
   printf("MATRIX:\n");
   for(y = 0; y < matrix->end_y; y++)
   {
      for(x = 0; x < matrix->end_x; x++)
      {
         printf("%c", matrix->matrix[y][x]);
      }
      printf("\n");
   }
   printf("max_x: %d\n", matrix->max_x);
   printf("max_y: %d\n", matrix->max_y);
   printf("end_x: %d\n", matrix->end_x);
   printf("end_y: %d\n", matrix->end_y);
}

void FG_stack_print(FG_stack *stack)
{
   int32_t i;

   printf("######################\n");
   printf("STACK:\n");
   for(i = stack->top; i > 0; i--)
   {
      printf("%d\n", stack->data[i-1]);
   }
}
void FG_context_print(FG_context *context)
{
   FG_matrix_print(context->matrix);
   FG_stack_print(context->stack);
   
   printf("#####################\n");
   printf("IP = dir.(%d,%d) coord.(%d,%d)\n",
          context->ip.dir.x, context->ip.dir.y,
          context->ip.coord.x, context->ip.coord.y);
   printf("INSTR = %d => %c\n",
          context->matrix->matrix[context->ip.coord.y][context->ip.coord.x],
          context->matrix->matrix[context->ip.coord.y][context->ip.coord.x]);
}


const char* FG_error_string(FG_error error)
{
   switch(error)
   {
      case FG_ERR_OK:
         return "[NO ERROR]";
      case FG_ERR_NOMEMORY:
         return "[NO MEMORY]";
      case FG_ERR_INTOVERFLOW:
         return "[INTEGER OVERFLOW]";
      case FG_ERR_OUTOFMATRIX:
         return "[OUT OF MATRIX]";
      case FG_ERR_NULLPTR:
         return "[NULL POINTER]";
      case FG_ERR_STACKEMPTY:
         return "[STACK EMPTY]";
      case FG_ERR_OPENFILE:
         return "[CAN'T OPEN FILE]";
      case FG_ERR_INVCOMMAND:
         return "[INVALID COMMAND]";
      case FG_ERR_DIVBYZERO:
         return "[DIVISION BY ZERO]";
   }
   return "[UNKNOWN ERROR]";
}
