#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// General flags
#define GFLAGS "-Wall -Werror -Wextra -pedantic -std=17"

// Dev flags
#define DFLAGS "-g " GFLAGS

// Prod flags
#define PFLAGS "-O2 " GFLAGS

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
}

typedef enum {
  DEV,
  PROD,
} Build;

void build_project(Build build) {
  if (build == DEV)
    system(DFLAGS);

  system(PFLAGS);
}

void run_project(Build build) {
  if (build == DEV) {
    build_project(DEV);
    system("./dev/cm");
  }

  build_project(PROD);
  system("./dist/cm");
}

void clean() {
  system("rm -rf dev");
  system("rm -rf dist");
}

void HandleCLI(int arsgc, char **arsgv) {
  char first[32];
  sprintf(first, "%s", arsgv[1]);

  if (strcmp(first, "n") == 0 || strcmp(first, "new") == 0) {
    if (arsgc < 3) {
      char err[64];
      sprintf(err, "Missing name for %s", first);
      perror(err);
      exit(EXIT_FAILURE);
    }

    create_project(arsgv[2]);
  } else if (strcmp(first, "r") == 0 || strcmp(first, "run") == 0) {
    if (arsgc == 3 && strcmp(arsgv[2], "prod") == 0) {
      run_project(PROD);
      return;
    }

    run_project(DEV);
  } else if (strcmp(first, "c") == 0 || strcmp(first, "clean") == 0) {
    clean();
  } else {
    build_project(DEV);
  }
}
