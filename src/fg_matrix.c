#include <stdlib.h>
#include "funge.h"

FG_matrix* FG_matrix_new(int32_t x, int32_t y)
{
   FG_matrix *matrix;
   int32_t i;
   
   if((matrix = malloc(sizeof(*matrix))) == NULL)
      goto matrix_error;

   if((matrix->matrix = malloc(sizeof(int32_t*)*y)) == NULL)
      goto matrix_x_error;

   for(i = 0; i < y; i++)
   {
      if((matrix->matrix[i] = calloc(sizeof(int32_t), x)) == NULL)
         goto matrix_y_error;
   }
   
   matrix->max_x = x;
   matrix->max_y = y;
   matrix->end_x = 0;
   matrix->end_y = 0;

   return matrix;

  matrix_y_error:
   for(i = 0; matrix->matrix[i] != NULL; i++)
      free(matrix->matrix[i]);

  matrix_x_error:
   free(matrix);

  matrix_error:
   return NULL;
}

FG_error FG_matrix_changecell(FG_matrix *matrix, int32_t x, int32_t y, int32_t val)
{
   if(matrix == NULL || matrix->matrix == NULL)
      return FG_ERR_NULLPTR;

   if(x < 0 || y < 0 || x >= matrix->max_x || y >= matrix->max_y)
      return FG_ERR_OUTOFMATRIX;

   matrix->matrix[y][x] = val;

   if(x >= matrix->end_x && val != ' ')
      matrix->end_x = x+1;
   if(y >= matrix->end_y && val != ' ')
      matrix->end_y = y+1;

   return FG_ERR_OK;
}

void FG_matrix_del(FG_matrix *matrix)
{
   int32_t i;

   if(matrix != NULL)
   {
      if(matrix->matrix != NULL)
      {
         for(i = 0; i < matrix->max_y; i++)
            free(matrix->matrix[i]);
         free(matrix->matrix);
      }
      free(matrix);
   }
}
