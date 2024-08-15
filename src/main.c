#include "cli.h"
#include <stdio.h>

int main(int argsc, char **argsv) {
  if (argsc < 2) {
    perror("Missing arguments\n");
    return 1;
  }

  HandleCLI(argsc, argsv);

  return 0;
}
