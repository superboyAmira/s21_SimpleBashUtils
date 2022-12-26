#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct options {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
  int E;
} OPT;

static struct option long_options[] = {
    {"number-nonblank", no_argument, NULL, 'b'},
    {"number", no_argument, NULL, 'n'},
    {"squeeze-blank", no_argument, NULL, 's'},
    {NULL, 0, NULL, 0}};

const char *short_options = "+benstvTE";

void parser(int argc, char *argv[], OPT *flags);
void reader(char *argv[], OPT *flags, int argc);
void functionB(int current, int *flag, int *counter_string, int *count_empty);
void functionN(int current, int *flag, int *counter_string, int *flag_empty);
void functionT(int current);
void functionE(int current);
void functionS(int current, int tmp);
void basedCat(int current);

void parser(int argc, char *argv[], OPT *flags) {
  int opt;
  int option_index;

  while ((opt = getopt_long(argc, argv, short_options, long_options,
                            &option_index)) != -1) {
    switch (opt) {
      case 'b':
        flags->b = 1;
        break;
      case 'E':
      case 'e':
        flags->e = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 's':
        flags->s = 1;
        break;
      case 'T':
      case 't':
        flags->t = 1;
        break;
      default:
        printf("\n%c\n", opt);
        fprintf(stderr,
                "usage\t"
                "+benstvTE");
        exit(1);
    }
  }
}

void reader(char *argv[], OPT *flags, int argc) {
  FILE *file;
  for (; optind < argc; optind++) {
    file = fopen(argv[optind], "r");
    if (file != NULL) {
      int current;
      int flag = 1;
      int flag_empty = 0;
      int counter_string = 1;
      int tmp = 0;

      while ((current = fgetc(file)) != EOF) {
        if (flags->b) {
          functionB(current, &flag, &counter_string, &flag_empty);
        } else if (flags->s) {
          if (current == '\n') {
            tmp += 1;
          } else {
            tmp = 0;
          }
          functionS(current, tmp);
        } else if (flags->n) {
          functionN(current, &flag, &counter_string, &flag_empty);
        } else if (flags->t) {
          functionT(current);
        } else if (flags->e) {
          functionE(current);
        } else {
          basedCat(current);
        }
      }
    } else {
      printf("No such file or directory");
    }
    fclose(file);
  }
}

void functionB(int current, int *flag, int *counter_string, int *count_empty) {
  if (current != '\n') {
    if (*flag == 1) {
      printf("%6d\t", *counter_string);
      printf("%c", current);
      *flag += 1;
    } else {
      printf("%c", current);
      *flag += 1;
    }
    *count_empty = 0;
  } else {
    if (*count_empty < 1) {
      *counter_string += 1;
    }
    *count_empty += 1;
    printf("\n");
    *flag = 1;
  }
}

void functionN(int current, int *flag, int *counter_string, int *flag_empty) {
  if (current != '\n') {
    if (*flag == 1) {
      printf("%6d\t", *counter_string);
      printf("%c", current);
      *flag += 1;
    } else {
      printf("%c", current);
      *flag += 1;
    }
    *flag_empty = 0;
  } else if (*flag_empty == 1) {
    printf("%6d\t", *counter_string);
    printf("\n");
    *counter_string += 1;
  } else {
    printf("\n");
    *counter_string += 1;
    *flag = 1;
    *flag_empty = 1;
  }
}

void functionT(int current) {
  switch (current) {
    case ('\t'):
      printf("^I");
      break;
    default:
      printf("%c", current);
      break;
  }
}

void functionE(int current) {
  if (current < 32 && current != 9) {
    if (current == '\n') {
      printf("$\n");
    } else {
      current += 64;
      printf("^%c", current);
    }
  } else {
    printf("%c", current);
  }
}

void functionS(int current, int tmp) {
  if (tmp < 3) {
    printf("%c", current);
  }
}

void basedCat(int current) { printf("%c", current); }

int main(int argc, char *argv[]) {
  OPT flags = {0};

  parser(argc, argv, &flags);
  if (flags.b) {
    flags.n = 0;
    flags.e = 0;
    flags.t = 0;
    flags.s = 0;
  }

  reader(argv, &flags, argc);

  return 0;
}
