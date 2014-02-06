#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "funge.h"

int FG_global_debug = 0;
int FG_global_matrix_x = BASE_MATRIX_X;
int FG_global_matrix_y = BASE_MATRIX_Y;
char FG_global_filename[MAX_PATH_LEN];

static void print_help(const char *progname)
{
   printf("Usage : %s [OPTION]... FILE\n", progname);
   printf("This program is a Befunge interpreter.\n");
   printf("\t-h\t\tPrint this short help.\n");
   printf("\t-v\t\tPrint the current program version.\n");
   printf("\t-d\t\tTurn under debugging mode.\n");
   printf("\t-x X\t\tAlloc X colomn for the matrix (default is %d)\n", BASE_MATRIX_X);
   printf("\t-y Y\t\tAlloc Y lines for the matrix (default is %d\n", BASE_MATRIX_Y);
   
   exit(EXIT_SUCCESS);
}

static void print_version(void)
{
   printf("Version : %s\n", FG_VERSION);
   exit(EXIT_SUCCESS);
}

void parse_argv(int argc, char **argv)
{
   int opt;

   while((opt = getopt(argc, argv, "hvdx:y:")) != EOF)
   {
      switch(opt)
      {
         case 'h':
            print_help(argv[0]);
            break;
         case 'v':
            print_version();
            break;
         case 'd':
            FG_global_debug = 1;
            break;
         case 'x':
            FG_global_matrix_x = atoi(optarg);
            break;
         case 'y':
            FG_global_matrix_y = atoi(optarg);
            break;
      }
   }
   if(FG_global_matrix_x <= 0)
   {
      printf("Invalid matrix X\n");
      exit(EXIT_FAILURE);
   }
   if(FG_global_matrix_y <= 0)
   {
      printf("Invalid matrix Y\n");
      exit(EXIT_FAILURE);
   }

   if(optind != argc - 1)
      print_help(argv[0]);
   
   strncpy(FG_global_filename, argv[optind], MAX_PATH_LEN);
   FG_global_filename[MAX_PATH_LEN-1] = '\0';
}

int main(int argc, char **argv)
{
   FG_context *context;
   FG_error err;

   parse_argv(argc, argv);


   context = FG_context_new(FG_global_matrix_x, FG_global_matrix_y);

   if(context == NULL)
   {
      fprintf(stderr, "[-] Error in FG_context_new !\n");
      exit(EXIT_FAILURE);
   }
      
   if((err = FG_context_load(context, FG_global_filename)) != FG_ERR_OK)
   {
      fprintf(stderr, "[-] Can't load %s!\n", FG_global_filename);
      exit(EXIT_FAILURE);
   }


   err = FG_context_run(context);

   printf("EXIT STATUS : %s\n", FG_error_string(err));
   FG_context_del(context);

   return EXIT_SUCCESS;
}
