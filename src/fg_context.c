#include <stdlib.h>
#include <stdio.h>
#include "funge.h"

FG_context* FG_context_new(int32_t matrix_x, int32_t matrix_y)
{
   FG_context *context;

   if((context = malloc(sizeof(*context))) != NULL)
   {
      if((context->matrix = FG_matrix_new(matrix_x, matrix_y)) == NULL)
         goto matrix_error;
      if((context->stack = FG_stack_new()) == NULL)
         goto stack_error;
   }

   context->string_mode_on = 0;
   context->is_running = 0;
   FG_vector_changedir(&context->ip, 1, 0);
   FG_vector_changecoord(&context->ip, 0, 0);
   
   return context;

  stack_error:
   FG_matrix_del(context->matrix);

  matrix_error:
   free(context);

   return NULL;
}

FG_error FG_context_load(FG_context *context, const char *filename)
{
   FILE *file;
   int32_t c;
   int32_t x, y;
   FG_error err;

   if((file = fopen(filename, "r")) == NULL)
   {
      err = FG_ERR_OPENFILE;
      goto error;
   }

   x = y = 0;

   while((c = fgetc(file)) != EOF)
   {
      if(c == '\n')
      {
         y++;
         x = 0;
      }
      else
      {
         if((err = FG_matrix_changecell(context->matrix, x, y, c)) != FG_ERR_OK)
         {
            goto error;
         }

         x++;
      }
   }
   fclose(file);

   return FG_ERR_OK;
   
  error:
   return err;
}

FG_error FG_context_nextstep(FG_context *context)
{
   FG_error err;

   err = FG_command_exec(context);

   if(err == FG_ERR_OK && context->is_running)
   {
      FG_vector_update(&context->ip, context->matrix->end_x, 
                       context->matrix->end_y);
   }
   return err;
}


FG_error FG_context_run(FG_context *context)
{
   FG_error err;

   context->is_running = 1;
   err = FG_ERR_OK;

   while(context->is_running)
   {
      if(FG_global_debug)
      {
         FG_context_print(context);
         getchar();
      }
      err = FG_context_nextstep(context);
      if(err != FG_ERR_OK)
      {
         context->is_running = 0;
      }
   }

   return err;
}

void FG_context_del(FG_context *context)
{
   if(context != NULL)
   {
      FG_matrix_del(context->matrix);
      FG_stack_del(context->stack);
      free(context);
   }
}
