.PHONY: clean

SRCDIR = src

CC = gcc
CFLAGS = -O2 -Wall -Wextra -Wwrite-strings -Wstrict-prototypes -Wuninitialized 
CFLAGS += -Wunreachable-code -g3 -I ./include/
#CFLAGS += -pg

SRC = $(wildcard $(SRCDIR)/*.c) 
SRC += $(wildcard $(IRC_CMD_DIR)/*.c)
OBJ = $(SRC:%.c=%.o)

EXE = c-funge

all: $(EXE)

$(EXE): $(OBJ)
	@echo "  LINK $(EXE)" ;
	@$(CC) $(CFLAGS) -o $(EXE) $(OBJ) ;

%.o:%.c
	@echo "  CC $@" ;
	@$(CC) $(CFLAGS) -c $< -o $@ ;

clean:
	rm -rf $(EXE) $(OBJ)


