#ifndef FILES_H
#define FILES_H


#include "FS.h"
#include <LittleFS.h>
#include <cstring>

#define FORMAT_LITTLEFS_IF_FAILED false
#define BUFFER_SIZE 50

void FSsetup();
void readFile(fs::FS &fs, const char * path, char *message);
void writeFile(fs::FS &fs, const char * path, const char * message);

#endif