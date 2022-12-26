#ifndef SRC_GREP_GREP_H
#define SRC_GREP_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 2000
#define TRUE 1
#define FALSE 0

regex_t reg_comp;
regmatch_t struct_reg[1] = {0};

typedef struct options {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int new_word;
} OPT;

const char *short_options = "e:ivcln";

int parser(int argc, char *argv[], OPT *flags, char *buffer_patterns);
void output(char *buffer_patterns, OPT *flags, int argc, char **argv,
            int disable);
void E_plus(char *Buff_paterns, OPT *flags);

#endif  // SRC_GREP_GREP_H
