#include "get_url.h"



void enumerate_url(URL * url , FILE * desc){

  int count = 0;

  char c;
  while((c = getc(desc)) != EOF){
    if(c == '\n'){
      count++;
    }
  }

  url->urlname = (char **) calloc(count , sizeof(char *));
  
  url->urlcount = count;

  printf("found %d urls \n",url->urlcount);
  
}


void clear_buffer (char * buffer){
  for(int i = 0 ; i < MAXSIZE ; i++){
    buffer[i] = '\0';
  }
}

void get_url_names(URL * url){

  FILE * desc = fopen(CONFIG_LOCATION , "r");

  if(desc == NULL){

    printf("Failed to load config file\n");
    exit(-1);
  }
  
  enumerate_url( url , desc);
  

  fclose(desc);

  desc = fopen(CONFIG_LOCATION , "r");
  
  char c;

  int urlcounter = 0;
  int buffcounter = 0;
  char * buffer = calloc(MAXSIZE , sizeof(char));
  clear_buffer(buffer);

  
  while((c = getc(desc)) != EOF){
    
    if(c != '\n'){

      buffer[buffcounter] = c;
      buffcounter++;
      
    }else {

      url->urlname[urlcounter] = (char *) calloc(buffcounter , sizeof(char));
      strcpy(url->urlname[urlcounter] , buffer);

      //printf("%s\n",buffer); just keeping it for when it counts

      urlcounter++;
      buffcounter = 0;

      clear_buffer(buffer);
    }

  }

  fclose(desc);
  

}

void clear_url_names(URL * url){

  for(int i = 0 ; i < url->urlcount ; i++){

    free(url->urlname[i]);
    
  }

  free(url->urlname);

}
