#include "s21_grep.h"

int parser(int argc, char *argv[], OPT *flags, char *buffer_patterns) {
  int opt;
  int disable = TRUE;

  while ((opt = getopt_long(argc, argv, short_options, NULL, NULL)) != -1) {
    switch (opt) {
      case 'e':
        flags->e = 1;
        E_plus(buffer_patterns, flags);
        flags->new_word++;
        break;
      case 'i':
        flags->i = 1;
        disable = FALSE;
        break;
      case 'n':
        flags->n = 1;
        disable = FALSE;
        break;
      case 'v':
        flags->v = 1;
        disable = FALSE;
        break;
      case 'c':
        flags->c = 1;
        disable = FALSE;
        break;
      case 'l':
        flags->l = 1;
        disable = FALSE;
        break;
    }
  }
  return disable;
}

void E_plus(char *buffer_patterns, OPT *flags) {
  if (flags->new_word) {
    strcat(buffer_patterns, "|");
  }
  strcat(buffer_patterns, optarg);
}

void output(char *buffer_patterns, OPT *flags, int argc, char **argv,
            int disable) {
  FILE *file;
  int more_files = FALSE;
  int exist = FALSE;

  int i_flags = REG_EXTENDED;
  if (flags->i) {
    i_flags = REG_ICASE;
  }

  int ERROR_reg;
  if ((ERROR_reg = regcomp(&reg_comp, buffer_patterns, i_flags)) != 0) {
    regerror(ERROR_reg, &reg_comp, buffer_patterns, 100);
    printf("regcomp() failed with '%s'\n", buffer_patterns);
    exit(1);
  }
  for (; optind < argc; optind++) {
    if (argc > 4) {
      more_files = TRUE;
    }
    if ((file = fopen(argv[optind], "r")) == NULL) {
      fprintf(stderr, "s21_grep: %s: No such file or directory\n",
              argv[optind]);
    }

    if (file != NULL) {
      char current_line[SIZE] = {0};
      int str_num = 0;
      int str_not_empty_count = 0;
      const size_t nmatch = 1;

      while (fgets(current_line, SIZE, file) != NULL) {
        str_num++;
        int status_err =
            regexec(&reg_comp, current_line, nmatch, struct_reg, 0);
        if (status_err == FALSE && (flags->e || flags->i)) {
          if (more_files) {
            printf("%s:%s", argv[optind], current_line);
          } else {
            printf("%s", current_line);
          }
        } else if (status_err == FALSE && flags->n) {
          if (more_files) {
            printf("%s:%d:%s", argv[optind], str_num, current_line);
          } else {
            printf("%d:%s", str_num, current_line);
          }
          exist = TRUE;
        } else if (status_err == FALSE && flags->c) {
          str_not_empty_count++;
        } else if (status_err != FALSE && flags->v) {
          if (more_files) {
            printf("%s:%s", argv[optind], current_line);
          } else {
            printf("%s", current_line);
          }
        } else if (status_err == FALSE && flags->l) {
          exist = TRUE;
        } else if (status_err == FALSE && disable) {
          if (argc > 3) {
            printf("%s:%s", argv[optind], current_line);
          } else {
            printf("%s", current_line);
          }
        }
      }
      if (more_files && flags->c) {
        printf("%s:%d\n", argv[optind], str_not_empty_count);
        str_not_empty_count = 0;
      } else if (flags->c) {
        printf("%d", str_not_empty_count);
        str_not_empty_count = 0;
      } else if (exist && flags->l) {
        printf("%s\n", argv[optind]);
      }

      if (flags->v || disable || (flags->n && exist == TRUE)) printf("\n");

      exist = FALSE;
      fclose(file);
    } else {
      fprintf(stderr, "s21_grep: %s: No such file or directory\n",
              argv[optind]);
    }
  }
  regfree(&reg_comp);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "s21_grep: To few arguments\n");
  }
  OPT flags = {0};
  char buffer_patterns[SIZE] = {0};

  int status = parser(argc, argv, &flags, buffer_patterns);
  if ((flags.new_word) == 0) {
    strcat(buffer_patterns, argv[optind]);
    optind++;
  }
  output(buffer_patterns, &flags, argc, argv, status);
  return 0;
}
