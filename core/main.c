#include "threading.h"
#include "ui.h"
#include "get_url.h"


int main(void){

  //get urls
  URL * url =  (URL *) malloc(sizeof(URL));
  get_url_names(url);

  //fetch data
  SITE_DATA * site_data;
  SITE_DATA * copy_of_site_data;
  init_site_data( &site_data , url);
  init_site_data( &copy_of_site_data , url);

  //threading init
  SET * set = (SET *) malloc(sizeof(SET));
  SET * copy_of_set = (SET *) malloc(sizeof(SET));
  THREAD_SUBSET * subset;

  init_set(set , url->urlcount , site_data);

  init_set(copy_of_set ,
	   url->urlcount ,
	   copy_of_site_data); //synchronization data not to be used from this one
  
  init_thread_subsets(&subset , set );

  for( int i = 0 ; i < url->urlcount ; i++){
    printf("%s\n",subset->data->url);
  }
  //threading data collection
  spawn_collector_threads(set , subset );

  //window init 
  InitWindow(800, 600, "WEBMONITOR"); 
  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);

  //gameloop
  while (!WindowShouldClose())
    {
      //logic
      // check_and_copy(copy_of_set , set , subset);
      //check_and_kill(set, subset);

      //drawing
      BeginDrawing();
      ClearBackground(RAYWHITE);
      
      EndDrawing();
    }


  //cleanup
  kill_collector_threads(set , subset);
  CloseWindow();
  clear_url_names(url);

  return 0;
}


