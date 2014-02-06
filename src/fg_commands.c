#include <stdio.h>
#include "funge.h"

FG_error FG_command_add(FG_context *context)
{
   int32_t a, b;

   a = FG_stack_pop(context->stack, NULL);
   b = FG_stack_pop(context->stack, NULL);

   return FG_stack_push(&context->stack, b+a);
}

FG_error FG_command_sub(FG_context *context)
{
   int32_t a, b;

   a = FG_stack_pop(context->stack, NULL);
   b = FG_stack_pop(context->stack, NULL);
   
   return FG_stack_push(&context->stack, b-a);
}

FG_error FG_command_mul(FG_context *context)
{
   int32_t a, b;

   a = FG_stack_pop(context->stack, NULL);
   b = FG_stack_pop(context->stack, NULL);
   
   return FG_stack_push(&context->stack, b*a);
}

FG_error FG_command_div(FG_context *context)
{
   int32_t a, b;

   a = FG_stack_pop(context->stack, NULL);
   b = FG_stack_pop(context->stack, NULL);

   if(a == 0)
      return FG_ERR_DIVBYZERO;

   return FG_stack_push(&context->stack, b/a);
}

FG_error FG_command_mod(FG_context *context)
{
   int32_t a, b;

   a = FG_stack_pop(context->stack, NULL);
   b = FG_stack_pop(context->stack, NULL);

   if(a == 0)
      return FG_ERR_DIVBYZERO;

   return FG_stack_push(&context->stack, b%a);
}

FG_error FG_command_not(FG_context *context)
{
   int32_t a;

   a = FG_stack_pop(context->stack, NULL);

   return FG_stack_push(&context->stack, !a);
}

FG_error FG_command_greater(FG_context *context)
{
   int32_t a, b;

   a = FG_stack_pop(context->stack, NULL);
   b = FG_stack_pop(context->stack, NULL);

   return FG_stack_push(&context->stack, b>a);
}

FG_error FG_command_right(FG_context *context)
{

   FG_vector_changedir(&context->ip, 1, 0);
   
   return FG_ERR_OK;
}

FG_error FG_command_left(FG_context *context)
{
   FG_vector_changedir(&context->ip, -1, 0);

   return FG_ERR_OK;
}

FG_error FG_command_up(FG_context *context)
{
   FG_vector_changedir(&context->ip, 0, -1);

   return FG_ERR_OK;
}

FG_error FG_command_down(FG_context *context)
{
   FG_vector_changedir(&context->ip, 0, 1);

   return FG_ERR_OK;
}

FG_error FG_command_random(FG_context *context)
{
   (void)context;

   return FG_ERR_OK;
}

FG_error FG_command_horizontal(FG_context *context)
{
   int32_t a;

   a = FG_stack_pop(context->stack, NULL);

   if(a)
      FG_vector_changedir(&context->ip, -1, 0);
   else
      FG_vector_changedir(&context->ip, 1, 0);

   return FG_ERR_OK;
}

FG_error FG_command_vertical(FG_context *context)
{
   int32_t a;

   a = FG_stack_pop(context->stack, NULL);

   if(a)
      FG_vector_changedir(&context->ip, 0, -1);
   else
      FG_vector_changedir(&context->ip, 0, 1);

   return FG_ERR_OK;
}

FG_error FG_command_stringmode(FG_context *context)
{
   context->string_mode_on = 1;

   return FG_ERR_OK;
}

FG_error FG_command_dup(FG_context *context)
{
   int32_t a;
   FG_error error;

   a = FG_stack_pop(context->stack, &error);
   
   if((error = FG_stack_push(&context->stack, a)) != FG_ERR_OK)
      return error;

   if((error = FG_stack_push(&context->stack, a)) != FG_ERR_OK)
      return error;

   return FG_ERR_OK;
}

