#ifndef DEF_FUNGE_H
#define DEF_FUNGE_H

#include <stdint.h>

#define FG_VERSION "1.0.0"

#define BASE_MATRIX_X 80
#define BASE_MATRIX_Y 25

#define MAX_PATH_LEN 256

#define BASE_STACK_SIZE 20

typedef int FG_bool;

typedef struct FG_coord
{
   int32_t x;
   int32_t y;

}FG_coord;

typedef struct FG_vector
{
   FG_coord coord;
   FG_coord dir;

}FG_vector;

typedef struct FG_matrix
{
   int32_t **matrix;
   int32_t max_x;
   int32_t max_y;

   int32_t end_x;
   int32_t end_y;
}FG_matrix;



typedef struct FG_stack
{
   int32_t *data;
   uint32_t top;
   uint32_t size;

}FG_stack;

typedef enum FG_error
{
   FG_ERR_OK,
   FG_ERR_NOMEMORY,
   FG_ERR_INTOVERFLOW,
   FG_ERR_OUTOFMATRIX,
   FG_ERR_NULLPTR,
   FG_ERR_STACKEMPTY,
   FG_ERR_OPENFILE,
   FG_ERR_INVCOMMAND,
   FG_ERR_DIVBYZERO,

}FG_error;

typedef struct FG_context
{
   FG_matrix *matrix;
   FG_stack *stack;
   FG_vector ip;

   FG_bool string_mode_on;
   FG_bool is_running;

}FG_context;


FG_error FG_command_exec(FG_context *context);
FG_context* FG_context_new(int32_t matrix_x, int32_t matrix_y);
FG_error FG_context_load(FG_context *context, const char *filename);
FG_error FG_context_nextstep(FG_context *context);
FG_error FG_context_run(FG_context *context);
void FG_context_del(FG_context *context);
const char* FG_error_string(FG_error error);
void FG_context_print(FG_context *context);
void FG_stack_print(FG_stack *stack);
void FG_matrix_print(FG_matrix *matrix);
FG_matrix* FG_matrix_new(int32_t x, int32_t y);
FG_error FG_matrix_changecell(FG_matrix *matrix, int32_t x, int32_t y, int32_t val);
void FG_matrix_del(FG_matrix *matrix);
FG_stack* FG_stack_new(void);
FG_error FG_stack_realloc(FG_stack **stack, int32_t new_size);
int32_t FG_stack_pop(FG_stack *stack, FG_error *error);
FG_error FG_stack_push(FG_stack **stack, int32_t value);
void FG_stack_del(FG_stack *stack);
void FG_vector_update(FG_vector *vector, int32_t max_x, int32_t max_y);
void FG_vector_changedir(FG_vector *vector, int32_t x, int32_t y);
void FG_vector_changecoord(FG_vector *vector, int32_t x, int32_t y);
FG_coord FG_vector_getdir(FG_vector *vector);
FG_coord FG_vector_getcoord(FG_vector *vector);

extern int FG_global_debug;
extern int FG_global_matrix_x;
extern int FG_global_matrix_y;
extern char FG_global_filename[];

#endif
