#pragma once

// Preprosesor OS check
#if defined(_WIN64) && defined(__CYWIN__)
#define COMPILER "MSVC"
#elif defined(__linux__)
#define COMPILER "gcc"
#elif defined(__APPLE__)
#define COMPILER "clang"
#else
#define COMPILER NULL
#endif

// General flags
#define GFLAGS "-std=c17"

// Dev flags
#define DFLAGS "-g -Wall -Werror -Wextra -pedantic " GFLAGS
#define DEV_FOLDER "dev"

// Prod flags
#define PFLAGS "-O2 " GFLAGS
#define PROD_FOLDER "dist"

// source folder
#define SRC "src"

// EXE name
#define EXE "cm"