FG_error FG_command_swap(FG_context *context)
{
   int32_t a, b;
   FG_error error;

   a = FG_stack_pop(context->stack, &error);
   b = FG_stack_pop(context->stack, &error);

   if((error = FG_stack_push(&context->stack, a)) != FG_ERR_OK)
      return error;

   if((error = FG_stack_push(&context->stack, b)) != FG_ERR_OK)
      return error;

   return FG_ERR_OK;
}

FG_error FG_command_pop(FG_context *context)
{
   FG_stack_pop(context->stack, NULL);

   return FG_ERR_OK;
}

FG_error FG_command_push(FG_context *context)
{
   int32_t a;
   FG_coord coord;

   coord = FG_vector_getcoord(&context->ip);

   a = context->matrix->matrix[coord.y][coord.x];
   
   return FG_stack_push(&context->stack, a);
}

FG_error FG_command_pushint(FG_context *context)
{
   int32_t a;
   FG_coord coord;

   coord = FG_vector_getcoord(&context->ip);

   a = context->matrix->matrix[coord.y][coord.x];
   
   return FG_stack_push(&context->stack, a-'0');
}

FG_error FG_command_outint(FG_context *context)
{
   int32_t a;

   a = FG_stack_pop(context->stack, NULL);

   printf("%d", a);

   return FG_ERR_OK;
}

FG_error FG_command_outascii(FG_context *context)
{
   int32_t a;

   a = FG_stack_pop(context->stack, NULL);

   putchar(a);

   return FG_ERR_OK;
}

FG_error FG_command_bridge(FG_context *context)
{
   FG_vector_update(&context->ip, 
                    context->matrix->end_x, 
                    context->matrix->end_y);

   return FG_ERR_OK;
}

FG_error FG_command_get(FG_context *context)
{
   int32_t x, y;

   y = FG_stack_pop(context->stack, NULL);
   x = FG_stack_pop(context->stack, NULL);

   if(x < 0 || y < 0 || x >= context->matrix->max_x || y >= context->matrix->max_y)
      return FG_ERR_OUTOFMATRIX;

   return FG_stack_push(&context->stack, context->matrix->matrix[y][x]);
}

FG_error FG_command_put(FG_context *context)
{
   int32_t a, x, y;

   y = FG_stack_pop(context->stack, NULL);
   x = FG_stack_pop(context->stack, NULL);
   a = FG_stack_pop(context->stack, NULL);

   if(x < 0 || y < 0 || x >= context->matrix->max_x || y >= context->matrix->max_y)
      return FG_ERR_OUTOFMATRIX;

   context->matrix->matrix[y][x] = a;
   return FG_ERR_OK;
}

FG_error FG_command_inint(FG_context *context)
{
   int32_t a;

   a = getchar();
   
   return FG_stack_push(&context->stack, a-'0');
}

FG_error FG_command_inascii(FG_context *context)
{
   int32_t a;

   a = getchar();
   
   return FG_stack_push(&context->stack, a);
}

FG_error FG_command_end(FG_context *context)
{
   context->is_running = 0;
   return FG_ERR_OK;
}

FG_error FG_command_nop(FG_context *context)
{
   (void)context;
   return FG_ERR_OK;
}

