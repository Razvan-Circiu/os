#include "fisiere.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

char *printMenu(char *name, enum FileType type) {
  char *options = malloc(32);
  switch (type) {
  case REG:
    printf("\n%s - REGULAR FILE\n", name);
    printf("--- OPTIONS ---\n");
    printf("-a: access rights\n");
    printf("-d: size\n");
    printf("-h: hard link count\n");
    printf("-l: create symbolic link\n");
    printf("-m: last modified\n");
    printf("-n: name\n");
    printf("\nPlease give some options (Your input should begin with \'-\'): ");
    scanf("%s", options);
    break;
  case LINK:
    // TODO after we get the requirements
    break;
  case DIR:
    // TODO after we get the requirements
    break;
  }
  if (!valid(type, options)) {
    return printMenu(name, type);
  }

  return options;
}

int valid(enum FileType type, const char *options) {
  switch (type) {
  case REG: {
    const char regValidFlags[] = "-adhlmn";
    for (int i = 0; regValidFlags[i] != '\0'; i++) {
      if (!strchr(regValidFlags, options[i])) {
        printf("\nINVALID OPTION: \'%c\'!\n\n", options[i]);
        return 0;
      }
    }
    break;
  }

  case LINK: {
    // TODO after we get the requirements
    break;
  }
  case DIR: {
    // TODO after we get the requirements
    break;
  }
  }

  return 1;
}

void parseArgs(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    struct stat st;
    stat(argv[i], &st);
    if (S_ISREG(st.st_mode)) {
      char *options = printMenu(argv[i], REG);
      runForFile(argv[i], REG, options);
    } else if (S_ISLNK(st.st_mode)) {
      char *options = printMenu(argv[i], LINK);
      runForFile(argv[i], LINK, options);
    } else if (S_ISDIR(st.st_mode)) {
      char *options = printMenu(argv[i], DIR);
      runForFile(argv[i], DIR, options);
    }
  }
}

void runForFile(char *name, enum FileType type, char *options) {
  struct stat st;
  stat(name, &st);

  for (int i = 0; options[i] != '\0'; i++) {
    switch (type) {
    case REG:
      switch (options[i]) {
      case 'a':
        printAccRights(st);
        break;
      case 'd':
        printSize(st);
        break;
      case 'h':
        printLinkCnt(st);
        break;
      case 'l': {
        char linkName[256];
        printf("Please give the link name: ");
        scanf("%s", linkName);
        symlink(name, linkName);
        printf("The link \'%s\' was created.\n", linkName);
        break;
      }
      case 'm':
        break;
      case 'n':
        printf("Name of file: %s\n", name);
        break;
      default:
        break;
      }
    case LINK:
      break;
    case DIR:
      break;
    }
  }
}

void printAccRights(struct stat st) {
  mode_t mode = st.st_mode;
  printf("\nAccess rights:\n");
  printf("  User:\n");
  printf("\tRead - %s\n", mode & S_IRUSR ? "yes" : "no");
  printf("\tWrite - %s\n", mode & S_IWUSR ? "yes" : "no");
  printf("\tExecute - %s\n", mode & S_IXUSR ? "yes" : "no");
  printf("  Group:\n");
  printf("\tRead - %s\n", mode & S_IRGRP ? "yes" : "no");
  printf("\tWrite - %s\n", mode & S_IWGRP ? "yes" : "no");
  printf("\tExecute - %s\n", mode & S_IXGRP ? "yes" : "no");
  printf("  Others:\n");
  printf("\tRead - %s\n", mode & S_IROTH ? "yes" : "no");
  printf("\tWrite - %s\n", mode & S_IWOTH ? "yes" : "no");
  printf("\tExecute - %s\n", mode & S_IXOTH ? "yes" : "no");
}

void printLinkCnt(struct stat st) {
  printf("Hard Link Count: %lu\n", st.st_nlink);
}

void printSize(struct stat st) { printf("Size: %lu bytes\n", st.st_size); }
