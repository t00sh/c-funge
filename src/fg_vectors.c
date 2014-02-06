#include "funge.h"



void FG_vector_update(FG_vector *vector, int32_t max_x, int32_t max_y)
{
   vector->coord.x = (vector->coord.x + vector->dir.x);
   vector->coord.y = (vector->coord.y + vector->dir.y);

   if(vector->coord.x < 0)
      vector->coord.x = max_x-1;
   if(vector->coord.y < 0)
      vector->coord.y = max_y-1;
   if(vector->coord.x >= max_x)
      vector->coord.x = 0;
   if(vector->coord.y >= max_y)
      vector->coord.y = 0;
}

void FG_vector_changedir(FG_vector *vector, int32_t x, int32_t y)
{
   vector->dir.x = x;
   vector->dir.y = y;
}

void FG_vector_changecoord(FG_vector *vector, int32_t x, int32_t y)
{
   vector->coord.x = x;
   vector->coord.y = y;
}

FG_coord FG_vector_getdir(FG_vector *vector)
{
   return vector->dir;
}

FG_coord FG_vector_getcoord(FG_vector *vector)
{
   return vector->coord;
}
