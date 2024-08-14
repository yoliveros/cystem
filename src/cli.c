#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void HandleCLI(int arsgc, char **arsgv) {
  for (int i = 0; arsgv[i]; i++)
    printf("%s\n", arsgv[i]);
  sprintf(arsgv[1], "%s", arsgv[1]);
  char *first = strcat(arsgv[1], "");

  if (strcmp(first, "-n") || strcmp(first, "-new")) {
    if (arsgc < 3) {
      perror(strcat("Missing name for ", first));
      return;
    }

    char *second = arsgv[2];

    int t = system(strcat("mkdir ", second));
    printf("%d\n", t);
  }
}
