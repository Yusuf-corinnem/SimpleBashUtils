#include "parsing.h"

void execution_file(int argc, char *argv[], opt *options) {
  for (int i = optind; i < argc;
       i++) {  // цикл дает возможность чтения нескольких файлов
    FILE *f = fopen(argv[i], "rt");
    if (f != NULL) {
      int cur, str_count = 0, counter = 0, empty_string = 0, prev = 0;
      while ((cur = fgetc(f)) != EOF) {
        if (options->s) {
          if (prev == '\n' && cur == '\n') {
            if (empty_string) continue;
            empty_string = 1;
          } else
            empty_string = 0;
        }
        if (options->b) {  // job b flag
          if (counter == 0 && cur != '\n') printf("%6d\t", ++str_count);
          counter = 1;
          if (cur == '\n') counter = 0;
        }
        if (options->n) {  // job n flag
          if (counter == 0) printf("%6d\t", ++str_count);
          counter = 1;
          if (cur == '\n') counter = 0;
        }
        if (options->e && cur == '\n') printf("$");  // job e flag
        if (options->t && cur == '\t') {
          printf("^");
          cur = '\t' + 64;
        }
        if (options->v) {
          if (cur > 127 && cur < 160) printf("M-^");
          if ((cur < 32 && cur != '\n' && cur != '\t') || cur == 127)
            printf("^");
          if ((cur < 32 || (cur > 126 && cur < 160)) && cur != '\n' &&
              cur != '\t')
            cur = cur > 126 ? cur - 128 + 64 : cur + 64;
        }
        printf("%c", cur);
        prev = cur;
      }
      fclose(f);
    } else {
      fprintf(stderr, "cat: %s: No such file or directory\n", argv[i]);
    }
  }
}