FG_error (*FG_command_lst[])(FG_context *context) =
{
   FG_command_nop, /*    0  */
   NULL, /*    1  */
   NULL, /*    2  */
   NULL, /*    3  */
   NULL, /*    4  */
   NULL, /*    5  */
   NULL, /*    6  */
   NULL, /*    7  */
   NULL, /*    8  */
   NULL, /*    9  */
   NULL, /*   10  */
   NULL, /*   11  */
   NULL, /*   12  */
   NULL, /*   13  */
   NULL, /*   14  */
   NULL, /*   15  */
   NULL, /*   16  */
   NULL, /*   17  */
   NULL, /*   18  */
   NULL, /*   19  */
   NULL, /*   20  */
   NULL, /*   21  */
   NULL, /*   22  */
   NULL, /*   23  */
   NULL, /*   24  */
   NULL, /*   25  */
   NULL, /*   26  */
   NULL, /*   27  */
   NULL, /*   28  */
   NULL, /*   29  */
   NULL, /*   30  */
   NULL, /*   31  */
   FG_command_nop, /*   32  */
   FG_command_not, /*   33  */
   FG_command_stringmode, /*   34  */
   FG_command_bridge, /*   35  */
   FG_command_pop, /*   36  */
   FG_command_mod, /*   37  */
   FG_command_inint, /*   38  */
   NULL, /*   39  */
   NULL, /*   40  */
   NULL, /*   41  */
   FG_command_mul, /*   42  */
   FG_command_add, /*   43  */
   FG_command_outascii, /*   44  */
   FG_command_sub, /*   45  */
   FG_command_outint, /*   46  */
   FG_command_div, /*   47  */
   FG_command_pushint, /*   48  */
   FG_command_pushint, /*   49  */
   FG_command_pushint, /*   50  */
   FG_command_pushint, /*   51  */
   FG_command_pushint, /*   52  */
   FG_command_pushint, /*   53  */
   FG_command_pushint, /*   54  */
   FG_command_pushint, /*   55  */
   FG_command_pushint, /*   56  */
   FG_command_pushint, /*   57  */
   FG_command_dup, /*   58  */
   NULL, /*   59  */
   FG_command_left, /*   60  */
   NULL, /*   61  */
   FG_command_right, /*   62  */
   FG_command_random, /*   63  */
   FG_command_end, /*   64  */
   NULL, /*   65  */
   NULL, /*   66  */
   NULL, /*   67  */
   NULL, /*   68  */
   NULL, /*   69  */
   NULL, /*   70  */
   NULL, /*   71  */
   NULL, /*   72  */
   NULL, /*   73  */
   NULL, /*   74  */
   NULL, /*   75  */
   NULL, /*   76  */
   NULL, /*   77  */
   NULL, /*   78  */
   NULL, /*   79  */
   NULL, /*   80  */
   NULL, /*   81  */
   NULL, /*   82  */
   NULL, /*   83  */
   NULL, /*   84  */
   NULL, /*   85  */
   NULL, /*   86  */
   NULL, /*   87  */
   NULL, /*   88  */
   NULL, /*   89  */
   NULL, /*   90  */
   NULL, /*   91  */
   FG_command_swap, /*   92  */
   NULL, /*   93  */
   FG_command_up, /*   94  */
   FG_command_horizontal, /*   95  */
   FG_command_greater, /*   96  */
   NULL, /*   97  */
   NULL, /*   98  */
   NULL, /*   99  */
   NULL, /*  100  */
   NULL, /*  101  */
   NULL, /*  102  */
   FG_command_get, /*  103  */
   NULL, /*  104  */
   NULL, /*  105  */
   NULL, /*  106  */
   NULL, /*  107  */
   NULL, /*  108  */
   NULL, /*  109  */
   NULL, /*  110  */
   NULL, /*  111  */
   FG_command_put, /*  112  */
   NULL, /*  113  */
   NULL, /*  114  */
   NULL, /*  115  */
   NULL, /*  116  */
   NULL, /*  117  */
   FG_command_down, /*  118  */
   NULL, /*  119  */
   NULL, /*  120  */
   NULL, /*  121  */
   NULL, /*  122  */
   NULL, /*  123  */
   FG_command_vertical, /*  124  */
   NULL, /*  125  */
   FG_command_inascii, /*  126  */
   NULL, /*  127  */
   NULL, /*  128  */
   NULL, /*  129  */
   NULL, /*  130  */
   NULL, /*  131  */
   NULL, /*  132  */
   NULL, /*  133  */
   NULL, /*  134  */
   NULL, /*  135  */
   NULL, /*  136  */
   NULL, /*  137  */
   NULL, /*  138  */
   NULL, /*  139  */
   NULL, /*  140  */
   NULL, /*  141  */
   NULL, /*  142  */
   NULL, /*  143  */
   NULL, /*  144  */
   NULL, /*  145  */
   NULL, /*  146  */
   NULL, /*  147  */
   NULL, /*  148  */
   NULL, /*  149  */
   NULL, /*  150  */
   NULL, /*  151  */
   NULL, /*  152  */
   NULL, /*  153  */
   NULL, /*  154  */
   NULL, /*  155  */
   NULL, /*  156  */
   NULL, /*  157  */
   NULL, /*  158  */
   NULL, /*  159  */
   NULL, /*  160  */
   NULL, /*  161  */
   NULL, /*  162  */
   NULL, /*  163  */
   NULL, /*  164  */
   NULL, /*  165  */
   NULL, /*  166  */
   NULL, /*  167  */
   NULL, /*  168  */
   NULL, /*  169  */
   NULL, /*  170  */
   NULL, /*  171  */
   NULL, /*  172  */
   NULL, /*  173  */
   NULL, /*  174  */
   NULL, /*  175  */
   NULL, /*  176  */
   NULL, /*  177  */
   NULL, /*  178  */
   NULL, /*  179  */
   NULL, /*  180  */
   NULL, /*  181  */
   NULL, /*  182  */
   NULL, /*  183  */
   NULL, /*  184  */
   NULL, /*  185  */
   NULL, /*  186  */
   NULL, /*  187  */
   NULL, /*  188  */
   NULL, /*  189  */
   NULL, /*  190  */
   NULL, /*  191  */
   NULL, /*  192  */
   NULL, /*  193  */
   NULL, /*  194  */
   NULL, /*  195  */
   NULL, /*  196  */
   NULL, /*  197  */
   NULL, /*  198  */
   NULL, /*  199  */
   NULL, /*  200  */
   NULL, /*  201  */
   NULL, /*  202  */
   NULL, /*  203  */
   NULL, /*  204  */
   NULL, /*  205  */
   NULL, /*  206  */
   NULL, /*  207  */
   NULL, /*  208  */
   NULL, /*  209  */
   NULL, /*  210  */
   NULL, /*  211  */
   NULL, /*  212  */
   NULL, /*  213  */
   NULL, /*  214  */
   NULL, /*  215  */
   NULL, /*  216  */
   NULL, /*  217  */
   NULL, /*  218  */
   NULL, /*  219  */
   NULL, /*  220  */
   NULL, /*  221  */
   NULL, /*  222  */
   NULL, /*  223  */
   NULL, /*  224  */
   NULL, /*  225  */
   NULL, /*  226  */
   NULL, /*  227  */
   NULL, /*  228  */
   NULL, /*  229  */
   NULL, /*  230  */
   NULL, /*  231  */
   NULL, /*  232  */
   NULL, /*  233  */
   NULL, /*  234  */
   NULL, /*  235  */
   NULL, /*  236  */
   NULL, /*  237  */
   NULL, /*  238  */
   NULL, /*  239  */
   NULL, /*  240  */
   NULL, /*  241  */
   NULL, /*  242  */
   NULL, /*  243  */
   NULL, /*  244  */
   NULL, /*  245  */
   NULL, /*  246  */
   NULL, /*  247  */
   NULL, /*  248  */
   NULL, /*  249  */
   NULL, /*  250  */
   NULL, /*  251  */
   NULL, /*  252  */
   NULL, /*  253  */
   NULL, /*  254  */
   NULL, /*  255  */
};

FG_error FG_command_exec(FG_context *context)
{
   FG_coord coord;
   FG_error err;
   int32_t instr;
   
   coord = FG_vector_getcoord(&context->ip);
   instr = context->matrix->matrix[coord.y][coord.x];
   err = FG_ERR_OK;

   if(instr >= 0 && (uint32_t)instr < sizeof(FG_command_lst)/sizeof(*FG_command_lst))
   {
      if(context->string_mode_on)
      {
         if(instr == '"')
            context->string_mode_on = 0;
         else
           err = FG_command_push(context);
      }
      else
      {
         if(FG_command_lst[instr] != NULL)
            err = FG_command_lst[instr](context);
         else
            err = FG_ERR_INVCOMMAND;
      }
   }
   
   return err;
}
