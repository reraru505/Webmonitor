#include "fetch_data.h"


//query the url and get data from the site using curl
void init_dataset(DATA_SET ** site_data ,URL * url){

  *site_data = (DATA_SET * ) calloc(url->urlcount ,
				    sizeof(DATA_SET) );

  for(int i = 0 ; i < url->urlcount ; i++){

    (*site_data)[i].url =  url->urlname[i];
    (*site_data)[i].status =  UNKNOWN;
    
      
  }

}

 
size_t getCode(char *buffer, size_t itemsize, size_t totalitems, void *userdata ){

  size_t bytes = itemsize*totalitems;
  return bytes;
  
}

//this function is set to modify individual site data 
//please dont forget to add this to threaded funtions
void getSiteData(DATA_SET * site_data , CURL * curl){

  curl = curl_easy_init();
  curl_easy_setopt(curl,
		   CURLOPT_URL,
		   site_data->url );

  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, getCode);
  curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
  printf("in GetstatusCode\n");

  
  CURLcode result = curl_easy_perform(curl);
  
  if(result != CURLE_OK){
    fprintf(stderr,"download problem: %s\n",curl_easy_strerror(result));
  }

  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE,
		    &site_data->status_code);
  
  curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME,
		    &site_data->res_time);
  
  curl_easy_getinfo(curl, CURLINFO_CONNECT_TIME,
		    &site_data->conn_time);
  
  curl_easy_getinfo(curl, CURLINFO_HTTP_CONNECTCODE,
		    &site_data->code);
  

  if(site_data->status_code >=200 && site_data->status_code<=299){

    site_data->status = UP;
    printf("status: UP %ld\n", site_data->status_code);
  }
  else{
    if( site_data->code>=200 && site_data->code<=299){
      site_data->status = UP;
      printf("status: UP %ld\n", site_data->status_code);
    }else{
      site_data->status = DOWN;
      printf("status: DOWN %ld \n", site_data->status_code);
    }
    
  }

  curl_easy_cleanup(curl);
  
} 
