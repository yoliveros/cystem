#include <stdio.h>

int main(int argsc, char **argsv) {
  if (argsc < 2) {
    perror("Missing argumensts\n");
    return 1;
  }

  for (int i = 0; argsv[i]; i++)
    printf("%s\n", argsv[i]);

  return 0;
}
