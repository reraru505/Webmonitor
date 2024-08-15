#pragma once

//system
#include "pthread.h"
#include "stdlib.h"
#include "stdio.h"

//user
#include "threading.h"
#include "fetch_data.h"


//let this act like a semaphone 
typedef enum THREAD_STATUS{

  RUNNING,
  COPYING,
  COMPLETE,
  JOINED
  
}THREAD_STATUS;

typedef struct THREAD_SUBSET{

  pthread_t * thread_id;
  CURL * curl;
  int index;
  DATA_SET * data_set;
  THREAD_STATUS status;
  
  
}THREAD_SUBSET;



void init_thread_subsets(THREAD_SUBSET ** subset , DATA_SET ** set , int len);

void * start_collection(void * subset);

void spawn_collector_threads(THREAD_SUBSET ** subset , int len);

void check_and_copy(DATA_SET ** copy_of_dataset , THREAD_SUBSET ** subset , int len );

void check_and_join(THREAD_SUBSET ** subset , int len);

void check_and_respawn(THREAD_SUBSET ** subset , int len);

void kill_collector_threads(THREAD_SUBSET ** subset , int len );
