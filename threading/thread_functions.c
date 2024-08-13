#include "threading.h"


void init_set(SET * set , int len , SITE_DATA * data ){

  set->set_len = len;

  set->data = data;

  set->threadID = (pthread_t *) calloc(len , sizeof(pthread_t));

  set->avil = (AVILABILITY *) calloc(len , sizeof(AVILABILITY));

  for(int i = 0 ;  i < len ; i++){

    set->avil[i] = AVILABLE;
    
  }

}

void init_thread_subsets(THREAD_SUBSET ** subset , SET * set){

  *subset = (THREAD_SUBSET *) calloc(set->set_len ,
				    sizeof(THREAD_SUBSET));

  for(int i = 0 ;  i < set->set_len ; i++){
    (*subset)->status = AVILABLE;
    (*subset)[i].data = set->data + (i * sizeof(SITE_DATA *));
  }
}

void * start_collection(void * thread_subset){

  THREAD_SUBSET * subset = (THREAD_SUBSET *) thread_subset;
  
  getSiteData(subset->data, subset->curl);

  subset->status = COPYING;
  
}

void spawn_collector_threads(SET * set , THREAD_SUBSET * subset){

  int ret;
  
  for(int i = 0 ; i < set->set_len ; i++){

    if(set->avil[i] == AVILABLE ){

      set->avil[i] = NOT_AVILABLE;

      //subset[i].data = &set->data[i];
      subset[i].index_in_set = i;
      subset[i].status = RUNNING;
      
      ret = pthread_create(&set->threadID[i] ,
			   NULL ,
			   start_collection ,
			   (void *) &subset[i] );

      if(ret != 0){

	printf("Error occured while creating threads\n");
	exit(-1);
      }else{
	printf("collector thread no %d spawnned \n",i);
      }
    }
    
  }
  
}


void check_and_copy(SET * set , SET * copy_of_set , THREAD_SUBSET * subset ){

  for(int i = 0 ;  i < set->set_len ; i++){
    if(subset[i].status == COPYING ){
      memcpy(copy_of_set[i].data , set[i].data , sizeof(SITE_DATA) );
      subset[i].status = COMPLETE;
    }
  }
  
  
}

void check_and_kill(SET * set , THREAD_SUBSET * subset){

  for(int i = 0 ; i < set->set_len ; i++){
    if(subset[i].status == COMPLETE){
      pthread_join(set->threadID[i] , NULL);
    }
  }
  
}

void kill_collector_threads(SET * set , THREAD_SUBSET * subset){

  for(int i = 0 ; i < set->set_len ; i++){

    pthread_cancel(set->threadID[i] );
    curl_easy_cleanup(subset[i].curl);
  }
  
}
