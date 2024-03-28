#include "parsing.h"

int main(int argc, char *argv[]) {
  opt options = {0};
  parser(argc, argv, &options);
  if (options.b) {
    options.n = 0;
  }
  execution_file(argc, argv, &options);
  return 0;
}