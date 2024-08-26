#include "cli.h"
#include "clip.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

void create_file(char *src, char *name, char *content) {
  char full_src[1024];
  sprintf(full_src, "%s/%s", src, name);

  FILE *new_file = fopen(src, "w");

  fputs(content, new_file);

  fclose(new_file);
}

void create_project(char *p_name) {
  char name[32];
  sprintf(name, "%s", p_name);

  char cmd[1024];
  sprintf(cmd, "mkdir %s && mkdir %s/src", name, name);

  int t = system(cmd);
  if (t == -1) {
    printf("Project name already taken");
    exit(EXIT_FAILURE);
  }

  char p_route[256];
  sprintf(p_route, "%s/src/main.c", name);

  char main_file[] = "#include <stdio.h>\n"
                     "\n"
                     "int main() {\n"
                     "  printf(\"Hello World!\");\n"
                     "  return 0;\n"
                     "}";
  create_file(SRC, "main.c", main_file);

  if (COMPILER == NULL) {
    perror("OS or Compiler not supported");
    exit(1);
  }

  char conf_file[1024];
  sprintf(conf_file,
          "#config file\n"
          "\n"
          "name: %s\n"
          "version: 0.0.0\n"
          "compiler: %s\n"
          "c_version: c17",
          p_name, COMPILER);

  create_file(SRC, "cystem.conf", conf_file);
}

typedef enum {
  DEV,
  PROD,
} Build;

void build_project(Build build) {
  char build_cmd[512];
  char folder_cmd[64];
  char mkdir[] = "mkdir -p";

  switch (build) {
  case DEV:
    sprintf(folder_cmd, "%s %s", mkdir, DEV_FOLDER);
    sprintf(build_cmd, "%s %s/*.c -o %s/%s %s", COMPILER, SRC, DEV_FOLDER, EXE,
            DFLAGS);
    break;
  case PROD:
    sprintf(folder_cmd, "%s %s", mkdir, PROD_FOLDER);
    sprintf(build_cmd, "%s %s/*.c -o %s/%s %s", COMPILER, SRC, PROD_FOLDER, EXE,
            DFLAGS);
    break;
  }

  system(folder_cmd);
  system(build_cmd);
}

void run_project(Build build) {
  if (build == DEV) {
    build_project(DEV);
    system("./dev/cm");
    return;
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
