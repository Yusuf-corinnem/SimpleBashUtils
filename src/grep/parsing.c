#include "parsing.h"

void priority(opt *options) {
  if (options->f)
    options->e = 0, options->c = 0, options->o = 0, options->s = 0,
    options->h = 0;

  if (options->v) {
    options->f = 0;
  }

  if (options->l && options->c) options->n = 0;

  if (options->l) {
    options->v = 0, options->o = 0, options->f = 0, options->h = 0,
    options->n = 0;
  }

  if (options->c) options->o = 0, options->n = 0;

  if (options->v && options->l) options->o = 0;
}

void e_f_flags(opt *options, char *argv[], int argc) {
  if (!options->e && !options->f) {
    if (argc > optind) {
      strcat(options->template, argv[optind]);
    }
    optind++;
  }
  if (options->e || options->f) {
    options->template[strlen(options->template) - 1] = '\0';
  }
}

void parser(int argc, char *argv[], opt *options) {
  int c;
  while ((c = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, 0)) != -1) {
    switch (c) {
      case 'f':
        options->f = 1, options->flags_counter++;
        f_flag(options);
        break;
      case 'e':
        options->e = 1, options->flags_counter_e++;
        options->flags_counter++;
        strcat(options->template, optarg);
        strcat(options->template, "|");
        break;
      case 'l':
        options->l = 1, options->flags_counter++;
        break;
      case 'c':
        options->c = 1, options->flags_counter++;
        break;
      case 'o':
        options->o = 1, options->flags_counter++;
        break;
      case 'i':
        options->i = 1, options->flags_counter++;
        break;
      case 'v':
        options->v = 1, options->flags_counter++;
        break;
      case 's':
        options->s = 1, options->flags_counter++;
        break;
      case 'n':
        options->n = 1, options->flags_counter++;
        break;
      case 'h':
        options->h = 1, options->flags_counter++;
        break;
      default:
        fprintf(stderr,
                "usage: grep [-ivclnhso] [-e pattern] [-f file] [pattern] "
                "[file ...]");
        break;
    }
  }
  e_f_flags(options, argv, argc);
}