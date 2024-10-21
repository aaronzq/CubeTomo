#include "files.h"


void FSsetup(){
  if(!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED)){
    Serial.println("LittleFS Mount Failed");
    return;
  }else{
       Serial.println("Little FS Mounted Successfully");
  } 
}

void readFile(fs::FS &fs, const char * path, char *message){
  Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if(!file || file.isDirectory()){
    Serial.println("- failed to open file for reading");
    return;
  }

  Serial.println("- read from file:");
  // while(file.available()){
  //   Serial.write(file.read());
  //   Serial.println(message);
  // }
  if(file.available()){
    // Serial.println(sizeof(message));
    file.readBytes(message, BUFFER_SIZE);
    // Serial.println(strlen(message));
  }
  Serial.println(message);
  file.close();
}

void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- file written");
  } else {
    Serial.println("- write failed");
  }
  file.close();
}