#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void create_project(char *p_name) {

  char name[32];
  sprintf(name, "%s", p_name);

  char cmd[1024];
  sprintf(cmd, "mkdir %s && mkdir %s/src", name, name);

  int t = system(cmd);
  if (t == -1) {
    printf("Folder name already exists");
    exit(EXIT_FAILURE);
  }

  char src[1024];
  sprintf(src, "%s/src/main.c", name);

  FILE *new_file = fopen(src, "w");

  char main_file[] = "#include <stdio.h>\n"
                     "\n"
                     "int main() {\n"
                     "  printf(\"Hello World!\");\n"
                     "  return 0;\n"
                     "}";
  fputs(main_file, new_file);

  fclose(new_file);

  exit(EXIT_SUCCESS);
}

void HandleCLI(int arsgc, char **arsgv) {
  char first[32];
  sprintf(first, "%s", arsgv[1]);

  if (strcmp(first, "-n") || strcmp(first, "-new")) {
    if (arsgc < 3) {
      char err[64];
      sprintf(err, "Missing name for %s", first);
      perror(err);
      exit(EXIT_FAILURE);
    }

    create_project(arsgv[2]);
  }
}
