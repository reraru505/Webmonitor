#include "threading.h"


void init_thread_subsets(THREAD_SUBSET ** subset , DATA_SET ** set , int len){

  *subset = (THREAD_SUBSET *) calloc(len ,
				    sizeof(THREAD_SUBSET));
  
  for(int i = 0 ;  i < len ; i++){

    (*subset)[i].data_set = set[i];
    (*subset)[i].index = i;
    (*subset)[i].thread_id = (pthread_t *) malloc(sizeof(pthread_t));
    (*subset)[i].data_set = &(*set)[i];
    
  }
}

void * start_collection(void * subset){

  THREAD_SUBSET * thread_subset = (THREAD_SUBSET * ) subset ;
  
  getSiteData(thread_subset->data_set , thread_subset->curl);

  thread_subset->status = COPYING;
  
}

void spawn_collector_threads(THREAD_SUBSET ** subset , int len){

  int ret;
  
  for(int i = 0 ; i < len ; i++){

    (*subset)[i].status = RUNNING;
    
    ret = pthread_create((*subset)[i].thread_id ,
			 NULL ,
			 start_collection ,
			 (void *) &(*subset)[i] );
    
    if(ret != 0){
      
      printf("Error occured while creating threads\n");
      exit(-1);
    }else{
      printf("collector thread no %d spawnned \n",i);
    }
    
    
  }
  
}


void check_and_copy(DATA_SET ** copy_of_dataset , THREAD_SUBSET ** subset , int len ){

  for(int i = 0 ;  i < len ; i++){
    if((*subset)[i].status == COPYING ){
      (*copy_of_dataset)[i].status_code = (*subset)[i].data_set->status_code;
      (*copy_of_dataset)[i].conn_time = (*subset)[i].data_set->conn_time;
      (*copy_of_dataset)[i].res_time = (*subset)[i].data_set->res_time;
      (*copy_of_dataset)[i].code = (*subset)[i].data_set->code;
      (*copy_of_dataset)[i].status = (*subset)[i].data_set->status;
      printf("Data copied from thread %d \n",i);
      (*subset)[i].status = COMPLETE;
    }
  }
  
  
}

void check_and_join(THREAD_SUBSET ** subset , int len){

  for(int i = 0 ; i < len ; i++){
    
    if((*subset)[i].status == COMPLETE){
      pthread_join(*(*subset)[i].thread_id , NULL);
      (*subset)[i].status = JOINED;
    }
    
  }
  
}

void check_and_respawn(THREAD_SUBSET ** subset , int len){

  int ret;
  
  for(int i = 0 ; i < len ; i++){
    if((*subset)[i].status == JOINED){

      (*subset)[i].status = RUNNING;
    
      ret = pthread_create((*subset)[i].thread_id ,
			   NULL ,
			   start_collection ,
			   (void *) &(*subset)[i] );
    
      if(ret != 0){
      
	printf("Error occured while creating threads\n");
	exit(-1);
      }else{
	printf("collector thread no %d spawnned \n",i);
      }

      
    }
  }
}

void kill_collector_threads(THREAD_SUBSET ** subset , int len){

  for(int i = 0 ; i < len ; i++){

    pthread_cancel(*(*subset)[i].thread_id  );
    //pthread_join(*(*subset)[i].thread_id , NULL );
    curl_easy_cleanup((*subset)[i].curl);
  }
  
}
