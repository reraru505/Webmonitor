//this file contains functions that lets us fetch data over network using curl

#pragma once

#include "stdlib.h"
#include "string.h"
#include "stdint.h"
#include "curl/curl.h"
#include "get_url.h"

typedef enum SITE_STATUS{

  UP,
  DOWN,
  UNKNOWN
  
}SITE_STATUS;


typedef struct SITE_DATA{

  char * url;
  long status_code;
  double conn_time;
  double res_time;
  double code;

  int index;
  int status; //SITE_STATUS
  
}SITE_DATA;


//query the url and get data from the site using curl
void init_site_data(SITE_DATA ** site_data ,URL * url);

//this function is set to modify individual site data 
//please dont forget to add this to threaded funtions
void getSiteData(SITE_DATA * site_data, CURL * curl);
