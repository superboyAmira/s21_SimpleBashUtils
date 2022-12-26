Q1 = s21_grep
GCC = gcc -Wall -Werror -Wextra
SRC_GREP = s21_grep.c

OBJ = $(SRC:.c=.o)

all : 
	$(GCC) $(SRC_GREP) -o $(Q1)

s21_grep : 
	$(GCC) $(SRC_GREP) -o $(Q1)

rebuild : 
	make clean
	make all

clean : 
	rm -rf $(Q1)
