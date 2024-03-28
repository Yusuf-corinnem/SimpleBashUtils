#ifndef _PARSING_H_
#define _PARSING_H_
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 15000

typedef struct options {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int flags_counter;
  int flags_counter_e;
  char string_o_flag[BUF];
  char template[BUF];  // строка шаблонов
  char string[BUF];  // строка, которую будем сравнивать RE с string
  char file_name[BUF];  // строка имен файлов
} opt;

enum option_codes {
  CLEAR = 0,
  SET = 1,
  HELP = 2,
};

void priority(opt *options);
void parser(int argc, char *argv[], opt *options);

void i_flag(opt *options, char *argv[], int files_counter, int match);
void h_flag(opt *options, int match);
void e_flag(opt *options, char *argv[], int files_counter, int match);
void f_flag_print(opt *options, char *argv[], int files_counter, int match);
void v_flag(int match, opt *options, char *argv[], int files_counter);
void n_flag(opt *options, char *argv[], int files_counter, int str_count,
            int match);
void o_flag(opt *options, regex_t RE, regmatch_t S, int match);
void s_flag(opt *options, char *argv[], int files_counter, int match);
void c_flag(opt *options, char *argv[], int files_counter, int match_counter);
void c_v_flag(opt *options, char *argv[], int files_counter, int match_counter,
              int match_counter_v);
void c_l_flag(int match, opt *options, char *argv[]);
void simple_grep(int match, opt *options, char *argv[], int files_counter);
void row_delimiter(opt *options, int match, int files_counter, int i);
void files_count(opt *options, int argc, int *files_counter);
void start_flags(opt *options, char *argv[], int files_counter, int str_count,
                 int match, regex_t RE, regmatch_t S);
void f_flag(opt *options);
void execution_file(int argc, char *argv[], opt *options);

#endif  // _PARSING_H_