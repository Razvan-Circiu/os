#include <sys/stat.h>

#ifndef FISIERE_H
#define FISIERE_H

enum FileType { REG, LINK, DIR };

char *printMenu(char *name, enum FileType type);
int valid(enum FileType type, const char *options);
void printAccRights(struct stat st);
void printSize(struct stat st);
void printLinkCnt(struct stat st);
void runForFile(char *name, enum FileType type, char *options);
void parseArgs(int argc, char *argv[]);

#endif // !FISIERE_H
