#pragma once

//system
#include "pthread.h"
#include "stdlib.h"
#include "stdio.h"

//user
#include "threading.h"
#include "fetch_data.h"


typedef enum AVILABILITY {

  AVILABLE,
  COPYING_SET,
  NOT_AVILABLE,
  JOB_DONE
  
} AVILABILITY;


typedef struct SET{

  pthread_t * threadID;
  SITE_DATA * data;
  int set_len;
  AVILABILITY * avil;
  
}SET;



//let this act like a semaphone 
typedef enum THREAD_STATUS{

  RUNNING,
  COPYING,
  COMPLETE,
  
}THREAD_STATUS;

typedef struct THREAD_SUBSET{

  SITE_DATA * data;
  int index_in_set;
  THREAD_STATUS status;
  CURL * curl;
  
}THREAD_SUBSET;



void init_set(SET * set , int len , SITE_DATA * data );

void init_thread_subsets(THREAD_SUBSET ** subset , SET * set);

void * start_collection(void * thread_subset);

void spawn_collector_threads(SET * set , THREAD_SUBSET * subset);

void check_and_copy(SET * set , SET * copy_of_set , THREAD_SUBSET * subset );

void check_and_kill(SET * set , THREAD_SUBSET * subset);

void kill_collector_threads(SET * set , THREAD_SUBSET * subset);
