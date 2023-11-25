#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>


#define SIZE 10
#define MAP_ANONYMOUS 0x20


#define msg(txt, ...) fprintf (stderr, txt "\n", ## __VA_ARGS__)

#define killpr(txt, ...) do { msg(txt, ## __VA_ARGS__); exit(EXIT_FAILURE);} while (0)

#define check(expr, txt, ...) do { if (!(expr)) killpr(txt, ## __VA_ARGS__);}  while (0)
