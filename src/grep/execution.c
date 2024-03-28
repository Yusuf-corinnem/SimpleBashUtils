#include "parsing.h"

void execution_file(int argc, char *argv[], opt *options) {
  regex_t RE;
  regmatch_t S;
  int match = 0, match_counter = 0, str_count = 0, empty_string = 0,
      files_counter, one_counter = 0, match_counter_v = 0;
  int i = strlen(options->template);
  int prev = options->string[i - 1];
  files_count(options, argc, &files_counter);
  FILE *f = fopen(argv[optind], "r");
  if (f != NULL) {
    if (options->i) {  // i flag
      regcomp(&RE, options->template, REG_EXTENDED | REG_ICASE);
    } else
      regcomp(&RE, options->template, REG_EXTENDED);
    while (fgets(options->string, BUF, f) != NULL) {
      match = regexec(&RE, options->string, 1, &S, 0);
      str_count++;
      if (!match) {
        match_counter++;
        simple_grep(match, options, argv, files_counter);
      }
      if (options->v) match = !match, match_counter_v++;
      start_flags(options, argv, files_counter, str_count, match, RE, S);
      if (prev == '\n' && options->string[i] == '\n') {
        if (empty_string) continue;
        empty_string = 1;
      } else
        empty_string = 0;
      if (!match && options->c && options->l && one_counter == 0) {
        c_l_flag(match, options, argv);
        one_counter++;
      }
      if (!match && options->l && match_counter == 1)  // l flag
        printf("%s\n", argv[optind]);
    }  // end while
    c_flag(options, argv, files_counter, match_counter);
    c_v_flag(options, argv, files_counter, match_counter, match_counter_v);
    row_delimiter(options, match, files_counter, i);
    regfree(&RE);
  } else {
    if (!options->s) {  // s flag
      fprintf(stderr, "grep: %s: No such file or directory\n", argv[optind]);
    }
  }
  fclose(f);
}

void i_flag(opt *options, char *argv[], int files_counter, int match) {
  if (!match && options->i) {
    if (files_counter > 1 && !options->e && !options->h && !options->n &&
        !options->o && !options->l && !options->c && !options->v)
      printf("%s:%s", argv[optind], options->string);
    else if (!options->e && !options->n && !options->o && !options->f &&
             !options->l && !options->c && !options->v)
      printf("%s", options->string);
  }
}

void h_flag(opt *options, int match) {
  if (!match && options->h) {
    if (!options->o && !options->n && !options->c && !options->v && !options->i)
      printf("%s", options->string);
  }
}

void e_flag(opt *options, char *argv[], int files_counter, int match) {
  if (!match && options->e) {
    if (files_counter >= 1 && !options->f && !options->h && !options->c)
      printf("%s:%s", argv[optind], options->string);
    else if (!options->f && !options->c)
      printf("%s", options->string);
  }
}

void f_flag_print(opt *options, char *argv[], int files_counter, int match) {
  if (!match && options->f) {
    if (files_counter > 1 && !options->h && !options->n && !options->v)
      printf("%s:%s", argv[optind], options->string);
    else if (!options->h && !options->n && !options->v)
      printf("%s", options->string);
  }
}

void v_flag(int match, opt *options, char *argv[], int files_counter) {
  if (options->v) {
    if (!match && files_counter > 1 && !options->h && !options->c)
      printf("%s:%s", argv[optind], options->string);
    else if (!match && !options->c && !options->n)
      printf("%s", options->string);
  }
}

void n_flag(opt *options, char *argv[], int files_counter, int str_count,
            int match) {
  if (options->n && !match) {
    if ((files_counter > 1 && !options->h && !options->f) ||
        (files_counter >= 1 && options->f && !options->h))
      printf("%s:%d:%s", argv[optind], str_count, options->string);
    else
      printf("%d:%s", str_count, options->string);
  }
}

void o_flag(opt *options, regex_t RE, regmatch_t S, int match) {
  if (!match && options->o && !options->l && !options->c) {
    char *pointer = options->string;
    while ((regexec(&RE, pointer, 1, &S, 0) == 0)) {
      printf("%.*s\n", (int)(S.rm_eo - S.rm_so), pointer + S.rm_so);
      pointer += S.rm_eo;
    }
  }
}

void s_flag(opt *options, char *argv[], int files_counter, int match) {
  if (!match && options->s && !options->f && !options->e) {
    if (files_counter > 1 && !options->h)
      printf("%s:%s", argv[optind], options->string);
    else
      printf("%s", options->string);
  }
}

void c_flag(opt *options, char *argv[], int files_counter, int match_counter) {
  if (options->c && !options->l && !options->v) {
    if (files_counter >= 1 && !options->h && options->n)
      printf("%s:%d\n", argv[optind], match_counter);
    else if (files_counter > 1 && !options->h && !options->n)
      printf("%s:%d\n", argv[optind], match_counter);
    else
      printf("%d\n", match_counter);
  }
}

void c_v_flag(opt *options, char *argv[], int files_counter, int match_counter,
              int match_counter_v) {
  if (options->c && !options->l && options->v) {
    if (files_counter > 1 && !options->h)
      printf("%s:%d\n", argv[optind], match_counter_v);
    else
      printf("%d\n", match_counter_v - match_counter);
  }
}

void c_l_flag(int match, opt *options, char *argv[]) {
  if (!match && !options->h) {
    printf("%s:1\n", argv[optind]);
  } else {
    printf("%s:0\n", argv[optind]);
  }
}

void simple_grep(int match, opt *options, char *argv[], int files_counter) {
  if (!match && !options->e && !options->i && !options->v && !options->c &&
      !options->l && !options->n && !options->h && !options->s && !options->f &&
      !options->o) {
    if (files_counter > 1) {
      printf("%s:%s", argv[optind], options->string);
    } else
      printf("%s", options->string);
  }
}

void row_delimiter(opt *options, int match, int files_counter, int i) {
  if (!match && files_counter > 1 && !options->h && !options->l &&
      !options->n && !options->c && !options->v && !options->f) {
    if ((options->string[i - 1] != '\0' && !options->o))
      printf("\n");
    else if (options->string[i - 1] == '\n')
      options->string[i - 1] = '\0';
  }
}

void files_count(opt *options, int argc, int *files_counter) {
  if (options->e) {
    *files_counter = (argc - 1) - (options->flags_counter_e +
                                   (options->flags_counter_e + 1));
  } else
    *files_counter = argc - options->flags_counter - 2;
}

void start_flags(opt *options, char *argv[], int files_counter, int str_count,
                 int match, regex_t RE, regmatch_t S) {
  i_flag(options, argv, files_counter, match);
  h_flag(options, match);
  e_flag(options, argv, files_counter, match);
  f_flag_print(options, argv, files_counter, match);
  v_flag(match, options, argv, files_counter);
  n_flag(options, argv, files_counter, str_count, match);
  o_flag(options, RE, S, match);
  s_flag(options, argv, files_counter, match);
}

void f_flag(opt *options) {
  FILE *f = fopen(optarg, "r");
  if (f != NULL) {
    while (fgets(options->string, BUF, f) != NULL) {
      if (options->string[strlen(options->string) - 1] == '\n' &&
          strlen(options->string) - 1 != '\0') {
        options->string[strlen(options->string) - 1] = '\0';
      }
      strcat(options->template, options->string);
      strcat(options->template, "|");
    }
  } else {
    fprintf(stderr, "grep: %s: No such file or directory\n", optarg);
  }
  fclose(f);
}