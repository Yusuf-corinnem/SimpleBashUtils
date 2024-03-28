#ifndef _PARSING_H_
#define _PARSING_H_
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
} opt;

void parser(int argc, char *argv[], opt *options);
void execution_file(int argc, char *argv[], opt *options);

#endif  // _PARSING_H_