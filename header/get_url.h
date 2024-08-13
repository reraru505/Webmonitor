#pragma once

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define CONFIG_LOCATION "config.txt"
#define MAXSIZE 1000

typedef struct URL{

  char ** urlname;
  int urlcount;
  
}URL;

void get_url_names(URL * url);

void clear_url_names(URL * url);
