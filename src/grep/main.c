#include "parsing.h"

int main(int argc, char *argv[]) {
  opt options = {0};
  parser(argc, argv, &options);
  priority(&options);

  while (optind < argc) {
    execution_file(argc, argv, &options);
    optind++;
  }
  return 0;
}